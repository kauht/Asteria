#include "menu.hpp"
#include "../utils/utils.hpp"
#include "../globals.hpp"
#include <zui/zui.hpp>

namespace menu {

    static float x = 200.f, y = 200.f, w = 400.f, h = 400.f;

    void menu() {
        if (!globals::bMenuOpen.load()) return;

        zui::begin();

        if (zui::begin_window("Asteria", x, y, w, h)) {
            if (zui::button("wsg tyo", 100.f, 25.f)) {}
            zui::end_window();
        }
        zui::end();
    }
}
