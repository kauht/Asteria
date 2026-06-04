#include "chams.hpp"
#include "../../../core/hooks/hooks.hpp"
#include "../../../utils/modules/modules.hpp"
#include "../../../utils/memory/memory.hpp"
#include "../../../sdk/game.hpp"
#include <cs2.hpp>
#include <format>
#include <optional>
#include <string_view>

namespace features::chams {
    using namespace scenesystem;

    State g_state;

    void Initialize() {
        g_state.material_system = sdk::MaterialSystem();
        g_state.CreateMaterial = (CreateMaterial_t)memory::FindPattern(sig::materialsystem2::CreateMaterial, modules::materialsystem2);
        g_state.LoadKV3 = (LoadKV3_t)memory::FindPattern(sig::tier0::LoadKV3, modules::tier0);

        sdk::PVSManager()->SetPvsEnabled(false);

        for (int i = 0; i < kMaterialCount; i++) {
            const Material& m = kMaterials[i];
            g_state.enemy[i].vis = MakeMaterial(std::format("vis_{}",  m.tag).c_str(), m.kv3_vis);
            g_state.enemy[i].occ = MakeMaterial(std::format("occ_{}",  m.tag).c_str(), m.kv3_occ);
            g_state.team[i].vis  = MakeMaterial(std::format("tvis_{}", m.tag).c_str(), m.kv3_vis);
            g_state.team[i].occ  = MakeMaterial(std::format("tocc_{}", m.tag).c_str(), m.kv3_occ);
        }
        for (int i = 0; i < kMaterialCountVM; ++i) {
            const Material& m = kMaterialsVM[i];
            g_state.viewmodel[i] = MakeMaterial(std::format("vm_{}", m.tag).c_str(), m.kv3_vis);
        }

        g_state.FindParameter = (FindParameter_t)memory::FindPattern(sig::materialsystem2::FindParameter, modules::materialsystem2);
        g_state.UpdateParameter = (UpdateParameter_t)memory::FindPattern(sig::materialsystem2::UpdateParameter, modules::materialsystem2);

        auto& wc = config::g_config.chams;
        g_state.wire_hand = MakeWireMaterial("vm_hand_wire", wc.hand_wire_color.r, wc.hand_wire_color.g, wc.hand_wire_color.b, wc.hand_wire_color.a);
        g_state.wire_weapon = MakeWireMaterial("vm_weapon_wire", wc.weapon_wire_color.r, wc.weapon_wire_color.g, wc.weapon_wire_color.b, wc.weapon_wire_color.a);
    }

