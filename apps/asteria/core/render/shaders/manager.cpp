#include "manager.hpp"
#include <d3dcompiler.h>
#include <cstring>

#pragma comment(lib, "d3dcompiler.lib")

namespace asteria::core::render::shaders {

PostProcessShader::~PostProcessShader() { shutdown(); }

bool PostProcessShader::init(ID3D11Device* device, IDXGISwapChain* swapchain, const char* hlsl_source, size_t cbuffer_size) {
    if (g_device) return true;

    g_device = device;
    g_device->GetImmediateContext(&g_context);
    m_cbuffer_size = cbuffer_size;

    if (m_cbuffer_size % 16 != 0) m_cbuffer_size = m_cbuffer_size + (16 - (m_cbuffer_size % 16));

    if (FAILED(swapchain->GetBuffer(0, IID_PPV_ARGS(&g_backBufferTexture)))) return false;

    D3D11_TEXTURE2D_DESC textureDesc = {};
    g_backBufferTexture->GetDesc(&textureDesc);

    textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;

    if (FAILED(g_device->CreateTexture2D(&textureDesc, nullptr, &g_copyTexture))) return false;
    if (FAILED(g_device->CreateTexture2D(&textureDesc, nullptr, &g_effectTexture))) return false;
    if (FAILED(g_device->CreateShaderResourceView(g_copyTexture, nullptr, &g_copySRV))) return false;
    if (FAILED(g_device->CreateShaderResourceView(g_effectTexture, nullptr, &g_effectSRV))) return false;
    if (FAILED(g_device->CreateRenderTargetView(g_effectTexture, nullptr, &g_renderTarget))) return false;

    D3D11_SAMPLER_DESC samplerDesc = {};
    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
    samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
    samplerDesc.MaxLOD = 1.0f;

    if (FAILED(g_device->CreateSamplerState(&samplerDesc, &g_samplerState))) return false;

    ID3DBlob* shaderBlob = nullptr;
    ID3DBlob* errorBlob = nullptr;
    HRESULT hr = D3DCompile(hlsl_source, strlen(hlsl_source), nullptr, nullptr, nullptr, "main", "ps_4_0", 0, 0, &shaderBlob, &errorBlob);

    if (FAILED(hr)) {
        if (errorBlob) errorBlob->Release();
        return false;
    }

    g_device->CreatePixelShader(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), nullptr, &g_pixelShader);
    shaderBlob->Release();

    if (m_cbuffer_size > 0) {
        D3D11_BUFFER_DESC cBufferDesc = {};
        cBufferDesc.ByteWidth = static_cast<UINT>(m_cbuffer_size);
        cBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
        cBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        cBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        if (FAILED(g_device->CreateBuffer(&cBufferDesc, nullptr, &g_constantBuffer))) return false;
    }

    return true;
}

void PostProcessShader::begin_frame(ID3D11DeviceContext* context, IDXGISwapChain* swapchain) {
    if (!g_copyTexture || !g_backBufferTexture) return;
    context->CopyResource(g_copyTexture, g_backBufferTexture);
}

void PostProcessShader::apply(ImDrawList* draw_list, void* cbuffer_data, ImVec2 pos, ImVec2 size, ImColor tint, float rounding) {
    if (!g_copySRV || !g_effectSRV) return;

    m_current_cbuffer_data = cbuffer_data;
    ImVec2 displaySize = ImGui::GetIO().DisplaySize;

    ImVec2 uv0 = ImVec2(pos.x / displaySize.x, pos.y / displaySize.y);
    ImVec2 uv1 = ImVec2((pos.x + size.x) / displaySize.x, (pos.y + size.y) / displaySize.y);

    ImDrawList* bg_draw_list = ImGui::GetBackgroundDrawList();
    bg_draw_list->PushClipRectFullScreen();
    bg_draw_list->AddCallback(shader_begin_callback, this);
    bg_draw_list->AddImage(reinterpret_cast<ImTextureID>(g_copySRV), ImVec2(0.0f, 0.0f), displaySize, ImVec2(0.0f, 0.0f), ImVec2(1.0f, 1.0f), ImColor(255, 255, 255));
    bg_draw_list->AddCallback(shader_end_callback, this);
    bg_draw_list->AddCallback(ImDrawCallback_ResetRenderState, nullptr);
    bg_draw_list->PopClipRect();

    draw_list->AddImageRounded(reinterpret_cast<ImTextureID>(g_effectSRV), pos, ImVec2(pos.x + size.x, pos.y + size.y), uv0, uv1, ImColor(255, 255, 255, 255), rounding);

    draw_list->AddRectFilled(pos, ImVec2(pos.x + size.x, pos.y + size.y), tint, rounding);
}

void PostProcessShader::shader_begin_callback(const ImDrawList* parent_list, const ImDrawCmd* cmd) {
    auto* shader = reinterpret_cast<PostProcessShader*>(cmd->UserCallbackData);
    if (shader) shader->bind_shader(shader->m_current_cbuffer_data);
}

void PostProcessShader::shader_end_callback(const ImDrawList* parent_list, const ImDrawCmd* cmd) {
    auto* shader = reinterpret_cast<PostProcessShader*>(cmd->UserCallbackData);
    if (shader) shader->unbind_shader();
}

void PostProcessShader::bind_shader(void* cbuffer_data) {
    if (!g_context || !g_renderTarget) return;

    g_context->OMGetRenderTargets(1, &g_oldRenderTarget, nullptr);
    g_context->OMSetRenderTargets(1, &g_renderTarget, nullptr);

    if (g_constantBuffer && cbuffer_data && m_cbuffer_size > 0) {
        D3D11_MAPPED_SUBRESOURCE mapped;
        if (SUCCEEDED(g_context->Map(g_constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped))) {
            std::memcpy(mapped.pData, cbuffer_data, m_cbuffer_size);
            g_context->Unmap(g_constantBuffer, 0);
        }
        g_context->PSSetConstantBuffers(0, 1, &g_constantBuffer);
    }

    g_context->PSSetSamplers(0, 1, &g_samplerState);
    g_context->PSSetShader(g_pixelShader, nullptr, 0);
}

void PostProcessShader::unbind_shader() {
    if (!g_context) return;
    g_context->OMSetRenderTargets(1, &g_oldRenderTarget, nullptr);
    if (g_oldRenderTarget) {
        g_oldRenderTarget->Release();
        g_oldRenderTarget = nullptr;
    }
}

void PostProcessShader::shutdown() {
    if (g_constantBuffer) {
        g_constantBuffer->Release();
        g_constantBuffer = nullptr;
    }
    if (g_pixelShader) {
        g_pixelShader->Release();
        g_pixelShader = nullptr;
    }
    if (g_samplerState) {
        g_samplerState->Release();
        g_samplerState = nullptr;
    }
    if (g_renderTarget) {
        g_renderTarget->Release();
        g_renderTarget = nullptr;
    }
    if (g_copySRV) {
        g_copySRV->Release();
        g_copySRV = nullptr;
    }
    if (g_effectSRV) {
        g_effectSRV->Release();
        g_effectSRV = nullptr;
    }
    if (g_effectTexture) {
        g_effectTexture->Release();
        g_effectTexture = nullptr;
    }
    if (g_copyTexture) {
        g_copyTexture->Release();
        g_copyTexture = nullptr;
    }
    if (g_backBufferTexture) {
        g_backBufferTexture->Release();
        g_backBufferTexture = nullptr;
    }

    g_context = nullptr;
    g_device = nullptr;
}

} // namespace asteria::core::render::shaders