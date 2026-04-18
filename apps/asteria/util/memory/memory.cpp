#include "memory.hpp"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Psapi.h>

#include <vector>
#include <string_view>

namespace asteria::util {

uintptr_t find_pattern(std::string_view pattern, std::string_view module_name) {
    HMODULE mod = GetModuleHandleA(module_name.data());
    if (!mod) return 0;

    MODULEINFO info{};
    GetModuleInformation(GetCurrentProcess(), mod, &info, sizeof(info));

    auto* base = reinterpret_cast<const uint8_t*>(info.lpBaseOfDll);
    size_t size = info.SizeOfImage;

    // Parse pattern string into (byte, is_wildcard) pairs
    struct byte_entry {
        uint8_t value;
        bool wildcard;
    };
    std::vector<byte_entry> bytes;
    bytes.reserve(32);

    for (size_t i = 0; i < pattern.size();) {
        if (pattern[i] == ' ') {
            ++i;
            continue;
        }
        if (pattern[i] == '?') {
            bytes.push_back({0, true});
            // '?' and '??' are both valid wildcards — skip one or two chars
            bool double_wildcard = (i + 1 < pattern.size() && pattern[i + 1] == '?');
            i += double_wildcard ? 2 : 1;
        } else {
            uint8_t byte = static_cast<uint8_t>(std::strtoul(pattern.data() + i, nullptr, 16));
            bytes.push_back({byte, false});
            i += 2;
        }
    }

    if (bytes.empty() || size < bytes.size()) return 0;

    for (size_t i = 0; i <= size - bytes.size(); ++i) {
        bool match = true;
        for (size_t j = 0; j < bytes.size(); ++j) {
            if (!bytes[j].wildcard && base[i + j] != bytes[j].value) {
                match = false;
                break;
            }
        }
        if (match) return reinterpret_cast<uintptr_t>(base + i);
    }

    return 0;
}

} // namespace asteria::util
