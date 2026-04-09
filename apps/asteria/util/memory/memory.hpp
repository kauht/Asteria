#pragma once
#include <vector>
#include <string>

namespace asteria::util {

    std::vector<std::pair<uint8_t, bool>> pattern_to_bytes(const std::string& pattern);

    uintptr_t find_pattern(const std::string& pattern, const std::string& module_name);
}
