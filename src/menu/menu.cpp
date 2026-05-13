#include "menu.hpp"
#include "../utils/utils.hpp"
#include "../globals.hpp"
#include <zui/zui.hpp>

namespace menu {

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
                        bool bToggle = true;
                        auto w = zui::calc_item_width(2);
                        if (zui::begin_group_box("Main", w)) {
                            if (zui::checkbox("Toggle", bToggle)) {}

                            zui::end_group_box();
                        }
                        break;
                    }
                    case TAB_VISUALS: {
                        auto w = zui::calc_item_width(3);
                        if (zui::begin_group_box("Main", w)) {
                            bool bToggle = false;
                            if (zui::checkbox("Toggle", bToggle)) {}

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
