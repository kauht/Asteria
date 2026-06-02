#include "input.hpp"
#include <thread>
#include "../io/io.hpp"
#include "../modules/modules.hpp"
#include "../../globals.hpp"
#include <cs2.hpp>
#include <safetyhook.hpp>

bool input::KeyDown(int key) {
    return key_states[key];
}

bool input::WasPressed(int key) {
    static std::unordered_map<int, bool> s_prev;
    const bool down    = key_states[key];
    const bool pressed = down && !s_prev[key];
    s_prev[key] = down;
    return pressed;
}

void input::ProcessKey(UINT msg, WPARAM wParam) {
    // If you think there's a better way to do this then fucking do it fuck you
    switch (msg) {
        case WM_KEYDOWN: case WM_SYSKEYDOWN: key_states[static_cast<int>(wParam)] = true;  break;
        case WM_KEYUP:   case WM_SYSKEYUP:   key_states[static_cast<int>(wParam)] = false; break;
        case WM_LBUTTONDOWN: key_states[VK_LBUTTON] = true;  break;
        case WM_LBUTTONUP:   key_states[VK_LBUTTON] = false; break;
        case WM_RBUTTONDOWN: key_states[VK_RBUTTON] = true;  break;
        case WM_RBUTTONUP:   key_states[VK_RBUTTON] = false; break;
        case WM_MBUTTONDOWN: key_states[VK_MBUTTON] = true;  break;
        case WM_MBUTTONUP:   key_states[VK_MBUTTON] = false; break;
        case WM_XBUTTONDOWN: key_states[HIWORD(wParam) == XBUTTON1 ? VK_XBUTTON1 : VK_XBUTTON2] = true;  break;
        case WM_XBUTTONUP:   key_states[HIWORD(wParam) == XBUTTON1 ? VK_XBUTTON1 : VK_XBUTTON2] = false; break;
        default: break;
    }
}

namespace {
    SafetyHookInline g_set_relative_hook{};

    ifc::inputsystem::CInputSystem* InputSystem() {
        static void* is = [] {
            using CreateInterfaceFn = void*(__cdecl*)(const char*, int*);
            auto ci = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(modules::inputsystem, "CreateInterface"));
            return ci("InputSystemVersion001", nullptr);
        }();
        return static_cast<ifc::inputsystem::CInputSystem*>(is);
    }

    void* __fastcall hkSetRelativeMouseMode(void* thisptr, bool relative) {
        return g_set_relative_hook.fastcall<void*>(thisptr, globals::bMenuOpen.load() ? false : relative);
    }
}

void input::SetRelativeMouse(bool relative) {
    auto* is = InputSystem();
    if (!is) return;
    if (!g_set_relative_hook) {
        // fix later
        if (void* target = ifc::detail::vfunc(is, &ifc::inputsystem::CInputSystem::SetRelativeMouseMode))
            g_set_relative_hook = safetyhook::create_inline(target, &hkSetRelativeMouseMode);
    }
    is->SetRelativeMouseMode(relative);
}
