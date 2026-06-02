#include "chams.hpp"
#include "../../../core/hooks/hooks.hpp"
#include "../../../utils/modules/modules.hpp"
#include "../../../utils/memory/memory.hpp"
#include <cs2.hpp>
#include <format>

namespace features::chams {

    static void DisablePVS() {
        if (!modules::engine2) return;
        auto* pvs = reinterpret_cast<ifc::engine2::CEnginePVSManager*>(reinterpret_cast<uintptr_t>(modules::engine2) + offsets::engine2::PVSManager);
        pvs->SetPvsEnabled(false);
    }

    void Initialize() {
        material_system = *(void**)((uintptr_t)modules::materialsystem2 + 0x15D750);
        CreateMaterial = (decltype(CreateMaterial))memory::FindPattern(sig::materialsystem2::CreateMaterial, modules::materialsystem2);
        LoadKV3 = (decltype(LoadKV3))memory::FindPattern(sig::tier0::LoadKV3, modules::tier0);
        DisablePVS();

        for (int i = 0; i < kMaterialCount; i++) {
            auto name = std::format("occ_{}", kMaterials[i].tag).c_str();
            g_mat_enemy_occ[i] = MakeMaterial(name, kMaterials[i].kv3_occ);

            name = std::format("tocc_{}", kMaterials[i].tag).c_str();
            g_mat_team_occ[i] = MakeMaterial(name, kMaterials[i].kv3_occ);

            name = std::format("vis_{}", kMaterials[i].tag).c_str();
            g_mat_enemy[i] = MakeMaterial(name, kMaterials[i].kv3_vis);

            name = std::format("tvis_{}", kMaterials[i].tag).c_str();
            g_mat_team[i] = MakeMaterial(name, kMaterials[i].kv3_vis);
        }
        for (int i = 0; i < kMaterialCountVM; ++i) {
            auto name = std::format("vm_{}", kMaterialsVM[i].tag).c_str();
            g_mat_viewmodel[i] = MakeMaterial(name, kMaterialsVM[i].kv3_vis);
        }

        FindParameter = (decltype(FindParameter))memory::FindPattern(sig::materialsystem2::FindParameter, modules::materialsystem2);
        UpdateParameter = (decltype(UpdateParameter))memory::FindPattern(sig::materialsystem2::UpdateParameter, modules::materialsystem2);

        auto& wc = config::g_config.chams;
        g_wire_hand = MakeWireMaterial("vm_hand_wire", wc.hand_wire_color.r, wc.hand_wire_color.g, wc.hand_wire_color.b, wc.hand_wire_color.a);
        g_wire_weapon = MakeWireMaterial("vm_weapon_wire", wc.weapon_wire_color.r, wc.weapon_wire_color.g, wc.weapon_wire_color.b, wc.weapon_wire_color.a);
    }

    void RecolorWireframe(int which, const config::Color& color) {
        void* mat = which ? g_wire_weapon : g_wire_hand;

        void* param = FindParameter(mat, "g_vOverrideColor");
        if (!param) return;

        auto* values = reinterpret_cast<float*>((uintptr_t)param + 0x08);
        values[0] = color.r;
        values[1] = color.g;
        values[2] = color.b;
        values[3] = color.a;

        UpdateParameter(param);
    }

    static uint32_t PackColor(float r, float g, float b, float a) {
        return (uint8_t)(r * 255)
             | ((uint8_t)(g * 255) << 8)
             | ((uint8_t)(b * 255) << 16)
             | ((uint8_t)(a * 255) << 24);
    }

    static void SetPrimitiveMaterial(c_mesh_primitive_output_buffer* buffer, int from, int to, void* material, uint32_t color) {
        float alpha = ((color >> 24) & 0xFF) / 255.0f;
        for (int i = from; i < to; i++) {
            buffer->m_out[i].m_material = material;
            buffer->m_out[i].m_tint_color = color;
            buffer->m_out[i].m_alpha_scale = alpha;
        }
    }

