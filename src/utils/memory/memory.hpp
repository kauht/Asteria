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

    uintptr_t ResolveRelativeAddress(uintptr_t address, int offset, int instruction_size);

    inline bool IsBadReadPtr(void* p, size_t size) {
        if (!p) return true;
        MEMORY_BASIC_INFORMATION mbi;
        if (VirtualQuery(p, &mbi, sizeof(mbi)) == 0) return true;
        if (mbi.State != MEM_COMMIT) return true;
        if (mbi.Protect == PAGE_NOACCESS || mbi.Protect == PAGE_GUARD) return true;
        return false;
    }
}
