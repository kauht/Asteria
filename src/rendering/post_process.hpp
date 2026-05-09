#pragma once

#include <d3d11.h>

namespace rendering
{
    class PostProcess
    {
    public:
        bool init(ID3D11Device* device, int width, int height);
        void cleanup();
        void resize(ID3D11Device* device, int width, int height);
        
        // Apply Gaussian blur to the current backbuffer
        // Returns the blurred texture
        ID3D11ShaderResourceView* apply_blur(
            ID3D11DeviceContext* context,
            ID3D11ShaderResourceView* input_texture,
            float sigma = 5.0f,
            int radius = 10
        );
        
    private:
        ID3D11Device* m_device = nullptr;
        
        // Intermediate render targets for two-pass blur
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
        
        // Constant buffer for blur parameters
        ID3D11Buffer* m_blur_params_cb = nullptr;
        
        // Input layout and vertex buffer
        ID3D11InputLayout* m_input_layout = nullptr;
        ID3D11Buffer* m_vertex_buffer = nullptr;
        
        // Sampler state
        ID3D11SamplerState* m_sampler = nullptr;
        
        int m_width = 0;
        int m_height = 0;
        
        bool create_shaders(ID3D11Device* device);
        bool create_render_targets(ID3D11Device* device);
        bool create_buffers(ID3D11Device* device);
    };
}
