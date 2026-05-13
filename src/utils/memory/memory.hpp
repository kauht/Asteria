#pragma once
#include <windows.h>
#include <string>

namespace memory {
    uintptr_t FindPattern(const std::string_view& pattern, const HMODULE module_base);

    template <typename T = void*>
    T GetVTableMethod(uintptr_t base, size_t index) {
        auto vtable = *reinterpret_cast<uintptr_t**>(base);
        return reinterpret_cast<T>(vtable[index]);
    }

}
