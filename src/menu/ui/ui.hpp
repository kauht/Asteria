#pragma once
#include <imgui.h>

namespace ui {
    inline ImFont* font_main;
    inline ImFont* font_small;
    inline int current_tab = 0;
    inline float dpi_scale = 1.0f;

    void LoadFonts();
    void SetupStyle();

    bool Tab(const char* label, int index);
    bool Checkbox(const char* label, bool* v);
    void ColorPicker(const char* label, float* col);
    bool Combo(const char* label, int* current_item, const char* const items[], int items_count);

    void BeginGroup(const char* name, ImVec2 size);
    void EndGroup();
}