    void Chams(void* scene, CSceneAnimatableObject* scene_object, void* context, c_mesh_primitive_output_buffer* buffer) {
        if (!scene_object || !buffer) {
            hooks::original::GeneratePrimitives.fastcall<void>(scene, scene_object, context, buffer);
            return;
        }
        auto& cfg = config::g_config.chams;

        CHandle<void> handle{ scene_object->m_hOwner.m_Index };
        if (!handle.IsValid()) {
            hooks::original::GeneratePrimitives.fastcall<void>(scene, scene_object, context, buffer);
            return;
        }

        uint16_t entity_index = handle.GetIndex();

        auto* entity = static_cast<client::C_BaseEntity*>(CGameEntitySystem::GetEntityByIndex(entity_index));
        auto* local_controller = *reinterpret_cast<client::CCSPlayerController**>((uintptr_t)modules::client + offsets::client::LocalPlayerController);
        if (!entity || !local_controller) {
            hooks::original::GeneratePrimitives.fastcall<void>(scene, scene_object, context, buffer);
            return;
        }

        int entity_team = entity->m_iTeamNum();
        bool is_local = local_controller->m_hPawn().GetIndex() == entity_index;

        auto* name_ptr = CGameEntitySystem::GetDesignerName(entity_index);
        if (!name_ptr) {
            hooks::original::GeneratePrimitives.fastcall<void>(scene, scene_object, context, buffer);
            return;
        }
        std::string name = name_ptr;
        if (name.empty()) {
            hooks::original::GeneratePrimitives.fastcall<void>(scene, scene_object, context, buffer);
            return;
        }

        bool is_hands = name.contains("cs2_hudmodel_arms");
        bool is_weapon = name.contains("cs2_hudmodel_weapon");

        bool is_player = (entity_team == 2 || entity_team == 3) && !is_local && CGameEntitySystem::IsPlayerPawn(entity_index);

        // Select material

        void* viewmodel_material = nullptr;
        uint32_t viewmodel_color = 0;
        bool viewmodel_is_wireframe = false;

        void* occluded_material = nullptr;
        uint32_t occluded_color = 0;

        void* visible_material = nullptr;
        uint32_t visible_color = 0;

        if (is_hands) {
            if (cfg.hand_chams_enabled) {
                viewmodel_color = PackColor(cfg.hand_color.r, cfg.hand_color.g, cfg.hand_color.b, cfg.hand_color.a);
                viewmodel_material = g_mat_viewmodel[cfg.hand_material];
                if (cfg.hand_material == kMaterialCountVM - 1) {
                    viewmodel_material = g_wire_hand;
                    viewmodel_is_wireframe = true;
                }
            }
        } else if (is_weapon) {
            if (cfg.weapon_chams_enabled) {
                viewmodel_color = PackColor(cfg.weapon_color.r, cfg.weapon_color.g, cfg.weapon_color.b, cfg.weapon_color.a);
                viewmodel_material = g_mat_viewmodel[cfg.weapon_material];
                if (cfg.weapon_material == kMaterialCountVM - 1) {
                    viewmodel_material = g_wire_weapon;
                    viewmodel_is_wireframe = true;
                }
            }
        }

        if (is_player && entity_team != local_controller->m_iTeamNum()) {
            if (cfg.enemy_occ_enabled) {
                int idx = cfg.enemy_occ_material;
                if (idx >= kMaterialCount) idx = 0;
                occluded_material = g_mat_enemy_occ[idx];
                occluded_color = PackColor(cfg.enemy_occ_color.r, cfg.enemy_occ_color.g, cfg.enemy_occ_color.b, cfg.enemy_occ_color.a);
            }
            if (cfg.enemy_vis_enabled) {
                int idx = cfg.enemy_vis_material;
                if (idx >= kMaterialCount) idx = 0;
                visible_material = g_mat_enemy[idx];
                visible_color = PackColor(cfg.enemy_vis_color.r, cfg.enemy_vis_color.g, cfg.enemy_vis_color.b, cfg.enemy_vis_color.a);
            }
        } else if (is_player) {
            if (cfg.team_occ_enabled) {
                int idx = cfg.team_occ_material;
                if (idx >= kMaterialCount) idx = 0;
                occluded_material = g_mat_team_occ[idx];
                occluded_color = PackColor(cfg.team_occ_color.r, cfg.team_occ_color.g, cfg.team_occ_color.b, cfg.team_occ_color.a);
            }
            if (cfg.team_vis_enabled) {
                int idx = cfg.team_vis_material;
                if (idx >= kMaterialCount) idx = 0;
                visible_material = g_mat_team[idx];
                visible_color = PackColor(cfg.team_vis_color.r, cfg.team_vis_color.g, cfg.team_vis_color.b, cfg.team_vis_color.a);
            }
        }

        if (!viewmodel_material && !occluded_material && !visible_material) {
            hooks::original::GeneratePrimitives.fastcall<void>(scene, scene_object, context, buffer);
            return;
        }

        int first_primitive = buffer->m_start_primitive;
        if (first_primitive < 0 || buffer->m_max_output_primitives <= 0 || first_primitive >= buffer->m_max_output_primitives) {
            hooks::original::GeneratePrimitives.fastcall<void>(scene, scene_object, context, buffer);
            return;
        }

        // Apply material

        hooks::original::GeneratePrimitives.fastcall<void>(scene, scene_object, context, buffer);

        int primitive_count = buffer->m_start_primitive - first_primitive;
        if (primitive_count <= 0) return;

        void* first_pass = nullptr;
        uint32_t first_color = 0;
        void* second_pass = nullptr;
        uint32_t second_color = 0;

        if (is_weapon && viewmodel_is_wireframe) {
            first_pass = g_mat_viewmodel[0];
            first_color = viewmodel_color;
            second_pass = viewmodel_material;
            second_color = viewmodel_color;
        } else if (occluded_material && visible_material) {
            first_pass = occluded_material;
            first_color = occluded_color;
            second_pass = visible_material;
            second_color = visible_color;
        } else if (viewmodel_material) {
            first_pass = viewmodel_material;
            first_color = viewmodel_color;
        } else if (occluded_material) {
            first_pass = occluded_material;
            first_color = occluded_color;
        } else {
            first_pass = visible_material;
            first_color = visible_color;
        }

        SetPrimitiveMaterial(buffer, first_primitive, first_primitive + primitive_count, first_pass, first_color);

        if (second_pass) {
            int second_start = buffer->m_start_primitive;
            hooks::original::GeneratePrimitives.fastcall<void>(scene, scene_object, context, buffer);
            int second_count = buffer->m_start_primitive - second_start;
            if (second_count) {
                SetPrimitiveMaterial(buffer, second_start, second_start + second_count, second_pass, second_color);
            }
        }
    }

} // namespace features::chams
