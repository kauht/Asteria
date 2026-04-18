#pragma once
#include <windows.h>
#include <d3d11.h>

namespace asteria {
inline bool g_show_menu = true;
inline bool g_imgui_init = false;
inline float g_blur_radius = 32.0f;

inline float g_accent_color[4] = {0.50f, 0.49f, 0.58f, 1.00f};
inline float g_bg_color[4] = {0.04f, 0.04f, 0.04f, 0.86f};
inline float g_text_color[4] = {0.90f, 0.90f, 0.90f, 1.00f};

// Chams - 0=Glass, 1=Flat, 2=Glow, 3=Latex, 4=Metallic
inline bool g_chams_enabled = true;
inline bool g_chams_visible_only = false;
inline int g_chams_occ_style = 0;
inline float g_chams_occ_color[4] = {0.8f, 0.2f, 1.0f, 1.0f};
inline int g_chams_vis_style = 0;
inline float g_chams_vis_color[4] = {0.2f, 0.8f, 1.0f, 1.0f};

// DirectX / window state — populated by the Present hook on first call
inline bool g_request_unload = false;
inline ID3D11Device* g_device = nullptr;
inline ID3D11DeviceContext* g_device_context = nullptr;
inline ID3D11RenderTargetView* g_render_target = nullptr;
inline HWND g_hWnd = nullptr;
inline WNDPROC g_oWndProc = nullptr;
} // namespace asteria
