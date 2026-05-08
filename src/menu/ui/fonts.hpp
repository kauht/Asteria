#pragma once

#include <imgui.h>

namespace ui
{
    namespace fonts
    {
        // Font indices
        #define FONT_REGULAR 0
        #define FONT_MEDIUM 1
        #define FONT_BOLD 2
        #define FONT_SMALL 3
        #define FONT_TINY 4
        #define FONT_SEMI_BOLD 5
        #define FONT_COUNT 6

        // Initialize fonts
        // Returns true if fonts were loaded successfully
        bool init(ImGuiIO& io);

        // Get font by index
        ImFont* get(int index);
    }
}
