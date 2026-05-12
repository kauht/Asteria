#pragma once

#include <windows.h>
#include <dxgi.h>
#include <d3d11.h>
#include <imgui.h>

namespace render {

    void GetDevice();

    void CreateRenderTarget();
    void ReleaseRenderTarget();

    void Initialize(IDXGISwapChain* pSwapChain);
    void Shutdown();

    void Render();

    // Render hooks
    HRESULT WINAPI hkPresent(IDXGISwapChain* pSwapChain, UINT syncInterval, UINT flags);
    HRESULT WINAPI hkResizeBuffers(IDXGISwapChain* pSwapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT flags);
    LRESULT CALLBACK hkWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    inline IDXGISwapChain*         pSwapChain{};
    inline ID3D11Device*           pDevice{};
    inline ID3D11DeviceContext*    pDeviceContext{};
    inline ID3D11RenderTargetView* pRenderTargetView{};
    inline HWND                    hWnd{};
    inline WNDPROC                 oWndProc{};
}
