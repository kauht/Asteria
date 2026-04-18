#pragma once

#include <dxgi.h>

namespace asteria::core::render {
void on_present(IDXGISwapChain* pSwapChain);
void shutdown();

} // namespace asteria::core::render
