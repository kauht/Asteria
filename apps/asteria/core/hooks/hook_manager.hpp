#pragma once

#include "present.hpp"
#include "generate_primitives.hpp"
#include "../../util/logger.hpp"
#include "../../globals.hpp"

namespace asteria::core::hooks {

inline bool install() {
    void* present_addr = find_present_addr();
    if (!present_addr) {
        asteria::util::error("Hooks: failed to find Present.");
        return false;
    }

    g_present_hook = safetyhook::create_inline(present_addr, reinterpret_cast<void*>(hk_present));
    if (!g_present_hook) {
        asteria::util::error("Hooks: failed to install Present hook.");
        return false;
    }

    if (!install_generate_primitives_hook()) return false;

    asteria::util::info("Hooks: all installed.");
    return true;
}

inline void uninstall() {
    uninstall_generate_primitives_hook();
    g_present_hook.reset();

    if (asteria::g_oWndProc && asteria::g_hWnd) SetWindowLongPtr(asteria::g_hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(asteria::g_oWndProc));

    asteria::util::info("Hooks: all removed.");
}

} // namespace asteria::core::hooks
