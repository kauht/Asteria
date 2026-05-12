#include "render.hpp"
#include "../menu.hpp"
#include "../ui/ui.hpp"
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include <winuser.h>
#include "../../globals.hpp"
#include "../../utils/utils.hpp"
#include "../../core/hooks/hooks.hpp"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void render::GetDevice() {
    WNDCLASSEX wc{};
    wc.cbSize = sizeof(wc);
    wc.lpfnWndProc = DefWindowProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = "Dummy";
    RegisterClassEx(&wc);

    HWND hWnd = CreateWindowEx(0, wc.lpszClassName, "", WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, nullptr, nullptr, wc.hInstance, nullptr);

    if (!hWnd) {
        io::println("render::GetDevice — failed to create dummy window");
        return;
    }

    DXGI_SWAP_CHAIN_DESC sd{};
    sd.BufferCount = 1;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.Width = 2;
    sd.BufferDesc.Height = 2;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.Windowed = TRUE;

    IDXGISwapChain* pSc = nullptr;
    ID3D11Device* pDev = nullptr;
    ID3D11DeviceContext* pCtx = nullptr;

    D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
    HRESULT hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0,
                                               D3D11_SDK_VERSION, &sd, &pSc, &pDev, &featureLevel, &pCtx);

    if (FAILED(hr)) {
        io::println("render::GetDevice — D3D11CreateDeviceAndSwapChain failed");
        DestroyWindow(hWnd);
        UnregisterClass(wc.lpszClassName, wc.hInstance);
        return;
    }

    hooks::vtables::pSwapChainVTable = *reinterpret_cast<void***>(pSc);

    pSc->Release();
    pDev->Release();
    pCtx->Release();
    DestroyWindow(hWnd);
    UnregisterClass(wc.lpszClassName, wc.hInstance);
    if (!hooks::vtables::pSwapChainVTable) io::println("hooks::Install - pSwapChainVTable is null");
}

void render::CreateRenderTarget() {
    if (!pSwapChain || !pDevice) return;

    ID3D11Texture2D* pBackBuffer = nullptr;
    pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
    pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &pRenderTargetView);
    pBackBuffer->Release();
}

void render::ReleaseRenderTarget() {
    if (!pRenderTargetView) return;
    pRenderTargetView->Release();
    pRenderTargetView = nullptr;
}

void render::Initialize(IDXGISwapChain* swapChain) {
    if (!swapChain || globals::bImGuiInitialized.load()) return;

    pSwapChain = swapChain;
    pSwapChain->GetDevice(__uuidof(ID3D11Device), reinterpret_cast<void**>(&pDevice));

    if (!pDevice) return;

    pDevice->GetImmediateContext(&pDeviceContext);
    if (!pDeviceContext) {
        pDevice->Release();
        pDevice = nullptr;
        return;
    }

    DXGI_SWAP_CHAIN_DESC swapChainDesc{};
    pSwapChain->GetDesc(&swapChainDesc);
    hWnd = swapChainDesc.OutputWindow;

    if (!hWnd) return;

    ImGui::CreateContext();
    ui::SetupStyle();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX11_Init(pDevice, pDeviceContext);

    CreateRenderTarget();
    if (!pRenderTargetView) return;

    oWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtrA(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&hkWndProc)));
    globals::bImGuiInitialized.store(true);
}

void render::Shutdown() {
    if (!globals::bImGuiInitialized.load()) return;
    if (!hWnd || !oWndProc) return;

    SetWindowLongPtrA(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(oWndProc));
    oWndProc = nullptr;

    ReleaseRenderTarget();
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    if (pDeviceContext) pDeviceContext->Release();
    if (pDevice) pDevice->Release();

    pDeviceContext = nullptr;
    pDevice = nullptr;
    pSwapChain = nullptr;
    hWnd = nullptr;
    globals::bImGuiInitialized.store(false);
}

void render::Render() {
    if (!globals::bImGuiInitialized.load() || !pDeviceContext || !pRenderTargetView) return;

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    menu::menu();

    ImGui::Render();

    pDeviceContext->OMSetRenderTargets(1, &pRenderTargetView, nullptr);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    // Restore null RT so the game's pipeline isn't left with our RT bound
    ID3D11RenderTargetView* nullRTV = nullptr;
    pDeviceContext->OMSetRenderTargets(1, &nullRTV, nullptr);
}

HRESULT WINAPI render::hkPresent(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags) {
    if (!globals::bImGuiInitialized.load()) Initialize(swapChain);
    if (globals::bImGuiInitialized.load()) Render();

    return hooks::original::Present.call<HRESULT>(swapChain, syncInterval, flags);
}

HRESULT WINAPI render::hkResizeBuffers(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT flags) {
    if (globals::bImGuiInitialized.load()) ReleaseRenderTarget();

    const HRESULT result = hooks::original::ResizeBuffers.call<HRESULT>(swapChain, bufferCount, width, height, newFormat, flags);
    pSwapChain = swapChain;

    if (globals::bImGuiInitialized.load()) CreateRenderTarget();

    return result;
}

LRESULT CALLBACK render::hkWndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    input::ProcessKey(msg, wParam);
    if (input::KeyDown(VK_INSERT)) globals::bMenuOpen.store(!globals::bMenuOpen.load());

    if (globals::bImGuiInitialized.load() && globals::bMenuOpen.load()) {
        ImGui_ImplWin32_WndProcHandler(wnd, msg, wParam, lParam);
        return TRUE;
    }

    return CallWindowProcA(oWndProc, wnd, msg, wParam, lParam);
}
