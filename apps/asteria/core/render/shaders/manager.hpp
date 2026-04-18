#pragma once

#include <d3d11.h>
#include <imgui.h>
#include <cstdint>

namespace asteria::core::render::shaders {

class PostProcessShader {
  public:
    PostProcessShader() = default;
    ~PostProcessShader();

    bool init(ID3D11Device* device, IDXGISwapChain* swapchain, const char* hlsl_source, size_t cbuffer_size);
    void begin_frame(ID3D11DeviceContext* context, IDXGISwapChain* swapchain);
    void apply(ImDrawList* draw_list, void* cbuffer_data, ImVec2 pos, ImVec2 size, ImColor tint = ImColor(255, 255, 255, 255), float rounding = 0.0f);
    void shutdown();

  private:
    static void shader_begin_callback(const ImDrawList* parent_list, const ImDrawCmd* cmd);
    static void shader_end_callback(const ImDrawList* parent_list, const ImDrawCmd* cmd);

    void bind_shader(void* cbuffer_data);
    void unbind_shader();

  private:
    ID3D11Device* g_device = nullptr;
    ID3D11DeviceContext* g_context = nullptr;
    ID3D11RenderTargetView* g_renderTarget = nullptr;
    ID3D11Texture2D* g_backBufferTexture = nullptr;
    ID3D11Texture2D* g_copyTexture = nullptr;
    ID3D11Texture2D* g_effectTexture = nullptr;
    ID3D11SamplerState* g_samplerState = nullptr;
    ID3D11ShaderResourceView* g_copySRV = nullptr;
    ID3D11ShaderResourceView* g_effectSRV = nullptr;
    ID3D11PixelShader* g_pixelShader = nullptr;
    ID3D11Buffer* g_constantBuffer = nullptr;

    ID3D11RenderTargetView* g_oldRenderTarget = nullptr;

    size_t m_cbuffer_size = 0;
    alignas(16) unsigned char m_safe_data[256]{};
    struct SafePtr {
        unsigned char* dst;
        size_t* sz;
        void operator=(void* src) {
            if (src && sz && *sz <= 256) {
                const unsigned char* s = static_cast<const unsigned char*>(src);
                for (size_t i = 0; i < *sz; ++i) dst[i] = s[i];
            }
        }
        operator void*() { return dst; }
    } m_current_cbuffer_data{m_safe_data, &m_cbuffer_size};
};

} // namespace asteria::core::render::shaders