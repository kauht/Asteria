#include "post_process.hpp"
#include <d3dcompiler.h>
#include <cmath>

#pragma comment(lib, "d3dcompiler.lib")

namespace rendering
{
    // Vertex shader for fullscreen quad
    static const char* g_vertex_shader_src = R"(
        struct VS_INPUT
        {
            float2 pos : POSITION;
            float2 uv : TEXCOORD0;
        };
        
        struct PS_INPUT
        {
            float4 pos : SV_POSITION;
            float2 uv : TEXCOORD0;
        };
        
        PS_INPUT main(VS_INPUT input)
        {
            PS_INPUT output;
            output.pos = float4(input.pos, 0.0f, 1.0f);
            output.uv = input.uv;
            return output;
        }
    )";
    
    // Horizontal Gaussian blur pixel shader
    static const char* g_blur_horizontal_ps_src = R"(
        Texture2D tex : register(t0);
        SamplerState samp : register(s0);
        
        cbuffer BlurParams : register(b0)
        {
            float2 texelSize;
            float sigma;
            int radius;
        };
        
        struct PS_INPUT
        {
            float4 pos : SV_POSITION;
            float2 uv : TEXCOORD0;
        };
        
        float Gauss(float sigma, int x)
        {
            return exp(-(x * x) / (2.0 * sigma * sigma));
        }
        
        float4 main(PS_INPUT input) : SV_Target
        {
            float4 result = 0;
            float totalWeight = 0;
            
            // Horizontal blur
            for (int i = -radius; i <= radius; i++)
            {
                float weight = Gauss(sigma, i);
                float2 offset = float2(texelSize.x * i, 0);
                result += tex.Sample(samp, input.uv + offset) * weight;
                totalWeight += weight;
            }
            
            return result / totalWeight;
        }
    )";
    
    // Vertical Gaussian blur pixel shader
    static const char* g_blur_vertical_ps_src = R"(
        Texture2D tex : register(t0);
        SamplerState samp : register(s0);
        
        cbuffer BlurParams : register(b0)
        {
            float2 texelSize;
            float sigma;
            int radius;
        };
        
        struct PS_INPUT
        {
            float4 pos : SV_POSITION;
            float2 uv : TEXCOORD0;
        };
        
        float Gauss(float sigma, int x)
        {
            return exp(-(x * x) / (2.0 * sigma * sigma));
        }
        
        float4 main(PS_INPUT input) : SV_Target
        {
            float4 result = 0;
            float totalWeight = 0;
            
            // Vertical blur
            for (int i = -radius; i <= radius; i++)
            {
                float weight = Gauss(sigma, i);
                float2 offset = float2(0, texelSize.y * i);
                result += tex.Sample(samp, input.uv + offset) * weight;
                totalWeight += weight;
            }
            
            return result / totalWeight;
        }
    )";
    
    struct Vertex
    {
        float pos[2];
        float uv[2];
    };
    
    struct BlurParams
    {
        float texelSize[2];
        float sigma;
        int radius;
    };
    
    bool PostProcess::init(ID3D11Device* device, int width, int height)
    {
        m_device = device;
        m_width = width;
        m_height = height;
        
        if (!create_shaders(device)) return false;
        if (!create_render_targets(device)) return false;
        if (!create_buffers(device)) return false;
        
        return true;
    }
    
    void PostProcess::cleanup()
    {
        if (m_horizontal_srv) { m_horizontal_srv->Release(); m_horizontal_srv = nullptr; }
        if (m_horizontal_rtv) { m_horizontal_rtv->Release(); m_horizontal_rtv = nullptr; }
        if (m_horizontal_texture) { m_horizontal_texture->Release(); m_horizontal_texture = nullptr; }
        
        if (m_vertical_srv) { m_vertical_srv->Release(); m_vertical_srv = nullptr; }
        if (m_vertical_rtv) { m_vertical_rtv->Release(); m_vertical_rtv = nullptr; }
        if (m_vertical_texture) { m_vertical_texture->Release(); m_vertical_texture = nullptr; }
        
        if (m_vertex_shader) { m_vertex_shader->Release(); m_vertex_shader = nullptr; }
        if (m_blur_horizontal_ps) { m_blur_horizontal_ps->Release(); m_blur_horizontal_ps = nullptr; }
        if (m_blur_vertical_ps) { m_blur_vertical_ps->Release(); m_blur_vertical_ps = nullptr; }
        
        if (m_blur_params_cb) { m_blur_params_cb->Release(); m_blur_params_cb = nullptr; }
        if (m_input_layout) { m_input_layout->Release(); m_input_layout = nullptr; }
        if (m_vertex_buffer) { m_vertex_buffer->Release(); m_vertex_buffer = nullptr; }
        if (m_sampler) { m_sampler->Release(); m_sampler = nullptr; }
    }
    
    void PostProcess::resize(ID3D11Device* device, int width, int height)
    {
        if (m_width == width && m_height == height)
            return;
        
        // Release old render targets
        if (m_horizontal_srv) { m_horizontal_srv->Release(); m_horizontal_srv = nullptr; }
        if (m_horizontal_rtv) { m_horizontal_rtv->Release(); m_horizontal_rtv = nullptr; }
        if (m_horizontal_texture) { m_horizontal_texture->Release(); m_horizontal_texture = nullptr; }
        
        if (m_vertical_srv) { m_vertical_srv->Release(); m_vertical_srv = nullptr; }
        if (m_vertical_rtv) { m_vertical_rtv->Release(); m_vertical_rtv = nullptr; }
        if (m_vertical_texture) { m_vertical_texture->Release(); m_vertical_texture = nullptr; }
        
        m_width = width;
        m_height = height;
        
        create_render_targets(device);
    }
    
    bool PostProcess::create_shaders(ID3D11Device* device)
    {
        ID3DBlob* vs_blob = nullptr;
        ID3DBlob* error_blob = nullptr;
        
        // Compile vertex shader
        if (FAILED(D3DCompile(g_vertex_shader_src, strlen(g_vertex_shader_src), nullptr, nullptr, nullptr,
            "main", "vs_5_0", 0, 0, &vs_blob, &error_blob)))
        {
            if (error_blob) error_blob->Release();
            return false;
        }
        
        if (FAILED(device->CreateVertexShader(vs_blob->GetBufferPointer(), vs_blob->GetBufferSize(), nullptr, &m_vertex_shader)))
        {
            vs_blob->Release();
            return false;
        }
        
        // Create input layout
        D3D11_INPUT_ELEMENT_DESC layout[] = {
            { "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 8, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        };
        
        if (FAILED(device->CreateInputLayout(layout, 2, vs_blob->GetBufferPointer(), vs_blob->GetBufferSize(), &m_input_layout)))
        {
            vs_blob->Release();
            return false;
        }
        
        vs_blob->Release();
        
        // Compile horizontal blur pixel shader
        ID3DBlob* ps_blob = nullptr;
        if (FAILED(D3DCompile(g_blur_horizontal_ps_src, strlen(g_blur_horizontal_ps_src), nullptr, nullptr, nullptr,
            "main", "ps_5_0", 0, 0, &ps_blob, &error_blob)))
        {
            if (error_blob) error_blob->Release();
            return false;
        }
        
        if (FAILED(device->CreatePixelShader(ps_blob->GetBufferPointer(), ps_blob->GetBufferSize(), nullptr, &m_blur_horizontal_ps)))
        {
            ps_blob->Release();
            return false;
        }
        ps_blob->Release();
        
        // Compile vertical blur pixel shader
        if (FAILED(D3DCompile(g_blur_vertical_ps_src, strlen(g_blur_vertical_ps_src), nullptr, nullptr, nullptr,
            "main", "ps_5_0", 0, 0, &ps_blob, &error_blob)))
        {
            if (error_blob) error_blob->Release();
            return false;
        }
        
        if (FAILED(device->CreatePixelShader(ps_blob->GetBufferPointer(), ps_blob->GetBufferSize(), nullptr, &m_blur_vertical_ps)))
        {
            ps_blob->Release();
            return false;
        }
        ps_blob->Release();
        
        return true;
    }
    
    bool PostProcess::create_render_targets(ID3D11Device* device)
    {
        D3D11_TEXTURE2D_DESC tex_desc = {};
        tex_desc.Width = m_width;
        tex_desc.Height = m_height;
        tex_desc.MipLevels = 1;
        tex_desc.ArraySize = 1;
        tex_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        tex_desc.SampleDesc.Count = 1;
        tex_desc.Usage = D3D11_USAGE_DEFAULT;
        tex_desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
        
        // Horizontal pass texture
        if (FAILED(device->CreateTexture2D(&tex_desc, nullptr, &m_horizontal_texture)))
            return false;
        if (FAILED(device->CreateRenderTargetView(m_horizontal_texture, nullptr, &m_horizontal_rtv)))
            return false;
        if (FAILED(device->CreateShaderResourceView(m_horizontal_texture, nullptr, &m_horizontal_srv)))
            return false;
        
        // Vertical pass texture
        if (FAILED(device->CreateTexture2D(&tex_desc, nullptr, &m_vertical_texture)))
            return false;
        if (FAILED(device->CreateRenderTargetView(m_vertical_texture, nullptr, &m_vertical_rtv)))
            return false;
        if (FAILED(device->CreateShaderResourceView(m_vertical_texture, nullptr, &m_vertical_srv)))
            return false;
        
        return true;
    }
    
    bool PostProcess::create_buffers(ID3D11Device* device)
    {
        // Create vertex buffer for fullscreen quad
        Vertex vertices[] = {
            { { -1.0f,  1.0f }, { 0.0f, 0.0f } },  // Top-left
            { {  1.0f,  1.0f }, { 1.0f, 0.0f } },  // Top-right
            { { -1.0f, -1.0f }, { 0.0f, 1.0f } },  // Bottom-left
            { {  1.0f, -1.0f }, { 1.0f, 1.0f } },  // Bottom-right
        };
        
        D3D11_BUFFER_DESC buffer_desc = {};
        buffer_desc.Usage = D3D11_USAGE_DEFAULT;
        buffer_desc.ByteWidth = sizeof(vertices);
        buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        
        D3D11_SUBRESOURCE_DATA init_data = {};
        init_data.pSysMem = vertices;
        
        if (FAILED(device->CreateBuffer(&buffer_desc, &init_data, &m_vertex_buffer)))
            return false;
        
        // Create constant buffer for blur parameters
        buffer_desc = {};
        buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
        buffer_desc.ByteWidth = sizeof(BlurParams);
        buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        
        if (FAILED(device->CreateBuffer(&buffer_desc, nullptr, &m_blur_params_cb)))
            return false;
        
        // Create sampler state
        D3D11_SAMPLER_DESC sampler_desc = {};
        sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
        sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
        sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
        sampler_desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
        sampler_desc.MinLOD = 0;
        sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;
        
        return SUCCEEDED(device->CreateSamplerState(&sampler_desc, &m_sampler));
    }
    
    ID3D11ShaderResourceView* PostProcess::apply_blur(
        ID3D11DeviceContext* context,
        ID3D11ShaderResourceView* input_texture,
        float sigma,
        int radius)
    {
        // Save current state
        ID3D11RenderTargetView* old_rtv = nullptr;
        ID3D11DepthStencilView* old_dsv = nullptr;
        context->OMGetRenderTargets(1, &old_rtv, &old_dsv);
        
        // Update blur parameters
        D3D11_MAPPED_SUBRESOURCE mapped;
        if (SUCCEEDED(context->Map(m_blur_params_cb, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped)))
        {
            BlurParams* params = (BlurParams*)mapped.pData;
            params->texelSize[0] = 1.0f / m_width;
            params->texelSize[1] = 1.0f / m_height;
            params->sigma = sigma;
            params->radius = radius;
            context->Unmap(m_blur_params_cb, 0);
        }
        
        // Set up rendering state
        UINT stride = sizeof(Vertex);
        UINT offset = 0;
        context->IASetInputLayout(m_input_layout);
        context->IASetVertexBuffers(0, 1, &m_vertex_buffer, &stride, &offset);
        context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
        context->VSSetShader(m_vertex_shader, nullptr, 0);
        context->PSSetSamplers(0, 1, &m_sampler);
        context->PSSetConstantBuffers(0, 1, &m_blur_params_cb);
        
        D3D11_VIEWPORT viewport = {};
        viewport.Width = (float)m_width;
        viewport.Height = (float)m_height;
        viewport.MinDepth = 0.0f;
        viewport.MaxDepth = 1.0f;
        context->RSSetViewports(1, &viewport);
        
        // Horizontal blur pass
        context->OMSetRenderTargets(1, &m_horizontal_rtv, nullptr);
        context->PSSetShader(m_blur_horizontal_ps, nullptr, 0);
        context->PSSetShaderResources(0, 1, &input_texture);
        context->Draw(4, 0);
        
        // Clear shader resource
        ID3D11ShaderResourceView* null_srv = nullptr;
        context->PSSetShaderResources(0, 1, &null_srv);
        
        // Vertical blur pass
        context->OMSetRenderTargets(1, &m_vertical_rtv, nullptr);
        context->PSSetShader(m_blur_vertical_ps, nullptr, 0);
        context->PSSetShaderResources(0, 1, &m_horizontal_srv);
        context->Draw(4, 0);
        
        // Clear shader resource
        context->PSSetShaderResources(0, 1, &null_srv);
        
        // Restore old render target
        context->OMSetRenderTargets(1, &old_rtv, old_dsv);
        if (old_rtv) old_rtv->Release();
        if (old_dsv) old_dsv->Release();
        
        return m_vertical_srv;
    }
}
