#pragma once

#include "entity.hpp"
#include "../util/memory/memory.hpp"
#include "../util/offsets.hpp"
/// ! CAUTION | AI GENERATED | NEEDS MANUAL REVIEW !

// CEntitySystem — the global entity manager in client.dll.
// Entities are stored in a two-level chunked array:
//   chunks[chunk_index][slot_index] -> entity slot (0x78 bytes)
//   entity pointer is at slot + 0x10

namespace asteria::sdk {

class CEntitySystem {
    static constexpr int CHUNK_SIZE = 512;
    static constexpr int ENTRY_SIZE = 0x78;
    static constexpr int ENTRY_ENTITY_PTR = 0x10;

    char pad_0x00[0x10];
    uint8_t* chunks[1]; // 0x10 — start of chunk pointer array (variable length)

  public:
    C_BaseEntity* get_entity(int index) const {
        if (index < 0 || index >= 0x8000) return nullptr;

        int chunk = index / CHUNK_SIZE;
        int slot = index % CHUNK_SIZE;

        if (!chunks[chunk]) return nullptr;

        auto* entry = chunks[chunk] + slot * ENTRY_SIZE;
        return *reinterpret_cast<C_BaseEntity**>(entry + ENTRY_ENTITY_PTR);
    }

    int get_highest_entity_index() const {
        // m_iHighestEnt is at 0x1510 — too far to embed in the struct cleanly,
        // so we read it by offset from this pointer.
        return *reinterpret_cast<const int*>(reinterpret_cast<const uint8_t*>(this) + 0x1510);
    }
};

// Global pointer — resolved once at init via pattern scan.
inline CEntitySystem* g_entity_system = nullptr;

inline bool init_entity_system() {
    uintptr_t addr = asteria::util::find_pattern(asteria::util::patterns::entity_system, "client.dll");
    if (!addr) return false;

    // Pattern: 48 8B 0D [rel32] — RIP-relative MOV
    int32_t rel = *reinterpret_cast<int32_t*>(addr + 3);
    g_entity_system = *reinterpret_cast<CEntitySystem**>(addr + 7 + rel);
    return g_entity_system != nullptr;
}

} // namespace asteria::sdk
