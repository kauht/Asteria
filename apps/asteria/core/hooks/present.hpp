#pragma once

#include <dxgi.h>
#include <d3d11.h>
#include <safetyhook.hpp>

namespace asteria::core::hooks {

extern SafetyHookInline g_present_hook;

HRESULT __stdcall hk_present(IDXGISwapChain* swapchain, UINT sync_interval, UINT flags);

// Finds the Present function address by creating a temporary DX11 swapchain
// and reading vtable[8]. Avoids hardcoded offsets.
void* find_present_addr();

} // namespace asteria::core::hooks
