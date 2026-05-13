#include "ui.hpp"
#include "geist_medium.hpp"
#include <imgui_internal.h>

namespace ui {
    static ImColor accent = ImColor(102, 85, 136);
    static float SCALE(float v) { return v * dpi_scale; }

    void LoadFonts() {
        ImGuiIO& io = ImGui::GetIO();
        io.Fonts->Clear();
        ImFontConfig cfg{};
        cfg.FontDataOwnedByAtlas = false;

        font_main  = io.Fonts->AddFontFromMemoryTTF((void*)geist_medium.data(), (int)geist_medium.size(), SCALE(16.f), &cfg);
        font_small = io.Fonts->AddFontFromMemoryTTF((void*)geist_medium.data(), (int)geist_medium.size(), SCALE(13.f), &cfg);
    }

    void SetupStyle() {
        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowPadding = ImVec2(0, 0);
        style.FramePadding = ImVec2(SCALE(8), SCALE(4));
        style.ItemSpacing = ImVec2(SCALE(10), SCALE(10));
        style.WindowRounding = SCALE(4.f);
        style.ChildRounding = SCALE(4.f);
        style.FrameRounding = SCALE(3.f);

        ImVec4* colors = style.Colors;
        colors[ImGuiCol_WindowBg] = ImColor(16, 16, 20);
        colors[ImGuiCol_ChildBg] = ImColor(22, 22, 28);
        colors[ImGuiCol_Border] = ImColor(48, 48, 58);
        colors[ImGuiCol_FrameBg] = ImColor(28, 28, 36);
        colors[ImGuiCol_PopupBg] = ImColor(22, 22, 28);
        colors[ImGuiCol_Header] = ImColor(35, 35, 45);
        colors[ImGuiCol_HeaderHovered] = ImColor(45, 45, 55);
        colors[ImGuiCol_Text] = ImColor(235, 235, 235);
    }

    bool Tab(const char* label, int index) {
        ImVec2 pos = ImGui::GetCursorScreenPos();
        ImVec2 size = ImVec2(SCALE(85), SCALE(32));
        bool pressed = ImGui::InvisibleButton(label, size);
        if (pressed) current_tab = index;

        ImDrawList* draw = ImGui::GetWindowDrawList();
        bool active = current_tab == index;
        ImColor tc = active ? ImColor(235, 235, 235) : (ImGui::IsItemHovered() ? ImColor(180, 180, 180) : ImColor(120, 120, 120));

        if (active)
            draw->AddRectFilled(ImVec2(pos.x, pos.y + SCALE(29)), ImVec2(pos.x + size.x, pos.y + SCALE(32)), accent, SCALE(2));

        ImVec2 ts = font_main->CalcTextSizeA(SCALE(16.f), FLT_MAX, 0.f, label);
        draw->AddText(font_main, SCALE(16.f), ImVec2(pos.x + (size.x - ts.x) * 0.5f, pos.y + (size.y - ts.y) * 0.5f), tc, label);
        return pressed;
    }

    bool Checkbox(const char* label, bool* v) {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        ImGuiID id = window->GetID(label);
        ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
        ImVec2 pos = window->DC.CursorPos;

        const float check_sz = SCALE(14.f);
        const ImRect bb(pos, ImVec2(pos.x + check_sz + SCALE(10) + label_size.x, pos.y + check_sz));
        ImGui::ItemSize(bb);
        if (!ImGui::ItemAdd(bb, id)) return false;

        bool hovered, held;
        bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held);
        if (pressed) *v = !(*v);

        window->DrawList->AddRectFilled(pos, ImVec2(pos.x + check_sz, pos.y + check_sz), ImColor(28, 28, 36), SCALE(2));
        window->DrawList->AddRect(pos, ImVec2(pos.x + check_sz, pos.y + check_sz), ImColor(48, 48, 58), SCALE(2));

        if (*v)
            window->DrawList->AddRectFilled(ImVec2(pos.x + SCALE(3), pos.y + SCALE(3)), ImVec2(pos.x + check_sz - SCALE(3), pos.y + check_sz - SCALE(3)), accent, SCALE(1));

        window->DrawList->AddText(font_main, SCALE(14.f), ImVec2(pos.x + check_sz + SCALE(10), pos.y - SCALE(1)), ImColor(235, 235, 235), label);
        return pressed;
    }

    void ColorPicker(const char* label, float* col) {
        ImGui::SameLine(ImGui::GetWindowWidth() - SCALE(35));
        ImGui::ColorEdit4(label, col, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoSidePreview);
    }

    bool Combo(const char* label, int* current_item, const char* const items[], int items_count) {
        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x - SCALE(15));
        return ImGui::Combo(label, current_item, items, items_count);
    }

    void BeginGroup(const char* name, ImVec2 size) {
        ImDrawList* draw = ImGui::GetWindowDrawList();
        ImVec2 pos = ImGui::GetCursorScreenPos();

        draw->AddRectFilled(pos, ImVec2(pos.x + size.x, pos.y + size.y), ImColor(22, 22, 28), SCALE(4));
        draw->AddRect(pos, ImVec2(pos.x + size.x, pos.y + size.y), ImColor(48, 48, 58), SCALE(4));

        ImVec2 ts = font_small->CalcTextSizeA(SCALE(13.f), FLT_MAX, 0.f, name);
        draw->AddRectFilled(ImVec2(pos.x + SCALE(10), pos.y - SCALE(7)), ImVec2(pos.x + SCALE(16) + ts.x, pos.y + SCALE(7)), ImColor(16, 16, 20));
        draw->AddText(font_small, SCALE(13.f), ImVec2(pos.x + SCALE(13), pos.y - SCALE(7)), accent, name);

        ImGui::BeginChild(name, size, false, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBackground);
        ImGui::ItemSize(ImVec2(0, SCALE(20)));
        ImGui::Indent(SCALE(15));
    }

    void EndGroup() {
        ImGui::Unindent(SCALE(15));
        ImGui::EndChild();
    }
}
