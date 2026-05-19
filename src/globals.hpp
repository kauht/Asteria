#pragma once
#include <windows.h>
#include <string>
#include <vector>
#include <atomic>

namespace globals {
    inline HMODULE module;

    // States
    inline std::atomic<bool> bMenuOpen = true;
    inline std::atomic<bool> bImGuiInitialized = false;


    inline bool bTest = false;
}
