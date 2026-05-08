#pragma once

#include <d3d11.h>

namespace rendering
{
    class GaussianBlur
    {
    public:
        bool init(ID3D11Device* device, int width, int height);
        void cleanup();
        
        // Apply blur to the current render target
        // Returns the blurred texture
        ID3D11ShaderResourceView* apply(
            ID3D11DeviceContext* context,
            ID3D11ShaderResourceView* input_texture
        );
        
        // Draw a texture as fullscreen quad
        void draw_fullscreen(
            ID3D11DeviceContext* context,
            ID3D11ShaderResourceView* texture
        );
        
        void resize(ID3D11Device* device, int width, int height);
        
    private:
        // Render targets for two-pass blur
        ID3D11Texture2D* m_horizontal_texture = nullptr;
        ID3D11RenderTargetView* m_horizontal_rtv = nullptr;
        ID3D11ShaderResourceView* m_horizontal_srv = nullptr;
        
        ID3D11Texture2D* m_vertical_texture = nullptr;
        ID3D11RenderTargetView* m_vertical_rtv = nullptr;
        ID3D11ShaderResourceView* m_vertical_srv = nullptr;
        
        // Shaders
        ID3D11VertexShader* m_vertex_shader = nullptr;
        ID3D11PixelShader* m_blur_horizontal_ps = nullptr;
        ID3D11PixelShader* m_blur_vertical_ps = nullptr;
        ID3D11PixelShader* m_passthrough_ps = nullptr;
        
        // Input layout
        ID3D11InputLayout* m_input_layout = nullptr;
        
        // Sampler state
        ID3D11SamplerState* m_sampler = nullptr;
        
        // Fullscreen quad vertex buffer
        ID3D11Buffer* m_vertex_buffer = nullptr;
        
        int m_width = 0;
        int m_height = 0;
        
        bool create_render_targets(ID3D11Device* device);
        bool create_shaders(ID3D11Device* device);
        bool create_sampler(ID3D11Device* device);
        bool create_vertex_buffer(ID3D11Device* device);
    };
}
