#include "../ui/fonts.hpp"
#include <vector>

// Include the embedded font data
#include "../fonts.hpp"

namespace ui
{
    namespace fonts
    {
        static std::vector<ImFont*> loaded_fonts;

        bool init(ImGuiIO& io)
        {
            loaded_fonts.clear();
            loaded_fonts.resize(FONT_COUNT, nullptr);

            ImFontConfig font_config;
            font_config.PixelSnapH = false;
            font_config.OversampleH = 3;
            font_config.OversampleV = 3;
            font_config.RasterizerMultiply = 1.0f;

            // Unicode ranges for extended character support
            static const ImWchar ranges[] = {
                0x0020, 0x00FF, // Basic Latin + Latin Supplement
                0x0400, 0x052F, // Cyrillic + Cyrillic Supplement
                0x2DE0, 0x2DFF, // Cyrillic Extended-A
                0xA640, 0xA69F, // Cyrillic Extended-B
                0,
            };

            font_config.GlyphRanges = ranges;

            // Load Geist fonts from embedded byte arrays
            // Regular font (16px) - main UI text, increased from 12px
            loaded_fonts[FONT_REGULAR] = io.Fonts->AddFontFromMemoryTTF(
                (void*)geist_regular, sizeof(geist_regular), 16.0f, &font_config, ranges
            );
            
            // Medium font (16px) - tabs and buttons, increased from 12px
            loaded_fonts[FONT_MEDIUM] = io.Fonts->AddFontFromMemoryTTF(
                (void*)geist_regular, sizeof(geist_regular), 16.0f, &font_config, ranges
            );
            
            // Bold font (18px) - headers, increased from 14px
            loaded_fonts[FONT_BOLD] = io.Fonts->AddFontFromMemoryTTF(
                (void*)geist_regular, sizeof(geist_regular), 18.0f, &font_config, ranges
            );
            
            // Small font (14px) - user name, increased from 11px
            loaded_fonts[FONT_SMALL] = io.Fonts->AddFontFromMemoryTTF(
                (void*)geist_regular, sizeof(geist_regular), 14.0f, &font_config, ranges
            );
            
            // Tiny font (11px) - subscription info, increased from 8px
            loaded_fonts[FONT_TINY] = io.Fonts->AddFontFromMemoryTTF(
                (void*)geist_regular, sizeof(geist_regular), 11.0f, &font_config, ranges
            );
            
            // Semi-bold font (17px), increased from 13px
            loaded_fonts[FONT_SEMI_BOLD] = io.Fonts->AddFontFromMemoryTTF(
                (void*)geist_regular, sizeof(geist_regular), 17.0f, &font_config, ranges
            );

            return true;
        }

        ImFont* get(int index)
        {
            if (index >= 0 && index < loaded_fonts.size() && loaded_fonts[index])
                return loaded_fonts[index];
            
            return ImGui::GetFont();
        }
    }
}
