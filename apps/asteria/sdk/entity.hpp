#pragma once

#include <cstdint>
/// ! CAUTION | AI GENERATED | NEEDS MANUAL REVIEW !

// CS2 client-side entity class hierarchy.
// Struct layouts match the game's memory layout — fields are at the correct offsets.
// Offsets sourced from CS2 schema dumps.

namespace asteria::sdk {

// ---- CEntityHandle ----
// Encodes an entity index + serial number. Serial changes when a slot is reused,
// so stale handles can be detected.

struct CEntityHandle {
    uint32_t value = 0xFFFFFFFF;

    bool is_valid() const { return value != 0xFFFFFFFF; }
    int get_index() const { return static_cast<int>(value & 0x7FFF); }
    int get_serial() const { return static_cast<int>(value >> 15); }
};

// ---- CEntityInstance ----
// Root of the entity hierarchy. All game objects inherit from this.

class CEntityInstance {
    char pad_0x00[0x10]; // vtable + internals
  public:
    CEntityHandle ref_ehandle; // 0x10
};

// ---- CGameSceneNode ----
// Links an entity to its visual representation in scenesystem.dll.
// Embedded inside the entity at m_pGameSceneNode.

class CGameSceneNode {
    char pad_0x00[0x08]; // vtable
  public:
    CEntityInstance* owner; // 0x08 — back-pointer to the owning entity
    char pad_0x10[0xB8];
    float abs_origin[3]; // 0xC8 — world position (x, y, z)
};

// ---- C_BaseEntity ----
// Client-side base entity. Players, props, weapons all inherit from this.

class C_BaseEntity : public CEntityInstance {
    char pad_0x18[0x310]; // gap between CEntityInstance and our fields
  public:
    CGameSceneNode* scene_node; // 0x328
    char pad_0x330[0x08];
    uint8_t life_state; // 0x338  (0 = alive)
    char pad_0x339[0x92];
    uint8_t team_num; // 0x3CB  (2 = T, 3 = CT)

    bool is_alive() const { return life_state == 0; }
};

static_assert(offsetof(C_BaseEntity, scene_node) == 0x328, "C_BaseEntity::scene_node offset mismatch");
static_assert(offsetof(C_BaseEntity, life_state) == 0x338, "C_BaseEntity::life_state offset mismatch");
static_assert(offsetof(C_BaseEntity, team_num) == 0x3CB, "C_BaseEntity::team_num offset mismatch");

// CS2 team numbers
constexpr uint8_t TEAM_T = 2;
constexpr uint8_t TEAM_CT = 3;

} // namespace asteria::sdk
