#include "blur.hpp"
#include "manager.hpp"
#include <imgui.h>

namespace asteria::core::render::shaders::blur {

struct alignas(16) BlurInputBufferT {
    float textureSize[2];
    float blurDirections;
    float blurQuality;
    float blurRadius;
    float padding[3];
};

static PostProcessShader g_blur_shader;

constexpr const char* blurPixelShaderSource = R"(
        struct PsInput {
            float4 pos : SV_POSITION;
            float4 color : COLOR0;
            float2 uv : TEXCOORD0;
        };

        cbuffer BlurInputBuffer : register(b0) {
            float2 textureSize;
            float blurDirections;
            float blurQuality;
            float blurRadius;
        };

        Texture2D backTexture : register(t0);
        sampler textureSampler : register(s0);

        float4 main(PsInput input) : SV_Target {
            const float pi2 = 6.28318530718f;

            float2 radius = blurRadius / textureSize;
            float4 color = backTexture.Sample(textureSampler, input.uv);

            float increment = 1.0f / blurQuality;
            for (float d = 0.0f; d < pi2; d += pi2 / blurDirections) {
                for (float i = increment; i < 1.00001f; i += increment) {
                    float2 blurUv = input.uv + float2(cos(d), sin(d)) * radius * i;
                    color += backTexture.Sample(textureSampler, blurUv);
                }
            }

            color /= (blurQuality * blurDirections + 1.0f);
            color.a = 1.0f;
            return color;
        }
    )";

bool init(ID3D11Device* device, IDXGISwapChain* swapchain) { return g_blur_shader.init(device, swapchain, blurPixelShaderSource, sizeof(BlurInputBufferT)); }
void begin_frame(ID3D11DeviceContext* context, IDXGISwapChain* swapchain) { g_blur_shader.begin_frame(context, swapchain); }
void apply_blur(ImDrawList* draw_list, float size, float quality, float directions, ImColor tint) {
    BlurInputBufferT params = {};
    params.textureSize[0] = ImGui::GetIO().DisplaySize.x;
    params.textureSize[1] = ImGui::GetIO().DisplaySize.y;
    params.blurRadius = size;
    params.blurQuality = quality;
    params.blurDirections = directions;

    ImVec2 window_pos = ImGui::GetWindowPos();
    ImVec2 window_size = ImGui::GetWindowSize();
    float window_rounding = ImGui::GetStyle().WindowRounding;

    g_blur_shader.apply(draw_list, &params, window_pos, window_size, tint, window_rounding);
}
void shutdown() { g_blur_shader.shutdown(); }
} // namespace asteria::core::render::shaders::blur
