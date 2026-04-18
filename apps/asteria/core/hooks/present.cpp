#include "present.hpp"
#include "../render/render.hpp"

#include <windows.h>

namespace asteria::core::hooks {

SafetyHookInline g_present_hook;

void* find_present_addr() {
    WNDCLASSEXA wc{sizeof(wc), CS_CLASSDC, DefWindowProcA, 0, 0, GetModuleHandleA(nullptr)};
    wc.lpszClassName = "asteria_dummy";
    RegisterClassExA(&wc);

    HWND hwnd = CreateWindowA(wc.lpszClassName, "", WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, nullptr, nullptr, wc.hInstance, nullptr);
    if (!hwnd) {
        UnregisterClassA(wc.lpszClassName, wc.hInstance);
        return nullptr;
    }

    DXGI_SWAP_CHAIN_DESC sd{};
    sd.BufferCount = 1;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hwnd;
    sd.SampleDesc.Count = 1;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    IDXGISwapChain* swapchain = nullptr;
    ID3D11Device* device = nullptr;
    ID3D11DeviceContext* context = nullptr;
    void* addr = nullptr;

    if (SUCCEEDED(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &sd, &swapchain, &device, nullptr, &context))) {
        addr = (*reinterpret_cast<void***>(swapchain))[8]; // vtable[8] = Present
        swapchain->Release();
        context->Release();
        device->Release();
    }

    DestroyWindow(hwnd);
    UnregisterClassA(wc.lpszClassName, wc.hInstance);
    return addr;
}

HRESULT __stdcall hk_present(IDXGISwapChain* swapchain, UINT sync_interval, UINT flags) {
    asteria::core::render::on_present(swapchain);
    return g_present_hook.call<HRESULT>(swapchain, sync_interval, flags);
}

} // namespace asteria::core::hooks
