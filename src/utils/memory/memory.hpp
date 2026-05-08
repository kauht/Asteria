#pragma once
#include <windows.h>
#include <string>

namespace memory {
    uintptr_t FindPattern(const std::string_view& pattern, const uintptr_t module_base);
}
