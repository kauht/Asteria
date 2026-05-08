#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS

#include "imgui.h"
#include "imgui_internal.h"

#include <functional>
#include <string>
#include <unordered_map>

#include "fonts.hpp"

#define to_vec4(r, g, b, a) ImColor((r) / 255.f, (g) / 255.f, (b) / 255.f, (a))

namespace ui
{
    // Color scheme - Exact colors from Figma
    inline int accent[4] = { 102, 85, 136, 255 }; // #658 border color
    inline float anim = 0.f;

    inline ImColor get_accent(float a = 1.f)
    {
        return to_vec4(accent[0], accent[1], accent[2], a * 255.0f);
    }

    // Style initialization
    void init_style();

    void group_box(const char* name, ImVec2 size, std::function<void()> content);
    void group_box_alt(const char* name, ImVec2 size, std::function<void()> content, ImVec2 padding = ImVec2(12, 12));
    void list_box(const char* name, ImVec2 size, std::function<void()> content, ImVec2 padding = ImVec2(8, 8));
    void popup(const char* id, const char* name, std::function<void()> content);
    void colored_rect(const char* id, ImColor color, ImVec2 size);
    void separator(const char* label = nullptr);

    bool checkbox(const char* label, bool* v, const char* hint = "");
    bool button(const char* label, const char* icon = "", ImVec2 size = ImVec2(0, 0));
    bool button_alt(const char* icon, ImVec2 size = ImVec2(0, 0));

    bool combo(const char* label, int* current, const char* const items[], int count);
    bool combo(const char* label, int* current, const char* items_null_separated);

    bool selectable(const char* label, bool selected, ImGuiSelectableFlags flags = 0, ImVec2 size = ImVec2(0, 0));
    bool selectable(const char* label, bool* p_selected, ImGuiSelectableFlags flags = 0, ImVec2 size = ImVec2(0, 0));

    bool tab(const char* icon, const char* label, bool selected, float rounding = 0.f, ImDrawFlags flags = 0);
    bool sub_tab(const char* label, bool selected);

    void image(
        ImTextureID tex,
        ImVec2 size,
        float rounding,
        ImDrawFlags flags,
        ImVec2 uv0 = ImVec2(0, 0),
        ImVec2 uv1 = ImVec2(1, 1),
        ImVec4 tint = ImVec4(1, 1, 1, 1),
        ImVec4 border = ImVec4(0, 0, 0, 0)
    );
}
