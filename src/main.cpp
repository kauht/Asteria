#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_internal.h>
#include <imgui_impl_win32.h>
#include <print>
#include <d3d11.h>
#include <windowsx.h>
#include <dwmapi.h>

#pragma comment(lib, "dwmapi.lib")

#include "menu/menu.hpp"
#include "menu/ui/ui.hpp"
#include "menu/ui/fonts.hpp"
#include "rendering/blur.hpp"
#include "rendering/desktop_capture.hpp"

static ID3D11Device*            g_device    = nullptr;
static ID3D11DeviceContext*     g_ctx       = nullptr;
static IDXGISwapChain*          g_swapChain = nullptr;
static ID3D11RenderTargetView*  g_rtv       = nullptr;
static HWND                     g_hwnd      = nullptr;
static WNDCLASSEXW              g_wc        = {};
static int                      g_window_width = 1050;
static int                      g_window_height = 750;

// Export device for icon loading
ID3D11Device* g_device_export = nullptr;

// Blur and desktop capture
static rendering::GaussianBlur g_blur;
static rendering::DesktopCapture g_desktop_capture;
static ID3D11ShaderResourceView* g_blurred_background = nullptr;
static POINT g_last_window_pos = {-1, -1};

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);

static bool g_dragging = false;
static POINT g_drag_start = {};
static bool g_drag_moved = false;
static bool g_needs_recapture = false;  // Flag to recapture after drag ends

static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    // Handle dragging BEFORE ImGui for mouse move, AFTER for button events
    if (msg == WM_MOUSEMOVE && g_dragging)
    {
        POINT pt;
        GetCursorPos(&pt);
        
        // Check if we've moved enough to consider it a drag (not just a click)
        int dx = pt.x - g_drag_start.x;
        int dy = pt.y - g_drag_start.y;
        if (abs(dx) > 2 || abs(dy) > 2)
        {
            g_drag_moved = true;
        }
        
        if (g_drag_moved)
        {
            RECT rect;
            GetWindowRect(hWnd, &rect);
            
            SetWindowPos(hWnd, nullptr,
                rect.left + dx,
                rect.top + dy,
                0, 0,
                SWP_NOSIZE | SWP_NOZORDER);
            
            g_drag_start = pt;
            return 0;
        }
    }
    
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam)) return true;
    
    switch (msg)
    {
        case WM_LBUTTONDOWN:
        {
            // Check if click is in top bar area
            POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
            if (pt.y < 75) // Top bar height with DPI scale
            {
                GetCursorPos(&g_drag_start);
                g_dragging = true;
                g_drag_moved = false;
                SetCapture(hWnd);
            }
            break;
        }
        
        case WM_LBUTTONUP:
        {
            if (g_dragging)
            {
                g_dragging = false;
                g_needs_recapture = g_drag_moved;  // Only recapture if we actually moved
                g_drag_moved = false;
                ReleaseCapture();
                
                // If we didn't actually drag, let ImGui handle it as a click
                if (!g_needs_recapture)
                {
                    // Re-send the event to ImGui
                    return ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam) ? 0 : DefWindowProcW(hWnd, msg, wParam, lParam);
                }
                return 0;
            }
            break;
        }
        
        case WM_DESTROY:
        {
            ::PostQuitMessage(0);
            return 0;
        }
    }
    
    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}

bool Setup()
{
    g_wc = { sizeof(g_wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"Asteria", nullptr };
    ::RegisterClassExW(&g_wc);
    
    // Create a layered window for transparency
    g_hwnd = ::CreateWindowExW(
        WS_EX_LAYERED,  // Layered for transparency
        g_wc.lpszClassName,
        L"Asteria",
        WS_POPUP,  // Popup style = no title bar, no borders
        100, 100, g_window_width, g_window_height,
        nullptr, nullptr, g_wc.hInstance, nullptr
    );

    DXGI_SWAP_CHAIN_DESC sd     = {};
    sd.BufferCount              = 2;
    sd.BufferDesc.Width         = g_window_width;
    sd.BufferDesc.Height        = g_window_height;
    sd.BufferDesc.Format        = DXGI_FORMAT_B8G8R8A8_UNORM;  // BGRA for proper alpha
    sd.BufferUsage              = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow             = g_hwnd;
    sd.SampleDesc.Count         = 1;
    sd.Windowed                 = TRUE;
    sd.SwapEffect               = DXGI_SWAP_EFFECT_DISCARD;  // Use discard for layered windows
    sd.Flags                    = 0;

    const D3D_FEATURE_LEVEL levels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0 };
    D3D_FEATURE_LEVEL featureLevel;
    if (D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0,
        levels, 2, D3D11_SDK_VERSION, &sd, &g_swapChain, &g_device, &featureLevel, &g_ctx) != S_OK)
        return false;
    
    g_device_export = g_device;  // Export for icon loading

    ID3D11Texture2D* backbuffer = nullptr;
    g_swapChain->GetBuffer(0, IID_PPV_ARGS(&backbuffer));
    g_device->CreateRenderTargetView(backbuffer, nullptr, &g_rtv);
    backbuffer->Release();

    ::ShowWindow(g_hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(g_hwnd);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    
    // Initialize custom style
    ui::init_style();
    
    // Load fonts
    ui::fonts::init(io);
    
    ImGui_ImplWin32_Init(g_hwnd);
    ImGui_ImplDX11_Init(g_device, g_ctx);
    
    // Initialize blur and desktop capture
    g_blur.init(g_device, g_window_width, g_window_height);
    g_desktop_capture.init(g_device, g_hwnd, g_window_width, g_window_height);

    return true;
}

