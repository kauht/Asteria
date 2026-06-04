#pragma once
#include <windows.h>
#include <cstdint>

namespace sdk {

    template <typename T>
    inline T* GlobalPtr(HMODULE mod, std::ptrdiff_t offset) noexcept {
        if (!mod) return nullptr;
        return *reinterpret_cast<T**>(reinterpret_cast<std::uintptr_t>(mod) + offset);
    }

    template <typename T>
    inline T* GlobalAt(HMODULE mod, std::ptrdiff_t offset) noexcept {
        if (!mod) return nullptr;
        return reinterpret_cast<T*>(reinterpret_cast<std::uintptr_t>(mod) + offset);
    }

}
