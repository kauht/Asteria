#include "chams.hpp"
#include "../../../core/hooks/hooks.hpp"
#include "../../../utils/modules/modules.hpp"
#include "../../../utils/memory/memory.hpp"
#include "../../../utils/io/io.hpp"
#include <signatures/signatures.hpp>
#include <sdk/offsets.hpp>
#include <sdk/scenesystem_dll.hpp>
#include <sdk/materialsystem2_dll.hpp>
#include <array>

namespace features {
    using namespace sdk::scenesystem;
    using namespace sdk::materialsystem2;

    static constexpr uint64_t k_kv3Unk0 = 0x469806E97412167CULL;
    static constexpr uint64_t k_kv3Unk1 = 0xE73790B53EE6F2AFULL;

    static void* g_materialSystem = nullptr;
    static bool(__fastcall* g_load_kv3)(void*, void*, const char*, const kv3_id_t*, const char*, uint32_t) = nullptr;
    static void*(__fastcall* g_create_material)(void*, void**, const char*, void*, void*, char) = nullptr;

    static CMaterial* g_mat_enemy[3] = {};
    static CMaterial* g_mat_team[3] = {};
    static CMaterial* g_mat_viewmodel[3] = {};

    static CMaterial* CreateMaterialFromKV3(const char* name, const char* kv3_text) {
        if (!g_materialSystem || !g_load_kv3 || !g_create_material)
            return nullptr;

        std::array<uint8_t, 0x400> buf{};
        auto* kv = buf.data() + 0x100;
        kv3_id_t id{ "generic", k_kv3Unk0, k_kv3Unk1 };

        if (!g_load_kv3(kv, nullptr, kv3_text, &id, nullptr, 0))
            return nullptr;

        void* handle = nullptr;
        g_create_material(g_materialSystem, &handle, name, kv, nullptr, 0);

        return handle ? *reinterpret_cast<CMaterial**>(handle) : nullptr;
    }

    namespace chams {
        void Initialize() {
            auto ms_base = reinterpret_cast<uintptr_t>(modules::materialsystem2);
            if (!ms_base) return;

            g_materialSystem = *reinterpret_cast<void**>(ms_base + 0x15D750);
            if (!g_materialSystem) return;

            g_create_material = reinterpret_cast<decltype(g_create_material)>(memory::FindPattern(sdk::sigs::materialsystem2::CreateMaterial, modules::materialsystem2));
            g_load_kv3 = reinterpret_cast<decltype(g_load_kv3)>(memory::FindPattern(sdk::sigs::tier0::LoadKV3, modules::tier0));

            g_mat_enemy[0] = CreateMaterialFromKV3("asteria_ev_flat", VMat::Flat);
            g_mat_enemy[1] = CreateMaterialFromKV3("asteria_ev_glow", VMat::Glow);
            g_mat_enemy[2] = CreateMaterialFromKV3("asteria_ev_elec", VMat::ElectricVis);
            g_mat_team[0] = CreateMaterialFromKV3("asteria_tv_flat", VMat::Flat);
            g_mat_team[1] = CreateMaterialFromKV3("asteria_tv_glow", VMat::Glow);
            g_mat_team[2] = CreateMaterialFromKV3("asteria_tv_elec", VMat::ElectricVis);
            g_mat_viewmodel[0] = CreateMaterialFromKV3("asteria_vm_flat", VMat::Flat);
            g_mat_viewmodel[1] = CreateMaterialFromKV3("asteria_vm_glow", VMat::Glow);
            g_mat_viewmodel[2] = CreateMaterialFromKV3("asteria_vm_elec", VMat::ElectricVis);
        }
    }

    static void Override(c_mesh_draw_primitive* mesh, CMaterial* mat, uint32_t color) {
        mesh->m_material = mat;
        mesh->m_tint_color = color;
    }

    static uint32_t PackColor(float r, float g, float b, float a) {
        return (static_cast<uint8_t>(r * 255.0f)) |
               (static_cast<uint8_t>(g * 255.0f) << 8) |
               (static_cast<uint8_t>(b * 255.0f) << 16) |
               (static_cast<uint8_t>(a * 255.0f) << 24);
    }

    static bool SubStr(const char* str, const char* sub);
    enum ViewModelType { NOT_VM, VM_WEAPON, VM_HAND };

    static int g_gp_debug = 0;

    static const char* GetRawDesignerName(uint16_t ent_index) {
        uintptr_t client_base = reinterpret_cast<uintptr_t>(modules::client);
        if (!client_base) return nullptr;

        auto entity_system = *reinterpret_cast<void**>(client_base + cs2::offsets::client::GameEntitySystemPtr);
        if (!entity_system) return nullptr;

        int nChunk = ent_index / 512;
        int nSlot = ent_index % 512;

        auto* chunks = reinterpret_cast<uintptr_t*>(reinterpret_cast<uint8_t*>(entity_system) + 0x10);
        auto pChunk = *reinterpret_cast<uintptr_t*>(chunks + nChunk);
        if (!pChunk) return nullptr;

        auto* identity = reinterpret_cast<uint8_t*>(pChunk + nSlot * 0x70);
        return *reinterpret_cast<const char**>(identity + 0x20);
    }

