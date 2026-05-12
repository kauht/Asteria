#include "menu.hpp"
#include "render/render.hpp"
#include "ui/ui.hpp"
#include <imgui.h>

#include "../globals.hpp"

namespace menu {

    void menu() {
        bool open = globals::bMenuOpen.load();
        if (!open) return;

        ImGui::SetNextWindowSize(ImVec2(560.0f, 420.0f), ImGuiCond_FirstUseEver);
        ImGui::Begin("asteria", &open, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

        ImGui::TextUnformatted("Asteria");
        ImGui::Separator();

        ImGui::End();
    }

}
