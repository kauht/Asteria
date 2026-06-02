#pragma once
#include "vmats.hpp"
#include "../../../utils/config/config.hpp"
#include <cs2.hpp>
#include <array>
#include <format>

namespace features::chams {

    struct Material {
        const char* tag;
        const char* kv3_vis;
        const char* kv3_occ;
    };

    inline const int kMaterialCount = 4;
    inline const Material kMaterials[kMaterialCount] = {
        { "flat", VMat::Flat, VMat::FlatOCC },
        { "glow", VMat::Glow, VMat::GlowOCC },
        { "elec", VMat::Electric, VMat::ElectricOCC },
        { "chrome", VMat::Chrome, VMat::ChromeOCC },
    };

    inline const int kMaterialCountVM = 5;
    inline const Material kMaterialsVM[kMaterialCountVM] = {
        { "flat", VMat::Flat, nullptr },
        { "glow", VMat::Glow, nullptr },
        { "elec", VMat::Electric, nullptr },
        { "chrome", VMat::Chrome, nullptr },
        { "wire", VMat::Flat, nullptr },
    };
    inline const char* kMaterialNames[kMaterialCount] = {"Flat", "Glow", "Electric", "Chrome"};
    inline const char* kMaterialNamesVM[kMaterialCountVM] = {"Flat", "Glow", "Electric", "Chrome", "Wireframe"};

    void Initialize();
    void RecolorWireframe(int which, const config::Color& color);
    void Chams(void* scene, scenesystem::CSceneAnimatableObject* sceneObject, void* ctx, scenesystem::c_mesh_primitive_output_buffer* render_buf);

    using namespace materialsystem2;
    using namespace scenesystem;

    inline constexpr uint64_t k_kv3Unk0 = 0x469806E97412167CULL;
    inline constexpr uint64_t k_kv3Unk1 = 0xE73790B53EE6F2AFULL;

    inline void* material_system = nullptr;
    inline bool(__fastcall* LoadKV3)(void*, void*, const char*, const kv3_id_t*, const char*, uint32_t) = nullptr;
    inline void*(__fastcall* CreateMaterial)(void*, void**, const char*, void*, void*, char) = nullptr;
    inline void*(__fastcall* FindParameter)(void*, const char*) = nullptr;
    inline void*(__fastcall* UpdateParameter)(void*) = nullptr;

    inline void* g_mat_enemy[kMaterialCount] = {};
    inline void* g_mat_team[kMaterialCount] = {};
    inline void* g_mat_enemy_occ[kMaterialCount] = {};
    inline void* g_mat_team_occ[kMaterialCount] = {};
    inline void* g_mat_viewmodel[kMaterialCountVM] = {};

    // Wireframe materials
    inline void* g_wire_hand = nullptr;
    inline void* g_wire_weapon = nullptr;
}
