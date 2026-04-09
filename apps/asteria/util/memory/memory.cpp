#include "memory.hpp"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <Psapi.h>
#include <Windows.h>
#include <vector>

namespace asteria::util {

std::vector<std::pair<uint8_t, bool>> pattern_to_bytes(const std::string& pattern) {
    std::vector<std::pair<uint8_t, bool>> pattern_bytes;
    const char* start = pattern.c_str();
    const char* end = start + pattern.size();

    for (const char* current = start; current < end; ++current) {
        if (*current == ' ')
            continue;
        if (*current == '?') {
            pattern_bytes.emplace_back(0, false);
            if (*(current + 1) == '?')
                ++current;
        } else {
            pattern_bytes.emplace_back(strtoul(current, nullptr, 16), true);
            if (*(current + 1) != ' ')
                ++current;
        }
    }

    return pattern_bytes;
}

uintptr_t find_pattern(const std::string& pattern, const std::string& module_name) {
    if (module_name.empty())
        return 0;

    auto mod = GetModuleHandle(module_name.c_str());
    if (!mod)
        return 0;

    MODULEINFO module_info;
    GetModuleInformation(GetCurrentProcess(), mod, &module_info, sizeof(MODULEINFO));

    size_t moduleSize = module_info.SizeOfImage;
    uintptr_t module_base = (uintptr_t) module_info.lpBaseOfDll;

    std::vector<std::pair<uint8_t, bool>> pattern_bytes = pattern_to_bytes(pattern);
    size_t pattern_length = pattern_bytes.size();

    for (size_t i = 0; i < moduleSize - pattern_length; ++i) {
        bool found = true;
        for (size_t j = 0; j < pattern_length; ++j) {
            if (pattern_bytes[j].second && pattern_bytes[j].first != *reinterpret_cast<uint8_t*>(module_base + i + j)) {
                found = false;
                break;
            }
        }
        if (found) {
            return module_base + i;
        }
    }

    return 0;
}

} // namespace asteria::util
