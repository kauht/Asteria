#pragma once

#include <windows.h>

namespace asteria::core::hooks {
LRESULT __stdcall hk_wnd_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
}
