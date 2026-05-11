#include "render.hpp"
#include "imgui.h"
#include <basetsd.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include <winuser.h>
#include "../../globals.hpp"

void render::Initialize() {

}

void render::Shutdown() {

}

void render::CreateRenderTarget() {
    if (!pSwapChain || !pDevice) return;

    ID3D11Texture2D* pBackBuffer;
    pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
    pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &pRenderTargetView);
    pBackBuffer->Release();
}

void render::ReleaseRenderTarget() {
    if (pRenderTargetView) return;
    pRenderTargetView->Release();
    pRenderTargetView = nullptr;
}

void render::InitializeImGui(IDXGISwapChain *pSwapChain) {
    pSwapChain->GetDevice(__uuidof(ID3D11Device), reinterpret_cast<void**>(&pDevice));
    pDevice->GetImmediateContext(&pDeviceContext);

    CreateRenderTarget();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

    DXGI_SWAP_CHAIN_DESC swapChainDesc;
    pSwapChain->GetDesc(&swapChainDesc);
    // use swapchains output window
    hWnd = swapChainDesc.OutputWindow;

    oWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtrA(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&hkWndProc)));
    globals::bImGuiInitialized.exchange(true);
}

void render::ShutdownImGui() {
    if (!pDeviceContext || !pDevice || !globals::bImGuiInitialized) return;

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    ReleaseRenderTarget();
    pDeviceContext->Release();
    pDevice->Release();
    globals::bImGuiInitialized.exchange(false);

}

void render::Render() {

}
