#pragma once

#include <d3d11.h>
#include <imgui.h>

namespace asteria::core::render::shaders::blur {

bool init(ID3D11Device* device, IDXGISwapChain* swapchain);
void begin_frame(ID3D11DeviceContext* context, IDXGISwapChain* swapchain);
void apply_blur(ImDrawList* draw_list, float size = 5.0f, float quality = 4.0f, float directions = 16.0f, ImColor tint = ImColor(26, 26, 26, 242));
void shutdown();

} // namespace asteria::core::render::shaders::blur