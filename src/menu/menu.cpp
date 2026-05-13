#include "menu.hpp"
#include "ui/ui.hpp"
#include "../utils/utils.hpp"
#include "../globals.hpp"

namespace menu {
    void menu() {
        if (!globals::bMenuOpen.load()) return;

        ImGui::PushFont(ui::font_main);
        float scale = ui::dpi_scale;
        ImGui::SetNextWindowSize(ImVec2(1100.f * scale, 700.f * scale), ImGuiCond_Always);

        if (ImGui::Begin("asteria", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar)) {
            ImDrawList* draw = ImGui::GetWindowDrawList();
            ImVec2 pos = ImGui::GetWindowPos();
            ImVec2 size = ImGui::GetWindowSize();
            float nav_h = 62.f * scale;

            // Background & Navbar
            draw->AddRectFilled(pos, ImVec2(pos.x + size.x, pos.y + size.y), ImColor(16, 16, 20), 6.f * scale);
            draw->AddRectFilled(pos, ImVec2(pos.x + size.x, pos.y + nav_h), ImColor(20, 20, 26), 6.f * scale, ImDrawFlags_RoundCornersTop);
            draw->AddLine(ImVec2(pos.x, pos.y + nav_h), ImVec2(pos.x + size.x, pos.y + nav_h), ImColor(48, 48, 58));

            // Tabs
            ImGui::SetCursorPos(ImVec2(200.f * scale, 15.f * scale));
            const char* tabs[] = { "Rage", "Legit", "Visuals", "Misc", "Inventory", "Config" };
            for (int i = 0; i < 6; i++) { ui::Tab(tabs[i], i); ImGui::SameLine(); }

            // Layout Constants
            float start_y = 85.f * scale;
            float gw = 520.f * scale;
            float gh = 585.f * scale;
            float sp = 18.f * scale;

            // Only rendering the Visuals tab for now to keep things clean
            if (ui::current_tab == 2) {
                // LEFT COLUMN
                ImGui::SetCursorPos(ImVec2(20.f * scale, start_y));
                ui::BeginGroup("Main", ImVec2(gw, gh));

                static bool box = false; static float box_col[4] = {1.f, 1.f, 1.f, 1.f};
                ui::Checkbox("Bounding Box", &box); ui::ColorPicker("##bc", box_col);

                static bool skel = false;
                ui::Checkbox("Skeleton", &skel);

                static bool health = false;
                ui::Checkbox("Health ESP", &health);

                static bool tracers = false;
                ui::Checkbox("Bullet Tracers", &tracers);

                ui::EndGroup();

                // RIGHT COLUMN
                ImGui::SetCursorPos(ImVec2(20.f * scale + gw + sp, start_y));
                ui::BeginGroup("Other", ImVec2(gw, gh));

                static bool chams = false; static float cham_col[4] = {1.f, 1.f, 1.f, 1.f};
                ui::Checkbox("Chams", &chams); ui::ColorPicker("##cc", cham_col);

                static int mat = 0;
                const char* mats[] = { "Textured", "Flat", "Glow" };
                ui::Combo("Material", &mat, mats, 3);

                static bool glow = false; static float glow_col[4] = {1.f, 1.f, 1.f, 1.f};
                ui::Checkbox("Glow", &glow); ui::ColorPicker("##gc", glow_col);

                static bool world = false; static float world_col[4] = {1.f, 1.f, 1.f, 1.f};
                ui::Checkbox("World Modulation", &world); ui::ColorPicker("##wc", world_col);

                static bool sky = false; static float sky_col[4] = {1.f, 1.f, 1.f, 1.f};
                ui::Checkbox("Skybox", &sky); ui::ColorPicker("##skyc", sky_col);

                ui::EndGroup();
            }
            else if (ui::current_tab == 5) {
                ImGui::SetCursorPos(ImVec2(20.f * scale, start_y));
                ui::BeginGroup("Main", ImVec2(gw, gh));
                ImGui::TextColored(ImColor(200, 50, 50), "Config system is currently detached.");
                ImGui::TextDisabled("Modify src/menu/menu.cpp to reconnect variables.");
                ui::EndGroup();
            }
            else {
                ImGui::SetCursorPos(ImVec2(20.f * scale, start_y));
                ui::BeginGroup("Main", ImVec2(gw, gh));
                ImGui::Text("Tab content placeholder...");
                ui::EndGroup();
            }
        }
        ImGui::End();
        ImGui::PopFont();
    }
}