    void RecolorWireframe(int which, const config::Color& color) {
        void* mat = which ? g_state.wire_weapon : g_state.wire_hand;

        void* param = g_state.FindParameter(mat, "g_vOverrideColor");
        if (!param) return;

        auto* values = reinterpret_cast<float*>((uintptr_t)param + 0x08);
        values[0] = color.r;
        values[1] = color.g;
        values[2] = color.b;
        values[3] = color.a;

        g_state.UpdateParameter(param);
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

   struct Target {
        bool is_hands  = false;
        bool is_weapon = false;
        bool is_player = false;
        bool is_enemy  = false;
    };

    static std::optional<Target> ResolveTarget(CSceneAnimatableObject* scene_object) {
        CHandle<void> handle{ scene_object->m_hOwner.m_Index };
        if (!handle.IsValid()) return std::nullopt;

        const uint16_t entity_index = handle.GetIndex();
        auto* entity = static_cast<client::C_BaseEntity*>(CGameEntitySystem::GetEntityByIndex(entity_index));
        auto* local  = sdk::LocalController();
        if (!entity || !local) return std::nullopt;

        const char* designer = CGameEntitySystem::GetDesignerName(entity_index);
        if (!designer || !*designer) return std::nullopt;
        const std::string_view name = designer;

        const int  entity_team = entity->m_iTeamNum();
        const bool is_local    = local->m_hPawn().GetIndex() == entity_index;

        Target t;
        t.is_hands  = name.contains("cs2_hudmodel_arms");
        t.is_weapon = name.contains("cs2_hudmodel_weapon");
        t.is_player = (entity_team == 2 || entity_team == 3) && !is_local && CGameEntitySystem::IsPlayerPawn(entity_index);
        t.is_enemy  = t.is_player && entity_team != local->m_iTeamNum();
        return t;
    }

    void Chams(void* scene, CSceneAnimatableObject* scene_object, void* context, c_mesh_primitive_output_buffer* buffer) {
        auto passthrough = [&] {
            hooks::original::GeneratePrimitives.fastcall<void>(scene, scene_object, context, buffer);
        };

        if (!scene_object || !buffer)
            return passthrough();

        const auto target = ResolveTarget(scene_object);
        if (!target)
            return passthrough();

        auto& cfg = config::g_config.chams;

        // Select material

        void* viewmodel_material = nullptr;
        uint32_t viewmodel_color = 0;
        bool viewmodel_is_wireframe = false;

        void* occluded_material = nullptr;
        uint32_t occluded_color = 0;

        void* visible_material = nullptr;
        uint32_t visible_color = 0;

        if (target->is_hands) {
            if (cfg.hand_chams_enabled) {
                viewmodel_color = PackColor(cfg.hand_color.r, cfg.hand_color.g, cfg.hand_color.b, cfg.hand_color.a);
                viewmodel_material = g_state.viewmodel[cfg.hand_material];
                if (cfg.hand_material == kMaterialCountVM - 1) {
                    viewmodel_material = g_state.wire_hand;
                    viewmodel_is_wireframe = true;
                }
            }
        } else if (target->is_weapon) {
            if (cfg.weapon_chams_enabled) {
                viewmodel_color = PackColor(cfg.weapon_color.r, cfg.weapon_color.g, cfg.weapon_color.b, cfg.weapon_color.a);
                viewmodel_material = g_state.viewmodel[cfg.weapon_material];
                if (cfg.weapon_material == kMaterialCountVM - 1) {
                    viewmodel_material = g_state.wire_weapon;
                    viewmodel_is_wireframe = true;
                }
            }
        }

        if (target->is_enemy) {
            if (cfg.enemy_occ_enabled) {
                int idx = cfg.enemy_occ_material;
                if (idx >= kMaterialCount) idx = 0;
                occluded_material = g_state.enemy[idx].occ;
                occluded_color = PackColor(cfg.enemy_occ_color.r, cfg.enemy_occ_color.g, cfg.enemy_occ_color.b, cfg.enemy_occ_color.a);
            }
            if (cfg.enemy_vis_enabled) {
                int idx = cfg.enemy_vis_material;
                if (idx >= kMaterialCount) idx = 0;
                visible_material = g_state.enemy[idx].vis;
                visible_color = PackColor(cfg.enemy_vis_color.r, cfg.enemy_vis_color.g, cfg.enemy_vis_color.b, cfg.enemy_vis_color.a);
            }
        } else if (target->is_player) {
            if (cfg.team_occ_enabled) {
                int idx = cfg.team_occ_material;
                if (idx >= kMaterialCount) idx = 0;
                occluded_material = g_state.team[idx].occ;
                occluded_color = PackColor(cfg.team_occ_color.r, cfg.team_occ_color.g, cfg.team_occ_color.b, cfg.team_occ_color.a);
            }
            if (cfg.team_vis_enabled) {
                int idx = cfg.team_vis_material;
                if (idx >= kMaterialCount) idx = 0;
                visible_material = g_state.team[idx].vis;
                visible_color = PackColor(cfg.team_vis_color.r, cfg.team_vis_color.g, cfg.team_vis_color.b, cfg.team_vis_color.a);
            }
        }

        if (!viewmodel_material && !occluded_material && !visible_material)
            return passthrough();

        int first_primitive = buffer->m_start_primitive;
        if (first_primitive < 0 || buffer->m_max_output_primitives <= 0 || first_primitive >= buffer->m_max_output_primitives)
            return passthrough();

        passthrough();

        int primitive_count = buffer->m_start_primitive - first_primitive;
        if (primitive_count <= 0) return;

        void* first_pass = nullptr;
        uint32_t first_color = 0;
        void* second_pass = nullptr;
        uint32_t second_color = 0;

        if (target->is_weapon && viewmodel_is_wireframe) {
            first_pass = g_state.viewmodel[0];
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
            passthrough();
            int second_count = buffer->m_start_primitive - second_start;
            if (second_count) {
                SetPrimitiveMaterial(buffer, second_start, second_start + second_count, second_pass, second_color);
            }
        }
    }

} // namespace features::chams
