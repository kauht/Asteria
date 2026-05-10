#pragma once
#include <windows.h>
#include <unordered_map>

namespace input {
    inline std::unordered_map<int, bool> key_states;
    inline bool running = true;

    void Initialize();
    void Shutdown();
    bool KeyDown(int key);
    void ProcessKey();
}
