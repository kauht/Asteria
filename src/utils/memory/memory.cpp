#include "memory.hpp"
#include <windows.h>
#include <vector>
#include <sstream>
#include <iomanip>

uintptr_t memory::FindPattern(const std::string_view& pattern, const HMODULE module_base) {
    if (!module_base) return 0;

    auto* base = reinterpret_cast<std::uint8_t*>(module_base);

    const auto dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(base);
    if (dos_header->e_magic != IMAGE_DOS_SIGNATURE) return 0;

    const auto nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<std::uint8_t*>(dos_header) + dos_header->e_lfanew);
    if (nt_headers->Signature != IMAGE_NT_SIGNATURE) return 0;

    const size_t size = nt_headers->OptionalHeader.SizeOfImage;

    std::vector<int> bytes;
    {
        std::stringstream ss;
        ss << pattern;
        std::string word;
        while (ss >> word) {
            if (word == "?" || word == "??") {
                bytes.push_back(-1);
            } else {
                try {
                    bytes.push_back(static_cast<int>(std::stoul(word, nullptr, 16)));
                } catch (...) {
                    continue;
                }
            }
        }
    }

    if (bytes.empty()) return 0;

    const size_t pattern_size = bytes.size();
    const int* pattern_data = bytes.data();

    for (size_t i = 0; i <= size - pattern_size; ++i) {
        bool found = true;
        for (size_t j = 0; j < pattern_size; ++j) {
            if (pattern_data[j] != -1 && base[i + j] != static_cast<uint8_t>(pattern_data[j])) {
                found = false;
                break;
            }
        }
        if (found) {
            return reinterpret_cast<uintptr_t>(base + i);
        }
    }
    return 0;
}

// RTTI-based vtable finder — scans .rdata for the RTTI Complete Object Locator
// that references the given class name, then returns the associated vtable pointer.
void** memory::FindVTable(const char* module_name, const char* rtti_name) {
    auto* hMod = GetModuleHandleA(module_name);
    if (!hMod) return nullptr;

    auto* base = reinterpret_cast<uint8_t*>(hMod);
    auto* dos = reinterpret_cast<PIMAGE_DOS_HEADER>(base);
    auto* nt = reinterpret_cast<PIMAGE_NT_HEADERS>(base + dos->e_lfanew);

    auto* rdata_sec = IMAGE_FIRST_SECTION(nt);
    uintptr_t rdata_start = 0, rdata_end = 0;
    for (WORD i = 0; i < nt->FileHeader.NumberOfSections; ++i) {
        if (std::string(reinterpret_cast<char*>(rdata_sec[i].Name)) == ".rdata") {
            rdata_start = reinterpret_cast<uintptr_t>(base + rdata_sec[i].VirtualAddress);
            rdata_end = rdata_start + rdata_sec[i].Misc.VirtualSize;
            break;
        }
    }
    if (!rdata_start) return nullptr;

    // Search for the RTTI name string
    size_t name_len = strlen(rtti_name);
    for (uintptr_t p = rdata_start; p < rdata_end - name_len; ++p) {
        if (memcmp(reinterpret_cast<void*>(p), rtti_name, name_len) == 0) {
            // Found the name. The RTTI Complete Object Locator is typically
            // 0x10 bytes before the name in MSVC RTTI layout.
            // The vtable pointer is typically 0x10 bytes before the COL.
            uintptr_t rtti_col = p - 0x10;
            uintptr_t vtable_ptr = rtti_col - 0x10;

            // Verify it looks like a vtable (pointer in .rdata or .text)
            auto candidate = *reinterpret_cast<uintptr_t*>(vtable_ptr);
            if (candidate >= (uintptr_t)base && candidate < (uintptr_t)base + nt->OptionalHeader.SizeOfImage) {
                return reinterpret_cast<void**>(candidate);
            }
        }
    }
    return nullptr;
}
