#pragma once
#include <windows.h>
#include <unordered_map>

namespace input {
    inline std::unordered_map<int, bool> key_states;

    bool KeyDown(int key);

    bool WasPressed(int key);

    void ProcessKey(UINT msg, WPARAM wParam);

    void SetRelativeMouse(bool relative);
}
