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

    inline constexpr int kMaterialCount = 4;
    inline constexpr Material kMaterials[kMaterialCount] = {
        { "flat", VMat::Flat, VMat::FlatOCC },
        { "glow", VMat::Glow, VMat::GlowOCC },
        { "elec", VMat::Electric, VMat::ElectricOCC },
        { "chrome", VMat::Chrome, VMat::ChromeOCC },
    };

    inline constexpr int kMaterialCountVM = 5;
    inline constexpr Material kMaterialsVM[kMaterialCountVM] = {
        { "flat", VMat::Flat, nullptr },
        { "glow", VMat::Glow, nullptr },
        { "elec", VMat::Electric, nullptr },
        { "chrome", VMat::Chrome, nullptr },
        { "wire", VMat::Flat, nullptr },
    };
    inline constexpr const char* kMaterialNames[kMaterialCount] = {"Flat", "Glow", "Electric", "Chrome"};
    inline constexpr const char* kMaterialNamesVM[kMaterialCountVM] = {"Flat", "Glow", "Electric", "Chrome", "Wireframe"};

    void Initialize();
    void RecolorWireframe(int which, const config::Color& color);
    void Chams(void* scene, scenesystem::CSceneAnimatableObject* sceneObject, void* ctx, scenesystem::c_mesh_primitive_output_buffer* render_buf);

    inline constexpr uint64_t k_kv3Unk0 = 0x469806E97412167CULL;
    inline constexpr uint64_t k_kv3Unk1 = 0xE73790B53EE6F2AFULL;

    using LoadKV3_t = bool (__fastcall*)(void*, void*, const char*, const materialsystem2::kv3_id_t*, const char*, uint32_t);
    using CreateMaterial_t = void* (__fastcall*)(void*, void**, const char*, void*, void*, char);
    using FindParameter_t = void* (__fastcall*)(void*, const char*);
    using UpdateParameter_t = void* (__fastcall*)(void*);

    struct MaterialPair {
        void* vis = nullptr;
        void* occ = nullptr;
    };

    struct State {
        void*             material_system = nullptr;
        LoadKV3_t         LoadKV3         = nullptr;
        CreateMaterial_t  CreateMaterial  = nullptr;
        FindParameter_t   FindParameter   = nullptr;
        UpdateParameter_t UpdateParameter = nullptr;

        MaterialPair enemy[kMaterialCount];
        MaterialPair team[kMaterialCount];
        void* viewmodel[kMaterialCountVM] = {};
        void* wire_hand   = nullptr;
        void* wire_weapon = nullptr;
    };
    extern State g_state;
}
