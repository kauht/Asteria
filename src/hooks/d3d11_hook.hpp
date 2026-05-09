#pragma once

#include <d3d11.h>
#include <dxgi.h>

namespace hooks
{
    namespace d3d11
    {
        // Initialize D3D11 hooks
        bool init();
        
        // Shutdown and unhook
        void shutdown();
        
        // Get hooked device and context
        ID3D11Device* get_device();
        ID3D11DeviceContext* get_context();
        IDXGISwapChain* get_swapchain();
    }
}
