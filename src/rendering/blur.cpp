#include "blur.hpp"
#include <d3dcompiler.h>

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
    
    // Horizontal blur pixel shader - strong blur
    static const char* g_blur_horizontal_ps_src = R"(
        Texture2D tex : register(t0);
        SamplerState samp : register(s0);
        
        struct PS_INPUT
        {
            float4 pos : SV_POSITION;
            float2 uv : TEXCOORD0;
        };
        
        // Gaussian blur weights for strong radius (about 15px)
        static const float weights[11] = {
            0.03, 0.05, 0.08, 0.11, 0.13, 0.14, 0.13, 0.11, 0.08, 0.05, 0.03
        };
        
        float4 main(PS_INPUT input) : SV_Target
        {
            float2 tex_size;
            tex.GetDimensions(tex_size.x, tex_size.y);
            float2 tex_offset = 1.0 / tex_size;
            
            float4 result = tex.Sample(samp, input.uv) * weights[5];
            
            // Sample horizontally - 5 samples each direction
            for (int i = 1; i <= 5; i++)
            {
                float2 offset = float2(tex_offset.x * float(i) * 1.5, 0.0);
                result += tex.Sample(samp, input.uv + offset) * weights[5 + i];
                result += tex.Sample(samp, input.uv - offset) * weights[5 - i];
            }
            
            return result;
        }
    )";
    
    // Vertical blur pixel shader - strong blur
    static const char* g_blur_vertical_ps_src = R"(
        Texture2D tex : register(t0);
        SamplerState samp : register(s0);
        
        struct PS_INPUT
        {
            float4 pos : SV_POSITION;
            float2 uv : TEXCOORD0;
        };
        
        // Gaussian blur weights for strong radius (about 15px)
        static const float weights[11] = {
            0.03, 0.05, 0.08, 0.11, 0.13, 0.14, 0.13, 0.11, 0.08, 0.05, 0.03
        };
        
        float4 main(PS_INPUT input) : SV_Target
        {
            float2 tex_size;
            tex.GetDimensions(tex_size.x, tex_size.y);
            float2 tex_offset = 1.0 / tex_size;
            
            float4 result = tex.Sample(samp, input.uv) * weights[5];
            
            // Sample vertically - 5 samples each direction
            for (int i = 1; i <= 5; i++)
            {
                float2 offset = float2(0.0, tex_offset.y * float(i) * 1.5);
                result += tex.Sample(samp, input.uv + offset) * weights[5 + i];
                result += tex.Sample(samp, input.uv - offset) * weights[5 - i];
            }
            
            return result;
        }
    )";
    
    // Simple passthrough pixel shader
    static const char* g_passthrough_ps_src = R"(
        Texture2D tex : register(t0);
        SamplerState samp : register(s0);
        
        struct PS_INPUT
        {
            float4 pos : SV_POSITION;
            float2 uv : TEXCOORD0;
        };
        
        float4 main(PS_INPUT input) : SV_Target
        {
            return tex.Sample(samp, input.uv);
        }
    )";
    
    struct Vertex
    {
        float pos[2];
        float uv[2];
    };
    
    bool GaussianBlur::init(ID3D11Device* device, int width, int height)
    {
        m_width = width;
        m_height = height;
        
        if (!create_shaders(device)) return false;
        if (!create_sampler(device)) return false;
        if (!create_vertex_buffer(device)) return false;
        if (!create_render_targets(device)) return false;
        
        return true;
    }
    
    void GaussianBlur::cleanup()
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
        if (m_passthrough_ps) { m_passthrough_ps->Release(); m_passthrough_ps = nullptr; }
        
        if (m_input_layout) { m_input_layout->Release(); m_input_layout = nullptr; }
        if (m_sampler) { m_sampler->Release(); m_sampler = nullptr; }
        if (m_vertex_buffer) { m_vertex_buffer->Release(); m_vertex_buffer = nullptr; }
    }
    
    bool GaussianBlur::create_render_targets(ID3D11Device* device)
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
    
    bool GaussianBlur::create_shaders(ID3D11Device* device)
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
        
        // Compile passthrough pixel shader
        if (FAILED(D3DCompile(g_passthrough_ps_src, strlen(g_passthrough_ps_src), nullptr, nullptr, nullptr,
            "main", "ps_5_0", 0, 0, &ps_blob, &error_blob)))
        {
            if (error_blob) error_blob->Release();
            return false;
        }
        
        if (FAILED(device->CreatePixelShader(ps_blob->GetBufferPointer(), ps_blob->GetBufferSize(), nullptr, &m_passthrough_ps)))
        {
            ps_blob->Release();
            return false;
        }
        ps_blob->Release();
        
        return true;
    }
    
    bool GaussianBlur::create_sampler(ID3D11Device* device)
    {
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
    
    bool GaussianBlur::create_vertex_buffer(ID3D11Device* device)
    {
        // Fullscreen quad vertices
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
        
        return SUCCEEDED(device->CreateBuffer(&buffer_desc, &init_data, &m_vertex_buffer));
    }
    
    ID3D11ShaderResourceView* GaussianBlur::apply(ID3D11DeviceContext* context, ID3D11ShaderResourceView* input_texture)
    {
        // Save current state
        ID3D11RenderTargetView* old_rtv = nullptr;
        ID3D11DepthStencilView* old_dsv = nullptr;
        context->OMGetRenderTargets(1, &old_rtv, &old_dsv);
        
        // Disable depth testing
        context->OMSetDepthStencilState(nullptr, 0);
        
        // Set up for rendering
        UINT stride = sizeof(Vertex);
        UINT offset = 0;
        context->IASetInputLayout(m_input_layout);
        context->IASetVertexBuffers(0, 1, &m_vertex_buffer, &stride, &offset);
        context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
        context->VSSetShader(m_vertex_shader, nullptr, 0);
        context->PSSetSamplers(0, 1, &m_sampler);
        
        // Disable blending for render-to-texture passes
        context->OMSetBlendState(nullptr, nullptr, 0xffffffff);
        
        D3D11_VIEWPORT viewport = {};
        viewport.Width = (float)m_width;
        viewport.Height = (float)m_height;
        viewport.MinDepth = 0.0f;
        viewport.MaxDepth = 1.0f;
        context->RSSetViewports(1, &viewport);
        
        // Set rasterizer state - no culling
        D3D11_RASTERIZER_DESC raster_desc = {};
        raster_desc.FillMode = D3D11_FILL_SOLID;
        raster_desc.CullMode = D3D11_CULL_NONE;
        raster_desc.DepthClipEnable = TRUE;
        
        ID3D11Device* device = nullptr;
        ID3D11RasterizerState* raster_state = nullptr;
        context->GetDevice(&device);
        device->CreateRasterizerState(&raster_desc, &raster_state);
        device->Release();
        context->RSSetState(raster_state);
        
        // Horizontal blur pass
        float clear_color[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
        context->ClearRenderTargetView(m_horizontal_rtv, clear_color);
        context->OMSetRenderTargets(1, &m_horizontal_rtv, nullptr);
        context->PSSetShader(m_blur_horizontal_ps, nullptr, 0);
        context->PSSetShaderResources(0, 1, &input_texture);
        context->Draw(4, 0);
        
        // Clear shader resource
        ID3D11ShaderResourceView* null_srv = nullptr;
        context->PSSetShaderResources(0, 1, &null_srv);
        
        // Vertical blur pass
        context->ClearRenderTargetView(m_vertical_rtv, clear_color);
        context->OMSetRenderTargets(1, &m_vertical_rtv, nullptr);
        context->PSSetShader(m_blur_vertical_ps, nullptr, 0);
        context->PSSetShaderResources(0, 1, &m_horizontal_srv);
        context->Draw(4, 0);
        
        // Clear shader resource
        context->PSSetShaderResources(0, 1, &null_srv);
        
        // Cleanup
        if (raster_state) raster_state->Release();
        
        // Restore old render target
        context->OMSetRenderTargets(1, &old_rtv, old_dsv);
        if (old_rtv) old_rtv->Release();
        if (old_dsv) old_dsv->Release();
        
        return m_vertical_srv;
    }
    
    void GaussianBlur::resize(ID3D11Device* device, int width, int height)
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
    
    void GaussianBlur::draw_fullscreen(ID3D11DeviceContext* context, ID3D11ShaderResourceView* texture)
    {
        // Set up for rendering
        UINT stride = sizeof(Vertex);
        UINT offset = 0;
        context->IASetInputLayout(m_input_layout);
        context->IASetVertexBuffers(0, 1, &m_vertex_buffer, &stride, &offset);
        context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
        context->VSSetShader(m_vertex_shader, nullptr, 0);
        context->PSSetShader(m_passthrough_ps, nullptr, 0);
        context->PSSetSamplers(0, 1, &m_sampler);
        context->PSSetShaderResources(0, 1, &texture);
        
        D3D11_VIEWPORT viewport = {};
        viewport.Width = (float)m_width;
        viewport.Height = (float)m_height;
        viewport.MinDepth = 0.0f;
        viewport.MaxDepth = 1.0f;
        context->RSSetViewports(1, &viewport);
        
        context->Draw(4, 0);
        
        // Clear shader resource
        ID3D11ShaderResourceView* null_srv = nullptr;
        context->PSSetShaderResources(0, 1, &null_srv);
    }
}
