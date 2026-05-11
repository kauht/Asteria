#include <dxgi.h>
#include <d3d11.h>
#include <imgui.h>

namespace render {
    void Initialize();
    void Shutdown();

    void CreateRenderTarget();
    void ReleaseRenderTarget();

    void InitializeImGui(IDXGISwapChain* pSwapChain);
    void ShutdownImGui();

    void Render();

    // Render Hooks
    HRESULT WINAPI hkPresent(IDXGISwapChain* pSwapChain, UINT syncInterval, UINT flags);
    //
    HRESULT WINAPI hkResizeBuffers(IDXGISwapChain* pSwapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT flags);
    // WndProc subclass forwards to imgui to block game input
    LRESULT CALLBACK hkWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    // inline vars
    inline IDXGISwapChain* pSwapChain{};
    inline ID3D11Device* pDevice{};
    inline ID3D11DeviceContext* pDeviceContext{};
    inline ID3D11RenderTargetView* pRenderTargetView{};
    inline HWND hWnd{}; // game window
    inline WNDPROC oWndProc{};
}
