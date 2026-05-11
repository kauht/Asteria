#include <windows.h>
#include <string>
#include <vector>
#include <atomic>

namespace globals {
    HMODULE module;

    // States
    std::atomic<bool> bMenuOpen = true;
    std::atomic<bool> bImGuiInitialized = false;
}
