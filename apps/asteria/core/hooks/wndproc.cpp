#include "wndproc.hpp"
#include "../../globals.hpp"

#include <imgui.h>
#include <imgui_impl_win32.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);

namespace asteria::core::hooks {

LRESULT __stdcall hk_wnd_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    if (msg == WM_KEYDOWN && wparam == VK_INSERT) {
        asteria::g_show_menu = !asteria::g_show_menu;
        return TRUE;
    }

    if (asteria::g_imgui_init && asteria::g_show_menu) {
        ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam);
        if ((msg >= WM_MOUSEFIRST && msg <= WM_MOUSELAST) || (msg >= WM_KEYFIRST && msg <= WM_KEYLAST)) return TRUE;
    }

    return CallWindowProc(asteria::g_oWndProc, hwnd, msg, wparam, lparam);
}

} // namespace asteria::core::hooks
