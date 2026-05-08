#include "memory.hpp"
#include <windows.h>
#include <Psapi.h>
#include <vector>
#include <charconv>

uintptr_t memory::FindPattern(const std::string_view& pattern, const uintptr_t module_base) {
    auto* base = reinterpret_cast<std::uint8_t*>(module_base);

    MODULEINFO info{};
    GetModuleInformation(GetCurrentProcess(), reinterpret_cast<HMODULE>(module_base), &info, sizeof(info));
    size_t size = info.SizeOfImage;

    struct byte_entry {
        uint8_t byte;
        bool wildcard;
    };
    std::vector<byte_entry> bytes;

    for (size_t i = 0; i < pattern.size();) {
        if (pattern[i] == ' ') {
            ++i;
            continue;
        }

        // "??" or "?"
        if (pattern[i] == '?') {
            bytes.push_back({ 0, true });
            // Skip "??" or "?"
            i += (i + 1 < pattern.size() && pattern[i + 1] == '?') ? 2 : 1;
        } else {
            uint8_t byte = 0;
            auto result = std::from_chars(pattern.data() + i, pattern.data() + i + 2, byte, 16);
            if (result.ec == std::errc{}) {
                bytes.push_back({ byte, false });
                i += 2;
            } else {
                ++i;
            }
        }
    }

    if (bytes.empty()) return 0;

    for (size_t i = 0; i <= size - bytes.size(); ++i) {
        bool found = true;
        for (size_t j = 0; j < bytes.size(); ++j) {
            if (!bytes[j].wildcard && base[i + j] != bytes[j].byte) {
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
