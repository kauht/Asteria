#include "d3d11_hook.hpp"
#include <print>
#include <MinHook.h>

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

#include "../rendering/post_process.hpp"
#include "../menu/menu.hpp"
#include "../menu/ui/ui.hpp"
#include "../menu/fonts.hpp"

#pragma comment(lib, "d3d11.lib")

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace hooks
{
    namespace d3d11
    {
        // Function pointers
        typedef HRESULT(__stdcall* Present)(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
        typedef HRESULT(__stdcall* ResizeBuffers)(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
        typedef LRESULT(CALLBACK* WndProc)(HWND, UINT, WPARAM, LPARAM);
        
        Present oPresent = nullptr;
        ResizeBuffers oResizeBuffers = nullptr;
        WndProc oWndProc = nullptr;
        
        // Hooked device objects
        ID3D11Device* g_device = nullptr;
        ID3D11DeviceContext* g_context = nullptr;
        IDXGISwapChain* g_swapchain = nullptr;
        ID3D11RenderTargetView* g_render_target_view = nullptr;
        
        // Post-processing
        rendering::PostProcess g_post_process;
        
        // ImGui state
        bool g_imgui_initialized = false;
        HWND g_hwnd = nullptr;
        
        // Forward declarations
        HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
        HRESULT __stdcall hkResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
        LRESULT CALLBACK hkWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
        
        bool init()
        {
            // Initialize MinHook
            if (MH_Initialize() != MH_OK)
            {
                std::println("[-] Failed to initialize MinHook");
                return false;
            }
            
            // Create dummy device to get Present function address
            D3D_FEATURE_LEVEL featureLevel;
            const D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0 };
            
            DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
            swapChainDesc.BufferCount = 1;
            swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
            swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            swapChainDesc.OutputWindow = GetForegroundWindow();
            swapChainDesc.SampleDesc.Count = 1;
            swapChainDesc.Windowed = TRUE;
            swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
            
            IDXGISwapChain* pSwapChain = nullptr;
            ID3D11Device* pDevice = nullptr;
            ID3D11DeviceContext* pContext = nullptr;
            
            if (FAILED(D3D11CreateDeviceAndSwapChain(
                nullptr,
                D3D_DRIVER_TYPE_HARDWARE,
                nullptr,
                0,
                featureLevels,
                2,
                D3D11_SDK_VERSION,
                &swapChainDesc,
                &pSwapChain,
                &pDevice,
                &featureLevel,
                &pContext)))
            {
                std::println("[-] Failed to create dummy D3D11 device");
                return false;
            }
            
            // Get Present function address from vtable
            void** pSwapChainVTable = *reinterpret_cast<void***>(pSwapChain);
            void* pPresentAddr = pSwapChainVTable[8];  // Present is at index 8
            void* pResizeBuffersAddr = pSwapChainVTable[13];  // ResizeBuffers is at index 13
            
            // Clean up dummy device
            pContext->Release();
            pDevice->Release();
            pSwapChain->Release();
            
            std::println("[+] Present address: 0x{:X}", (uintptr_t)pPresentAddr);
            std::println("[+] ResizeBuffers address: 0x{:X}", (uintptr_t)pResizeBuffersAddr);
            
            // Hook Present
            if (MH_CreateHook(pPresentAddr, &hkPresent, reinterpret_cast<LPVOID*>(&oPresent)) != MH_OK)
            {
                std::println("[-] Failed to create Present hook");
                return false;
            }
            
            // Hook ResizeBuffers
            if (MH_CreateHook(pResizeBuffersAddr, &hkResizeBuffers, reinterpret_cast<LPVOID*>(&oResizeBuffers)) != MH_OK)
            {
                std::println("[-] Failed to create ResizeBuffers hook");
                return false;
            }
            
            // Enable hooks
            if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
            {
                std::println("[-] Failed to enable hooks");
                return false;
            }
            
            std::println("[+] Hooks enabled successfully");
            return true;
        }
        
        void shutdown()
        {
            // Cleanup ImGui
            if (g_imgui_initialized)
            {
                ImGui_ImplDX11_Shutdown();
                ImGui_ImplWin32_Shutdown();
                ImGui::DestroyContext();
                g_imgui_initialized = false;
            }
            
            // Cleanup post-processing
            g_post_process.cleanup();
            
            // Cleanup render target
            if (g_render_target_view)
            {
                g_render_target_view->Release();
                g_render_target_view = nullptr;
            }
            
            // Unhook WndProc
            if (oWndProc && g_hwnd)
            {
                SetWindowLongPtr(g_hwnd, GWLP_WNDPROC, (LONG_PTR)oWndProc);
            }
            
            // Disable and remove hooks
            MH_DisableHook(MH_ALL_HOOKS);
            MH_Uninitialize();
            
            std::println("[+] Hooks disabled");
        }
        
        HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
        {
            // Initialize on first call
            static bool initialized = false;
            if (!initialized)
            {
                std::println("[+] Present hook called for the first time");
                
                // Get device and context
                if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&g_device)))
                {
                    g_device->GetImmediateContext(&g_context);
                    g_swapchain = pSwapChain;
                    
                    std::println("[+] Got D3D11 device and context");
                    
                    // Get window handle
                    DXGI_SWAP_CHAIN_DESC desc;
                    pSwapChain->GetDesc(&desc);
                    g_hwnd = desc.OutputWindow;
                    
                    // Create render target view
                    ID3D11Texture2D* pBackBuffer = nullptr;
                    pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
                    g_device->CreateRenderTargetView(pBackBuffer, nullptr, &g_render_target_view);
                    
                    // Get backbuffer dimensions
                    D3D11_TEXTURE2D_DESC backbuffer_desc;
                    pBackBuffer->GetDesc(&backbuffer_desc);
                    pBackBuffer->Release();
                    
                    std::println("[+] Created render target view ({}x{})", backbuffer_desc.Width, backbuffer_desc.Height);
                    
                    // Initialize post-processing
                    if (g_post_process.init(g_device, backbuffer_desc.Width, backbuffer_desc.Height))
                    {
                        std::println("[+] Post-processing initialized");
                    }
                    
                    // Initialize ImGui
                    IMGUI_CHECKVERSION();
                    ImGui::CreateContext();
                    ImGuiIO& io = ImGui::GetIO();
                    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
                    
                    // Initialize custom style
                    ui::init_style();
                    
                    // Load fonts from byte array
                    fonts::init(io);
                    
                    ImGui_ImplWin32_Init(g_hwnd);
                    ImGui_ImplDX11_Init(g_device, g_context);
                    
                    // Hook WndProc
                    oWndProc = (WndProc)SetWindowLongPtr(g_hwnd, GWLP_WNDPROC, (LONG_PTR)hkWndProc);
                    
                    g_imgui_initialized = true;
                    std::println("[+] ImGui initialized");
                    
                    initialized = true;
                }
            }
            
            if (initialized && g_imgui_initialized && g_context && g_render_target_view)
            {
                // Start ImGui frame
                ImGui_ImplDX11_NewFrame();
                ImGui_ImplWin32_NewFrame();
                ImGui::NewFrame();
                
                // Copy backbuffer to a texture for blurring
                ID3D11Texture2D* pBackBuffer = nullptr;
                pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
                
                // Create a shader resource view of the backbuffer
                ID3D11ShaderResourceView* backbuffer_srv = nullptr;
                g_device->CreateShaderResourceView(pBackBuffer, nullptr, &backbuffer_srv);
                pBackBuffer->Release();
                
                // Apply blur to backbuffer
                ID3D11ShaderResourceView* blurred_srv = g_post_process.apply_blur(g_context, backbuffer_srv, 5.0f, 10);
                
                // Clean up temporary SRV
                if (backbuffer_srv) backbuffer_srv->Release();
                
                // Render menu with blurred background
                menu::render(blurred_srv);
                
                // Render ImGui
                ImGui::Render();
                g_context->OMSetRenderTargets(1, &g_render_target_view, nullptr);
                ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
            }
            
            return oPresent(pSwapChain, SyncInterval, Flags);
        }
        
        HRESULT __stdcall hkResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
        {
            // Release render target before resize
            if (g_render_target_view)
            {
                g_render_target_view->Release();
                g_render_target_view = nullptr;
            }
            
            // Resize post-processing buffers
            if (g_device)
            {
                g_post_process.resize(g_device, Width, Height);
            }
            
            HRESULT result = oResizeBuffers(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
            
            // Recreate render target after resize
            if (SUCCEEDED(result) && g_device)
            {
                ID3D11Texture2D* pBackBuffer = nullptr;
                pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
                g_device->CreateRenderTargetView(pBackBuffer, nullptr, &g_render_target_view);
                pBackBuffer->Release();
            }
            
            return result;
        }
        
        LRESULT CALLBACK hkWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
        {
            if (g_imgui_initialized)
            {
                if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
                    return true;
            }
            
            return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
        }
        
        ID3D11Device* get_device()
        {
            return g_device;
        }
        
        ID3D11DeviceContext* get_context()
        {
            return g_context;
        }
        
        IDXGISwapChain* get_swapchain()
        {
            return g_swapchain;
        }
    }
}