void Cleanup()
{
    g_blur.cleanup();
    g_desktop_capture.cleanup();
    
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    if (g_rtv)       { g_rtv->Release();      g_rtv       = nullptr; }
    if (g_swapChain) { g_swapChain->Release(); g_swapChain = nullptr; }
    if (g_ctx)       { g_ctx->Release();       g_ctx       = nullptr; }
    if (g_device)    { g_device->Release();    g_device    = nullptr; }

    ::DestroyWindow(g_hwnd);
    ::UnregisterClassW(g_wc.lpszClassName, g_wc.hInstance);
}

int main(int, char**)
{
    if (!Setup()) return 1;

    // Create a memory DC for UpdateLayeredWindow
    HDC hdc_screen = GetDC(nullptr);
    HDC hdc_mem = CreateCompatibleDC(hdc_screen);
    HBITMAP hbm_mem = CreateCompatibleBitmap(hdc_screen, g_window_width, g_window_height);
    HBITMAP hbm_old = (HBITMAP)SelectObject(hdc_mem, hbm_mem);

    bool done = false;
    while (!done)
    {
        MSG msg;
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT) done = true;
        }
        if (done) break;

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        // Capture and blur on first frame or after drag ends
        static bool first_frame = true;
        if (first_frame || g_needs_recapture)
        {
            // Hide window temporarily before capturing
            ShowWindow(g_hwnd, SW_HIDE);
            
            // Small delay to ensure window is hidden
            Sleep(10);
            
            // Recapture and blur
            ID3D11ShaderResourceView* desktop_srv = g_desktop_capture.capture();
            g_blurred_background = g_blur.apply(g_ctx, desktop_srv);
            first_frame = false;
            g_needs_recapture = false;
            
            // Show window again
            ShowWindow(g_hwnd, SW_SHOW);
        }

        menu::render(g_blurred_background);  // Pass blurred background to menu

        // Render with transparency
        constexpr float clear[4] = { 0.0f, 0.0f, 0.0f, 0.0f };  // Transparent clear
        g_ctx->OMSetRenderTargets(1, &g_rtv, nullptr);
        g_ctx->ClearRenderTargetView(g_rtv, clear);
        
        // Draw ImGui
        ImGui::Render();
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        
        // Copy backbuffer to system memory for UpdateLayeredWindow
        ID3D11Texture2D* backbuffer = nullptr;
        g_swapChain->GetBuffer(0, IID_PPV_ARGS(&backbuffer));
        
        D3D11_TEXTURE2D_DESC desc;
        backbuffer->GetDesc(&desc);
        desc.Usage = D3D11_USAGE_STAGING;
        desc.BindFlags = 0;
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
        
        ID3D11Texture2D* staging_texture = nullptr;
        g_device->CreateTexture2D(&desc, nullptr, &staging_texture);
        g_ctx->CopyResource(staging_texture, backbuffer);
        
        D3D11_MAPPED_SUBRESOURCE mapped;
        g_ctx->Map(staging_texture, 0, D3D11_MAP_READ, 0, &mapped);
        
        // Create bitmap from mapped data - need to handle row pitch correctly
        BITMAPINFO bmi = {};
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = g_window_width;
        bmi.bmiHeader.biHeight = -g_window_height;  // Top-down
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biCompression = BI_RGB;
        
        // Copy row by row to handle pitch correctly
        unsigned char* temp_buffer = new unsigned char[g_window_width * g_window_height * 4];
        for (int y = 0; y < g_window_height; y++)
        {
            memcpy(
                temp_buffer + y * g_window_width * 4,
                (unsigned char*)mapped.pData + y * mapped.RowPitch,
                g_window_width * 4
            );
        }
        
        SetDIBitsToDevice(hdc_mem, 0, 0, g_window_width, g_window_height,
            0, 0, 0, g_window_height, temp_buffer, &bmi, DIB_RGB_COLORS);
        
        delete[] temp_buffer;
        
        g_ctx->Unmap(staging_texture, 0);
        staging_texture->Release();
        backbuffer->Release();
        
        // Update layered window with alpha
        POINT pt_src = { 0, 0 };
        SIZE size = { g_window_width, g_window_height };
        BLENDFUNCTION blend = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
        
        POINT pt_dst;
        RECT rect;
        GetWindowRect(g_hwnd, &rect);
        pt_dst.x = rect.left;
        pt_dst.y = rect.top;
        
        UpdateLayeredWindow(g_hwnd, hdc_screen, &pt_dst, &size, hdc_mem, &pt_src, 0, &blend, ULW_ALPHA);
    }

    SelectObject(hdc_mem, hbm_old);
    DeleteObject(hbm_mem);
    DeleteDC(hdc_mem);
    ReleaseDC(nullptr, hdc_screen);

    Cleanup();
    return 0;
}
