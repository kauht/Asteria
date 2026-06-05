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

    template <typename T>
    inline T* GetInterface(HMODULE mod, const char* name) noexcept {
        if (!mod) return nullptr;
        using CreateInterfaceFn = void*(__cdecl*)(const char*, int*);
        auto CreateInterface = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(mod, "CreateInterface"));
        if (!CreateInterface) return nullptr;
        return static_cast<T*>(CreateInterface(name, nullptr));
    }

}
