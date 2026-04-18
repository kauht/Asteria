#include "render.hpp"
#include "menu.hpp"
#include "shaders/blur.hpp"
#include "../../globals.hpp"
#include "../hooks/wndproc.hpp"

#include <d3d11.h>
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

namespace asteria::core::render {

void on_present(IDXGISwapChain* swapchain) {
    if (!asteria::g_imgui_init) {
        if (swapchain->GetDevice(__uuidof(ID3D11Device), reinterpret_cast<void**>(&asteria::g_device)) < 0) return;

        asteria::g_device->GetImmediateContext(&asteria::g_device_context);

        DXGI_SWAP_CHAIN_DESC sd;
        swapchain->GetDesc(&sd);
        asteria::g_hWnd = sd.OutputWindow;

        ID3D11Texture2D* back_buffer = nullptr;
        swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&back_buffer));
        if (back_buffer) {
            asteria::g_device->CreateRenderTargetView(back_buffer, nullptr, &asteria::g_render_target);
            back_buffer->Release();
        }

        asteria::g_oWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(asteria::g_hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(asteria::core::hooks::hk_wnd_proc)));

        ImGui::CreateContext();
        ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        ImGui::GetIO().ConfigWindowsMoveFromTitleBarOnly = true;

        menu::setup_style();

        ImGui_ImplWin32_Init(asteria::g_hWnd);
        ImGui_ImplDX11_Init(asteria::g_device, asteria::g_device_context);

        shaders::blur::init(asteria::g_device, swapchain);

        asteria::g_imgui_init = true;
    }

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    shaders::blur::begin_frame(asteria::g_device_context, swapchain);

    menu::draw();

    ImGui::Render();
    if (asteria::g_render_target) {
        asteria::g_device_context->OMSetRenderTargets(1, &asteria::g_render_target, nullptr);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    }
}

void shutdown() {
    shaders::blur::shutdown();

    if (asteria::g_imgui_init) {
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
        asteria::g_imgui_init = false;
    }

    if (asteria::g_render_target) asteria::g_render_target->Release();
    if (asteria::g_device_context) asteria::g_device_context->Release();
    if (asteria::g_device) asteria::g_device->Release();
}

} // namespace asteria::core::render
