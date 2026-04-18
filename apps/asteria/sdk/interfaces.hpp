#pragma once

#include <cstdint>
#include <windows.h>
/// ! CAUTION | AI GENERATED | NEEDS MANUAL REVIEW !

// Helpers for resolving game interfaces and RIP-relative addresses.

namespace asteria::sdk {

// Calls CreateInterface on a loaded module to get a named interface pointer.
// e.g. get_interface("client.dll", "Source2Client001")
inline void* get_interface(const char* module_name, const char* interface_name) {
    HMODULE mod = GetModuleHandleA(module_name);
    if (!mod) return nullptr;
    using Fn = void* (*)(const char*, int*);
    auto fn = reinterpret_cast<Fn>(GetProcAddress(mod, "CreateInterface"));
    return fn ? fn(interface_name, nullptr) : nullptr;
}

// Resolves a RIP-relative address from a pattern match result.
// Most patterns like "48 8B 0D [rel32]" use offset=3, size=7.
inline uintptr_t resolve_rip(uintptr_t addr, int rel_offset = 3, int insn_size = 7) {
    int32_t rel = *reinterpret_cast<int32_t*>(addr + rel_offset);
    return addr + insn_size + rel;
}

} // namespace asteria::sdk
