#include "render.hpp"
#include "../menu.hpp"
#include "../../globals.hpp"
#include "../../utils/utils.hpp"
#include "../../core/hooks/hooks.hpp"
#include "zscene/zscene.hpp"
#include <d3d11.h>
#include <zdraw.hpp>
#include <zui/zui.hpp>
#include <zscene/zscene.hpp>

long long __stdcall render::WndProc_Handler( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam )
	{
		zui::process_wndproc_message( msg, wparam, lparam );

		if (msg == WM_SETCURSOR) {
			SetCursor( LoadCursorA( nullptr, IDC_ARROW ) );
			return TRUE;
		}

		// @note: could move these to process_wndproc_message

		if ( msg == WM_SIZE && wparam != SIZE_MINIMIZED )
			resize( LOWORD( lparam ), HIWORD( lparam ) );

		if ( msg == WM_DESTROY )
			PostQuitMessage( 0 );

		return DefWindowProcW( hwnd, msg, wparam, lparam );
	}

void render::GetDevice() {
    WNDCLASSEX wc{};
    wc.cbSize = sizeof(wc);
    wc.lpfnWndProc = DefWindowProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = "Dummy";
    RegisterClassEx(&wc);

    HWND hWnd = CreateWindowEx(0, wc.lpszClassName, "", WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, nullptr, nullptr, wc.hInstance, nullptr);

    if (!hWnd) {
        io::println("couldn't to create window");
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
        io::println("create device and swap chain failed");
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

    DXGI_SWAP_CHAIN_DESC swapChainDesc{};
    pSwapChain->GetDesc(&swapChainDesc);
    hWnd = swapChainDesc.OutputWindow;
    view_width  = swapChainDesc.BufferDesc.Width;
    view_height = swapChainDesc.BufferDesc.Height;

    if (!zdraw::initialize(pDevice, pDeviceContext)) return;
    if (!zui::initialize(hWnd)) return;

    input::SetRelativeMouse(!globals::bMenuOpen.load());
    // create context

    scene.initialize(pDevice, pDeviceContext, view_width, view_height);
    scene.set_orientation(zscene::orientation::z_up);
    scene.set_clear_color(0.f, 0.f, 0.f);
    scene.play();


    CreateRenderTarget();

    oWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtrA(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&hkWndProc)));
    globals::bImGuiInitialized.store(true);
}

void render::Shutdown() {
    if (!globals::bImGuiInitialized.load()) return;
    if (!hWnd || !oWndProc) return;

    scene.shutdown();

    SetWindowLongPtrA(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(oWndProc));
    oWndProc = nullptr;

    ReleaseRenderTarget();

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

    D3D11_VIEWPORT vp;
    vp.Width = static_cast<float>(view_width);
    vp.Height = static_cast<float>(view_height);
    vp.MinDepth = 0.f;
    vp.MaxDepth = 1.f;
    vp.TopLeftX = 0.f;
    vp.TopLeftY = 0.f;
    pDeviceContext->RSSetViewports(1, &vp);

    pDeviceContext->OMSetRenderTargets(1, &pRenderTargetView, nullptr);

    zdraw::begin_frame();
    if (globals::bMenuOpen.load()) menu::menu();
    zdraw::end_frame();

    // Restore null render target
    ID3D11RenderTargetView* nullRTV = nullptr;
    pDeviceContext->OMSetRenderTargets(1, &nullRTV, nullptr);
}

void render::resize(unsigned int width, unsigned int height) {
    view_width = width;
    view_height = height;

    if (globals::bImGuiInitialized.load()) {
        ReleaseRenderTarget();
        CreateRenderTarget();
    }
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

    view_width = width;
    view_height = height;

    return result;
}

LRESULT CALLBACK render::hkWndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    input::ProcessKey(msg, wParam);
    if (input::WasPressed(config::g_config.keybinds["toggle_menu"].key)) {
        const bool open = !globals::bMenuOpen.load();
        globals::bMenuOpen.store(open);
        input::SetRelativeMouse(!open);
    }

    if (globals::bImGuiInitialized.load() && globals::bMenuOpen.load()) {
        return WndProc_Handler(wnd, msg, wParam, lParam);
    }

    return CallWindowProcA(oWndProc, wnd, msg, wParam, lParam);
}
