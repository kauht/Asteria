#include "menu.hpp"
#include "../utils/utils.hpp"
#include "../globals.hpp"
#include <zui/zui.hpp>

namespace menu {

    static bool bToggleAimbot = true;
    static bool bToggleVisuals = false;

    static float x = 400.f, y = 400.f, w = 700.f, h = 500.f;
    static int tab = 0;
    enum {
        TAB_AIMBOT,
        TAB_VISUALS,
        TAB_INVENTORY,
        TAB_MISC,
        TAB_SETTINGS
    };
    void menu() {
        if (!globals::bMenuOpen.load()) return;

        zui::begin();

        if (zui::begin_window("Asteria", x, y, w, h)) {

            auto& style = zui::get_style();
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

            if (zui::begin_nested_window("Main", avail_w, avail_h-50)) {
                switch (tab) {
                    case TAB_AIMBOT: {
                        auto w = zui::calc_item_width(2);
                        if (zui::begin_group_box("Main", w)) {
                            if (zui::checkbox("Toggle", globals::bTest)) {}

                            zui::end_group_box();
                        }
                        break;
                    }
                    case TAB_VISUALS: {
                        auto w = zui::calc_item_width(2);
                        auto& chams = config::g_config.chams;

                        static zdraw::rgba s_enemy_vis_color;
                        static zdraw::rgba s_enemy_occ_color;
                        static zdraw::rgba s_team_vis_color;
                        static zdraw::rgba s_team_occ_color;
                        static zdraw::rgba s_viewmodel_color;
                        static bool s_colors_init = false;
                        if (!s_colors_init) {
                            s_enemy_vis_color = zdraw::rgba(uint8_t(chams.enemy_vis_color.r*255.f), uint8_t(chams.enemy_vis_color.g*255.f), uint8_t(chams.enemy_vis_color.b*255.f), uint8_t(chams.enemy_vis_color.a*255.f));
                            s_enemy_occ_color = zdraw::rgba(uint8_t(chams.enemy_occ_color.r*255.f), uint8_t(chams.enemy_occ_color.g*255.f), uint8_t(chams.enemy_occ_color.b*255.f), uint8_t(chams.enemy_occ_color.a*255.f));
                            s_team_vis_color = zdraw::rgba(uint8_t(chams.team_vis_color.r*255.f), uint8_t(chams.team_vis_color.g*255.f), uint8_t(chams.team_vis_color.b*255.f), uint8_t(chams.team_vis_color.a*255.f));
                            s_team_occ_color = zdraw::rgba(uint8_t(chams.team_occ_color.r*255.f), uint8_t(chams.team_occ_color.g*255.f), uint8_t(chams.team_occ_color.b*255.f), uint8_t(chams.team_occ_color.a*255.f));
                            s_viewmodel_color = zdraw::rgba(uint8_t(chams.viewmodel_color.r*255.f), uint8_t(chams.viewmodel_color.g*255.f), uint8_t(chams.viewmodel_color.b*255.f), uint8_t(chams.viewmodel_color.a*255.f));
                            s_colors_init = true;
                        }

                        if (zui::begin_group_box("Viewmodel", w)) {
                            zui::checkbox("Weapon", chams.weapon_chams_enabled);
                            zui::checkbox("Hands", chams.hand_chams_enabled);

                            if (zui::color_picker("Color", s_viewmodel_color)) {
                                chams.viewmodel_color.r = s_viewmodel_color.r / 255.f;
                                chams.viewmodel_color.g = s_viewmodel_color.g / 255.f;
                                chams.viewmodel_color.b = s_viewmodel_color.b / 255.f;
                                chams.viewmodel_color.a = s_viewmodel_color.a / 255.f;
                            }

                            static const char* vm_materials[] = { "Flat", "Glow", "Electric" };
                            zui::combo("Material", chams.viewmodel_material, vm_materials, 3);

                            zui::end_group_box();
                        }

                        if (zui::begin_group_box("Enemy", w)) {
                            zui::checkbox("Visible", chams.enemy_vis_enabled);
                            zui::checkbox("Occluded", chams.enemy_occ_enabled);

                            if (zui::color_picker("Visible Color", s_enemy_vis_color)) {
                                chams.enemy_vis_color.r = s_enemy_vis_color.r / 255.f;
                                chams.enemy_vis_color.g = s_enemy_vis_color.g / 255.f;
                                chams.enemy_vis_color.b = s_enemy_vis_color.b / 255.f;
                                chams.enemy_vis_color.a = s_enemy_vis_color.a / 255.f;
                            }

                            if (zui::color_picker("Occluded Color", s_enemy_occ_color)) {
                                chams.enemy_occ_color.r = s_enemy_occ_color.r / 255.f;
                                chams.enemy_occ_color.g = s_enemy_occ_color.g / 255.f;
                                chams.enemy_occ_color.b = s_enemy_occ_color.b / 255.f;
                                chams.enemy_occ_color.a = s_enemy_occ_color.a / 255.f;
                            }

                            static const char* materials[] = { "Flat", "Glow", "Electric" };
                            zui::combo("Visible", chams.enemy_vis_material, materials, 3);
                            zui::combo("Occluded", chams.enemy_occ_material, materials, 3);

                            zui::end_group_box();
                        }

                        zui::same_line();

                        if (zui::begin_group_box("Team", w)) {
                            zui::checkbox("Visible", chams.team_vis_enabled);
                            zui::checkbox("Occluded", chams.team_occ_enabled);

                            if (zui::color_picker("Visible Color", s_team_vis_color)) {
                                chams.team_vis_color.r = s_team_vis_color.r / 255.f;
                                chams.team_vis_color.g = s_team_vis_color.g / 255.f;
                                chams.team_vis_color.b = s_team_vis_color.b / 255.f;
                                chams.team_vis_color.a = s_team_vis_color.a / 255.f;
                            }

                            if (zui::color_picker("Occluded Color", s_team_occ_color)) {
                                chams.team_occ_color.r = s_team_occ_color.r / 255.f;
                                chams.team_occ_color.g = s_team_occ_color.g / 255.f;
                                chams.team_occ_color.b = s_team_occ_color.b / 255.f;
                                chams.team_occ_color.a = s_team_occ_color.a / 255.f;
                            }

                            static const char* materials[] = { "Flat", "Glow", "Electric" };
                            zui::combo("Visible", chams.team_vis_material, materials, 3);
                            zui::combo("Occluded", chams.team_occ_material, materials, 3);

                            zui::end_group_box();
                        }

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
