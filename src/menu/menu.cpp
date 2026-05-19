#include "menu.hpp"
#include "../utils/utils.hpp"
#include "../globals.hpp"
#include "../core/features/chams/chams.hpp"
#include <zui/zui.hpp>

namespace menu {

    static float x = 400.f, y = 400.f, win_w = 700.f, win_h = 500.f;
    static int tab = 0;

    enum {
        TAB_AIMBOT,
        TAB_VISUALS,
        TAB_INVENTORY,
        TAB_MISC,
        TAB_SETTINGS
    };

    static zdraw::rgba NormalizedToRGBA(const config::Color& src) {
        return zdraw::rgba(
            uint8_t(src.r * 255.f),
            uint8_t(src.g * 255.f),
            uint8_t(src.b * 255.f),
            uint8_t(src.a * 255.f)
        );
    }

    static void NormalizeRGBA(config::Color& dst, const zdraw::rgba& src) {
        dst.r = src.r / 255.f;
        dst.g = src.g / 255.f;
        dst.b = src.b / 255.f;
        dst.a = src.a / 255.f;
    }

    static void TabChams() {
        using namespace features::chams;
        auto& chams = config::g_config.chams;

        static zdraw::rgba s_enemy_vis_color = NormalizedToRGBA(chams.enemy_vis_color);
        static zdraw::rgba s_enemy_occ_color = NormalizedToRGBA(chams.enemy_occ_color);
        static zdraw::rgba s_team_vis_color = NormalizedToRGBA(chams.team_vis_color);
        static zdraw::rgba s_team_occ_color = NormalizedToRGBA(chams.team_occ_color);
        static zdraw::rgba s_hand_color = NormalizedToRGBA(chams.hand_color);
        static zdraw::rgba s_hand_wire_color = NormalizedToRGBA(chams.hand_wire_color);
        static zdraw::rgba s_weapon_color = NormalizedToRGBA(chams.weapon_color);
        static zdraw::rgba s_weapon_wire_color = NormalizedToRGBA(chams.weapon_wire_color);

        auto fw = zui::calc_item_width(1);
        if (zui::begin_group_box("Chams", fw)) {
            auto hw = zui::calc_item_width(2);

            if (zui::begin_group_box("Enemy", hw)) {
                zui::checkbox("Visible", chams.enemy_vis_enabled);
                if (zui::color_picker("Vis Color", s_enemy_vis_color)) NormalizeRGBA(chams.enemy_vis_color, s_enemy_vis_color);
                zui::combo("Vis Mat", chams.enemy_vis_material, kMaterialNames, kMaterialCount);
                zui::checkbox("Occluded", chams.enemy_occ_enabled);
                if (zui::color_picker("Occ Color", s_enemy_occ_color)) NormalizeRGBA(chams.enemy_occ_color, s_enemy_occ_color);
                zui::combo("Occ Mat", chams.enemy_occ_material, kMaterialNames, kMaterialCount);
                zui::end_group_box();
            }
            zui::same_line();
            if (zui::begin_group_box("Team", hw)) {
                zui::checkbox("Visible", chams.team_vis_enabled);
                if (zui::color_picker("Vis Color", s_team_vis_color)) NormalizeRGBA(chams.team_vis_color, s_team_vis_color);
                zui::combo("Vis Mat", chams.team_vis_material, kMaterialNames, kMaterialCount);
                zui::checkbox("Occluded", chams.team_occ_enabled);
                if (zui::color_picker("Occ Color", s_team_occ_color)) NormalizeRGBA(chams.team_occ_color, s_team_occ_color);
                zui::combo("Occ Mat", chams.team_occ_material, kMaterialNames, kMaterialCount);
                zui::end_group_box();
            }

            if (zui::begin_group_box("Hands", hw)) {
                zui::checkbox("Enabled", chams.hand_chams_enabled);
                if (zui::color_picker("Color", s_hand_color)) NormalizeRGBA(chams.hand_color, s_hand_color);
                zui::combo("Material", chams.hand_material, kMaterialNamesVM, kMaterialCountVM);
                if (zui::color_picker("Wire Color", s_hand_wire_color)) {
                    NormalizeRGBA(chams.hand_wire_color, s_hand_wire_color);
                    features::chams::RecolorWireframe(0, chams.hand_wire_color);
                }
                zui::end_group_box();
            }
            zui::same_line();
            if (zui::begin_group_box("Weapon", hw)) {
                zui::checkbox("Enabled", chams.weapon_chams_enabled);
                if (zui::color_picker("Color", s_weapon_color)) NormalizeRGBA(chams.weapon_color, s_weapon_color);
                zui::combo("Material", chams.weapon_material, kMaterialNamesVM, kMaterialCountVM);
                if (zui::color_picker("Wire Color", s_weapon_wire_color)) {
                    NormalizeRGBA(chams.weapon_wire_color, s_weapon_wire_color);
                    features::chams::RecolorWireframe(1, chams.weapon_wire_color);
                }
                zui::end_group_box();
            }

            zui::end_group_box();
        }
    }

    void menu() {
        if (!globals::bMenuOpen.load()) return;

        zui::begin();

        if (zui::begin_window("Asteria", x, y, win_w, win_h)) {
            auto [avail_w, avail_h] = zui::get_content_region_avail();

            if (zui::begin_nested_window("Nav", avail_w, 50.f)) {
                auto btn_w = zui::calc_item_width(5);
                if (zui::button("Aimbot", btn_w, 26.f)) tab = TAB_AIMBOT;
                zui::same_line();
                if (zui::button("Visuals", btn_w, 26.f)) tab = TAB_VISUALS;
                zui::same_line();
                if (zui::button("Inventory", btn_w, 26.f)) tab = TAB_INVENTORY;
                zui::same_line();
                if (zui::button("Misc", btn_w, 26.f)) tab = TAB_MISC;
                zui::same_line();
                if (zui::button("Settings", btn_w, 26.f)) tab = TAB_SETTINGS;
                zui::end_nested_window();
            }

            if (zui::begin_nested_window("Main", avail_w, avail_h - 50)) {
                switch (tab) {
                    case TAB_AIMBOT: {
                        break;
                    }
                    case TAB_VISUALS: {
                        TabChams();
                        break;
                    }
                    case TAB_INVENTORY: {
                        break;
                    }
                    case TAB_MISC: {
                        break;
                    }
                    case TAB_SETTINGS: {
                        break;
                    }
                }
                zui::end_nested_window();
            }
            zui::end_window();
        }
        zui::end();
    }
}
