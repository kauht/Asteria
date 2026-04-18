#pragma once
/// ! CAUTION | AI GENERATED | NEEDS MANUAL REVIEW !

#include "chams.hpp"
#include "materials.hpp"
#include "../../../util/memory/memory.hpp"

#include <windows.h>
#include <vector>

// KV3 Material shit

namespace asteria::core::features::chams {

static constexpr int NUM_STYLES = 5;
extern c_material2* g_mats[NUM_STYLES][2]; // [0=occluded, 1=visible]

namespace {

struct kv3_id_t {
    const char* name;
    uint64_t unk1;
    uint64_t unk2;
};
using fn_load_kv3 = bool(__fastcall*)(void*, void*, const char*, const kv3_id_t*, const char*, uint32_t);
using fn_create_material = void(__fastcall*)(void*, void**, const char*, void*, uint32_t, uint32_t);

inline void* get_material_system() {
    auto get = [](const char* mod, const char* name) -> void* {
        HMODULE h = GetModuleHandleA(mod);
        if (!h) return nullptr;
        auto fn = reinterpret_cast<void* (*)(const char*, int*)>(GetProcAddress(h, "CreateInterface"));
        return fn ? fn(name, nullptr) : nullptr;
    };
    void* ms = get("materialsystem2.dll", "VMaterialSystem2_001");
    return ms ? ms : get("materialsystem2.dll", "VMaterialSystem2_000");
}

inline c_material2* create_material(const char* name, const char* kv3_text) {
    static void* ms = get_material_system();
    static auto load_kv3 = reinterpret_cast<fn_load_kv3>(GetProcAddress(GetModuleHandleA("tier0.dll"), "?LoadKV3@@YA_NPEAVKeyValues3@@PEAVCUtlString@@PEBDAEBUKV3ID_t@@2I@Z"));
    static auto create = reinterpret_cast<fn_create_material>(asteria::util::find_pattern("48 89 5C 24 ? 48 89 6C 24 ? 56 57 41 56 48 81 EC ? ? ? ? 48 8B 05", "materialsystem2.dll"));

    if (!ms || !load_kv3 || !create) return nullptr;

    void* buf = malloc(0x400);
    if (!buf) return nullptr;
    memset(buf, 0, 0x400);
    void* kv = reinterpret_cast<uint8_t*>(buf) + 0x100;

    kv3_id_t id{"generic", 0x469806E97412167CULL, 0xE73790B53EE6F2AFULL};
    if (!load_kv3(kv, nullptr, kv3_text, &id, nullptr, 0)) {
        free(buf);
        return nullptr;
    }

    static std::vector<void*> alive;
    alive.push_back(buf);

    void* handle = nullptr;
    create(ms, &handle, name, kv, 0, 0);
    return handle ? *reinterpret_cast<c_material2**>(handle) : nullptr;
}

} // anonymous namespace

inline void init_materials() {
    using namespace materials;
    g_mats[0][0] = create_material("asteria_glass_occ", glass_occ);
    g_mats[0][1] = create_material("asteria_glass_vis", glass_vis);
    g_mats[1][0] = create_material("asteria_flat_occ", flat_occ);
    g_mats[1][1] = create_material("asteria_flat_vis", flat_vis);
    g_mats[2][0] = create_material("asteria_glow_occ", glow_occ);
    g_mats[2][1] = create_material("asteria_glow_vis", glow_vis);
    g_mats[3][0] = create_material("asteria_latex_occ", latex_occ);
    g_mats[3][1] = create_material("asteria_latex_vis", latex_vis);
    g_mats[4][0] = create_material("asteria_metallic_occ", metallic_occ);
    g_mats[4][1] = create_material("asteria_metallic_vis", metallic_vis);
}

} // namespace asteria::core::features::chams
