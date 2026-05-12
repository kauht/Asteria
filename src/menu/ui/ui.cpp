#include "ui.hpp"
#include <imgui.h>

namespace ui {

    void SetupStyle() {
        ImGui::StyleColorsDark();

        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowRounding = 6.0f;
        style.ChildRounding = 6.0f;
        style.FrameRounding = 4.0f;
        style.PopupRounding = 4.0f;
        style.ScrollbarRounding = 6.0f;
        style.GrabRounding = 4.0f;
        style.TabRounding = 4.0f;
        style.WindowBorderSize = 0.0f;
        style.FrameBorderSize = 0.0f;
        style.WindowPadding = ImVec2(12.0f, 12.0f);
        style.FramePadding = ImVec2(10.0f, 4.0f);
        style.ItemSpacing = ImVec2(8.0f, 6.0f);
        style.ItemInnerSpacing = ImVec2(6.0f, 4.0f);
        style.WindowTitleAlign = ImVec2(0.5f, 0.5f);

        ImVec4* colors = style.Colors;
        colors[ImGuiCol_Text] = ImVec4(0.92f, 0.92f, 0.95f, 1.00f);
        colors[ImGuiCol_TextDisabled] = ImVec4(0.55f, 0.55f, 0.60f, 1.00f);
        colors[ImGuiCol_WindowBg] = ImVec4(0.09f, 0.10f, 0.12f, 0.98f);
        colors[ImGuiCol_ChildBg] = ImVec4(0.08f, 0.09f, 0.10f, 1.00f);
        colors[ImGuiCol_PopupBg] = ImVec4(0.10f, 0.11f, 0.13f, 0.98f);
        colors[ImGuiCol_Border] = ImVec4(0.20f, 0.22f, 0.26f, 1.00f);
        colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.18f, 0.21f, 1.00f);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.21f, 0.24f, 0.28f, 1.00f);
        colors[ImGuiCol_FrameBgActive] = ImVec4(0.24f, 0.27f, 0.31f, 1.00f);
        colors[ImGuiCol_TitleBg] = ImVec4(0.08f, 0.09f, 0.11f, 1.00f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(0.10f, 0.11f, 0.14f, 1.00f);
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.06f, 0.07f, 0.08f, 1.00f);
        colors[ImGuiCol_Button] = ImVec4(0.18f, 0.20f, 0.24f, 1.00f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(0.25f, 0.28f, 0.33f, 1.00f);
        colors[ImGuiCol_ButtonActive] = ImVec4(0.30f, 0.34f, 0.39f, 1.00f);
        colors[ImGuiCol_Header] = ImVec4(0.18f, 0.20f, 0.24f, 1.00f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(0.25f, 0.28f, 0.33f, 1.00f);
        colors[ImGuiCol_HeaderActive] = ImVec4(0.30f, 0.34f, 0.39f, 1.00f);
        colors[ImGuiCol_CheckMark] = ImVec4(0.45f, 0.68f, 1.00f, 1.00f);
        colors[ImGuiCol_SliderGrab] = ImVec4(0.32f, 0.54f, 0.92f, 1.00f);
        colors[ImGuiCol_SliderGrabActive] = ImVec4(0.43f, 0.66f, 1.00f, 1.00f);
        colors[ImGuiCol_Tab] = ImVec4(0.14f, 0.16f, 0.19f, 1.00f);
        colors[ImGuiCol_TabHovered] = ImVec4(0.25f, 0.28f, 0.33f, 1.00f);
        colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.23f, 0.27f, 1.00f);
        colors[ImGuiCol_TabUnfocused] = ImVec4(0.12f, 0.13f, 0.16f, 1.00f);
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.16f, 0.18f, 0.21f, 1.00f);
    }

}
