#pragma once

#include <cstdint>
#include <string_view>

namespace asteria::util {

// Scans a loaded module for a byte pattern. Wildcards are represented as '?'.
// Returns the address of the first match, or 0 if not found.
// Example: find_pattern("48 8B 0D ? ? ? ?", "client.dll")
uintptr_t find_pattern(std::string_view pattern, std::string_view module_name);

} // namespace asteria::util
