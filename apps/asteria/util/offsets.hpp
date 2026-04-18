#pragma once

// Byte patterns used for runtime address resolution.
// Only patterns that are actively used are kept here.

namespace asteria::util::patterns {

// CEntitySystem* — resolves the global entity manager pointer in client.dll
constexpr auto entity_system = "48 8B 0D ? ? ? ? 48 89 7C 24 ? 8B FA C1 EB";

} // namespace asteria::util::patterns