    static ViewModelType GetViewModelType(uint16_t ent_index) {
        const char* designer = nullptr;

        // Method 1: try custom entity map
        auto* ent = entities::GetEntityByIndex(ent_index);
        if (ent) {
            auto identity = *reinterpret_cast<uintptr_t*>(reinterpret_cast<uint8_t*>(ent) + 0x10);
            if (identity)
                designer = *reinterpret_cast<const char**>(reinterpret_cast<uint8_t*>(identity) + 0x20);
        }

        // Method 2: fallback to raw entity list (catches viewmodels not in custom map)
        if (!designer)
            designer = GetRawDesignerName(ent_index);

        if (designer && SubStr(designer, "hudmodel")) {
            if (SubStr(designer, "arms"))
                return VM_HAND;
            return VM_WEAPON;
        }

        // Method 3: check against local player's arms viewmodel handle
        auto* local_ctrl = entities::GetLocalPlayer();
        if (local_ctrl) {
            auto pawn_handle = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(local_ctrl) + 0x90C);
            uint16_t pawn_idx = pawn_handle & 0x7FFF;
            if (pawn_idx > 0 && pawn_idx <= 4096) {
                auto* pawn = entities::GetEntityByIndex(pawn_idx);
                if (pawn) {
                    auto arms_handle = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(pawn) + 0x1B58);
                    if (arms_handle != 0xFFFFFFFF && (arms_handle & 0x7FFF) == ent_index) return VM_HAND;
                }
            }
        }

        return NOT_VM;
    }

    static bool SubStr(const char* str, const char* sub) {
        if (!str || !sub) return false;
        while (*str) {
            const char* a = str;
            const char* b = sub;
            while (*a && *b && *a == *b) { a++; b++; }
            if (!*b) return true;
            str++;
        }
        return false;
    }

    void chams::OnGeneratePrimitives(void* scene, CSceneAnimatableObject* obj, void* ctx, c_mesh_primitive_output_buffer* buf) {
        auto& cfg = config::g_config.chams;

        auto orig = [&]() {
            hooks::original::GeneratePrimitives.fastcall<void>(scene, obj, ctx, buf);
        };

        if (!obj || !buf) { orig(); return; }

        uint32_t handle = obj->m_hOwner.m_Index;

        if (handle == 0xFFFFFFFF) { orig(); return; }

        const uint16_t ent_index = handle & 0x7FFF;

        if (g_gp_debug < 1000) {
            const char* rn = GetRawDesignerName(ent_index);
            if (rn && (SubStr(rn, "player") || SubStr(rn, "pawn") || SubStr(rn, "Player") || SubStr(rn, "Pawn")))
                io::println("[gp-player] idx=%hu raw='%s'", ent_index, rn);
            g_gp_debug++;
        }

        // Viewmodel (weapon/hands)
        auto vm_type = GetViewModelType(ent_index);
        if (vm_type != NOT_VM) {
            bool enabled = (vm_type == VM_WEAPON) ? cfg.weapon_chams_enabled : cfg.hand_chams_enabled;
            if (!enabled || !g_mat_viewmodel[0]) { orig(); return; }
            auto* mat = g_mat_viewmodel[cfg.viewmodel_material];
            if (!mat) { orig(); return; }
            uint32_t col = PackColor(cfg.viewmodel_color.r, cfg.viewmodel_color.g, cfg.viewmodel_color.b, cfg.viewmodel_color.a);
            int start = buf->m_start_primitive;
            orig();
            int count = buf->m_start_primitive - start;
            if (count > 0) {
                for (int i = start; i < start + count; ++i)
                    Override(&buf->m_out[i], mat, col);
            }
            return;
        }

        auto* ent = entities::GetEntityByIndex(ent_index);
        if (!ent) { orig(); return; }

        // Team check
        int team = ent->m_iTeamNum();
        if (team != 2 && team != 3) { orig(); return; }

        // Player pawn filter
        bool is_player_pawn = false;
        for (int i = 1; i <= 64; ++i) {
            auto* ctrl = entities::GetEntityByIndex(i);
            if (!ctrl) continue;
            auto pawn_handle = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(ctrl) + 0x90C);
            if ((pawn_handle & 0x7FFF) == ent_index) {
                is_player_pawn = true;
                break;
            }
        }
        if (!is_player_pawn) { orig(); return; }

        // Local player detection
        auto* local_ctrl = entities::GetLocalPlayer();
        if (!local_ctrl) { orig(); return; }

        int local_team = local_ctrl->m_iTeamNum();
        bool is_enemy = (team != local_team);

        // Self skip: compare entity index against local controller's pawn handle
        auto local_pawn_handle = *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(local_ctrl) + 0x90C);
        if ((local_pawn_handle & 0x7FFF) == ent_index) { orig(); return; }

        bool enabled = is_enemy ? cfg.enemy_vis_enabled : cfg.team_vis_enabled;
        if (!enabled) { orig(); return; }

        int mat_idx = is_enemy ? cfg.enemy_vis_material : cfg.team_vis_material;
        auto* mat = is_enemy ? g_mat_enemy[mat_idx] : g_mat_team[mat_idx];
        if (!mat) { orig(); return; }

        auto& c = is_enemy ? cfg.enemy_vis_color : cfg.team_vis_color;
        uint32_t col = PackColor(c.r, c.g, c.b, c.a);

        int start = buf->m_start_primitive;
        orig();
        int count = buf->m_start_primitive - start;
        if (count > 0) {
            for (int i = start; i < start + count; ++i)
                Override(&buf->m_out[i], mat, col);
        }
    }
}
