#include "menu.hpp"

#include "ui/ui.hpp"
#include "fonts.hpp"
#include "../rendering/texture.hpp"
#include "../hooks/d3d11_hook.hpp"

namespace menu
{
    // Icon textures
    static ID3D11ShaderResourceView* g_icon_crosshair = nullptr;
    static ID3D11ShaderResourceView* g_icon_eye = nullptr;
    static ID3D11ShaderResourceView* g_icon_palette = nullptr;
    static ID3D11ShaderResourceView* g_icon_settings = nullptr;
    static ID3D11ShaderResourceView* g_icon_pfp = nullptr;
    static bool g_icons_loaded = false;
    
    static void load_icons()
    {
        if (g_icons_loaded) return;
        
        ID3D11Device* device = hooks::d3d11::get_device();
        if (!device) return;
        
        int w, h;
        rendering::load_texture_from_file("vendor/crosshair.png", device, &g_icon_crosshair, &w, &h);
        rendering::load_texture_from_file("vendor/eye.png", device, &g_icon_eye, &w, &h);
        rendering::load_texture_from_file("vendor/palette.png", device, &g_icon_palette, &w, &h);
        rendering::load_texture_from_file("vendor/settings.png", device, &g_icon_settings, &w, &h);
        rendering::load_texture_from_file("vendor/pfp.png", device, &g_icon_pfp, &w, &h);
        
        g_icons_loaded = true;
    }
    
    void render(ID3D11ShaderResourceView* blurred_background)
    {
        // Load icons on first frame
        load_icons();
        static bool open = true;
        static int tab = 1; // Start with Visuals selected (index 1)

        ::ui::anim = ImLerp(::ui::anim, 1.f, 0.15f);

        // DPI scaling
        const float dpi_scale = 1.5f;
        
        // Get the full viewport - the window IS the application
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        
        // Make the window fill the entire application window
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);  // No rounding on outer window
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        
        if (!ImGui::Begin(
            "##RatWare",
            &open,
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoScrollbar |
            ImGuiWindowFlags_NoBringToFrontOnFocus))
        {
            ImGui::PopStyleVar(2);
            ImGui::End();
            return;
        }

        ImDrawList* dl = ImGui::GetWindowDrawList();
        ImVec2 window_pos = ImGui::GetWindowPos();
        ImVec2 window_size = ImGui::GetWindowSize();

        // Draw blurred background if available
        if (blurred_background)
        {
            dl->AddImageRounded(
                blurred_background,
                window_pos,
                ImVec2(window_pos.x + window_size.x, window_pos.y + window_size.y),
                ImVec2(0, 0), ImVec2(1, 1),
                ImColor(255, 255, 255, 180),  // 70% opacity
                12.0f
            );
        }

        // Draw main window background with rounded corners (12px) - rgba(5,5,5,0.85)
        // This creates the base shape with rounded corners
        dl->AddRectFilled(
            window_pos,
            ImVec2(window_pos.x + window_size.x, window_pos.y + window_size.y),
            ImColor(5, 5, 5, 217),  // rgba(5,5,5,0.85) = 217 alpha
            12.0f
        );

        // Top bar background: rgba(40,40,40,0.4) with border bottom #658
        // Draw OVER the main background, respecting top corners
        const float top_bar_height = 50 * dpi_scale;
        ImVec2 top_bar_min = window_pos;
        ImVec2 top_bar_max = ImVec2(window_pos.x + window_size.x, window_pos.y + top_bar_height);
        
        // Draw top bar with only top corners rounded to match main background
        dl->AddRectFilled(
            top_bar_min,
            top_bar_max,
            ImColor(40, 40, 40, 102),  // rgba(40,40,40,0.4) = 102 alpha
            12.0f,
            ImDrawFlags_RoundCornersTop
        );

        // Border bottom: #658 (102, 85, 136)
        dl->AddLine(
            ImVec2(top_bar_min.x, top_bar_max.y),
            ImVec2(top_bar_max.x, top_bar_max.y),
            ImColor(102, 85, 136, 255),
            1.0f
        );

        // User profile section (left side of top bar) - centered vertically
        const float profile_x = 10 * dpi_scale;
        const float avatar_size = 26 * dpi_scale;
        
        // Calculate vertical centering
        const float profile_content_height = avatar_size;
        const float profile_y = (top_bar_height - profile_content_height) / 2;
        
        // Avatar - use pfp.png if loaded, otherwise circle placeholder
        ImVec2 avatar_center = ImVec2(
            window_pos.x + profile_x + avatar_size/2,
            window_pos.y + profile_y + avatar_size/2
        );
        
        if (g_icon_pfp)
        {
            dl->AddImageRounded(
                g_icon_pfp,
                ImVec2(window_pos.x + profile_x, window_pos.y + profile_y),
                ImVec2(window_pos.x + profile_x + avatar_size, window_pos.y + profile_y + avatar_size),
                ImVec2(0, 0), ImVec2(1, 1),
                ImColor(255, 255, 255, 255),
                avatar_size / 2  // Fully rounded (circle)
            );
        }
        else
        {
            // Fallback circle placeholder
            dl->AddCircleFilled(
                avatar_center,
                avatar_size/2,
                ImColor(80, 80, 80, 255)
            );
        }
        
        // Text positioning - vertically centered with avatar
        const float text_x = profile_x + avatar_size + 8 * dpi_scale;
        
        // Get font heights for proper centering
        ImFont* small_font = fonts::get(FONT_SMALL);
        ImFont* tiny_font = fonts::get(FONT_TINY);
        
        const float username_height = small_font->LegacySize;
        const float sub_height = tiny_font->LegacySize;
        const float text_gap = 2 * dpi_scale;
        const float total_text_height = username_height + text_gap + sub_height;
        const float text_y = profile_y + (avatar_size - total_text_height) / 2;
        
        // Username "Sammy" - Geist Regular 11px
        dl->AddText(
            small_font,
            small_font->LegacySize,
            ImVec2(window_pos.x + text_x, window_pos.y + text_y),
            ImColor(255, 255, 255, 255),
            "Sammy"
        );
        
        // Subscription info "28 days left" - Geist Regular 8px
        dl->AddText(
            tiny_font,
            tiny_font->LegacySize,
            ImVec2(window_pos.x + text_x, window_pos.y + text_y + username_height + text_gap),
            ImColor(255, 255, 255, 102),  // rgba(255,255,255,0.4) = 102 alpha
            "28 days left"
        );

        // Separator line (vertical)
        const float sep_x = 120 * dpi_scale;
        dl->AddLine(
            ImVec2(window_pos.x + sep_x, window_pos.y + 7 * dpi_scale),
            ImVec2(window_pos.x + sep_x, window_pos.y + 43 * dpi_scale),
            ImColor(255, 255, 255, 26),
            1.0f
        );

        // Navigation tabs - with icon placeholders
        const float tabs_start_x = 132 * dpi_scale;
        const float tab_y = 11 * dpi_scale;
        const float tab_height = 28 * dpi_scale;
        const float tab_spacing = 12 * dpi_scale;
        const float icon_size = 14 * dpi_scale;
        const float icon_text_gap = 4 * dpi_scale;
        
        ImGui::PushFont(fonts::get(FONT_MEDIUM));
        
        float current_x = tabs_start_x;
        
        // Tab: Aimbot
        {
            const char* label = "Aimbot";
            ImVec2 label_size = ImGui::CalcTextSize(label);
            const float tab_width = icon_size + icon_text_gap + label_size.x + 20 * dpi_scale;
            
            ImVec2 tab_pos = ImVec2(window_pos.x + current_x, window_pos.y + tab_y);
            bool is_selected = (tab == 0);
            bool hovered = ImGui::IsMouseHoveringRect(tab_pos, ImVec2(tab_pos.x + tab_width, tab_pos.y + tab_height));
            
            if (is_selected)
            {
                dl->AddRectFilled(
                    tab_pos,
                    ImVec2(tab_pos.x + tab_width, tab_pos.y + tab_height),
                    ImColor(255, 255, 255, 15),
                    2.0f
                );
            }
            
            // Icon placeholder (circle)
            dl->AddCircleFilled(
                ImVec2(tab_pos.x + 10 * dpi_scale + icon_size/2, tab_pos.y + tab_height/2),
                icon_size/2,
                ImColor(255, 255, 255, is_selected ? 204 : 102),
                12
            );
            
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, is_selected ? 0.8f : 0.4f));
            dl->AddText(
                ImVec2(tab_pos.x + 10 * dpi_scale + icon_size + icon_text_gap, tab_pos.y + (tab_height - label_size.y) / 2),
                ImGui::GetColorU32(ImGuiCol_Text),
                label
            );
            ImGui::PopStyleColor();
            
            if (hovered && ImGui::IsMouseClicked(0))
                tab = 0;
                
            current_x += tab_width + tab_spacing;
        }
        
        // Tab: Visuals
        {
            const char* label = "Visuals";
            ImVec2 label_size = ImGui::CalcTextSize(label);
            const float tab_width = icon_size + icon_text_gap + label_size.x + 20 * dpi_scale;
            
            ImVec2 tab_pos = ImVec2(window_pos.x + current_x, window_pos.y + tab_y);
            bool is_selected = (tab == 1);
            bool hovered = ImGui::IsMouseHoveringRect(tab_pos, ImVec2(tab_pos.x + tab_width, tab_pos.y + tab_height));
            
            if (is_selected)
            {
                dl->AddRectFilled(
                    tab_pos,
                    ImVec2(tab_pos.x + tab_width, tab_pos.y + tab_height),
                    ImColor(255, 255, 255, 15),
                    2.0f
                );
            }
            
            // Icon placeholder (circle)
            dl->AddCircleFilled(
                ImVec2(tab_pos.x + 10 * dpi_scale + icon_size/2, tab_pos.y + tab_height/2),
                icon_size/2,
                ImColor(255, 255, 255, is_selected ? 204 : 102),
                12
            );
            
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, is_selected ? 0.8f : 0.4f));
            dl->AddText(
                ImVec2(tab_pos.x + 10 * dpi_scale + icon_size + icon_text_gap, tab_pos.y + (tab_height - label_size.y) / 2),
                ImGui::GetColorU32(ImGuiCol_Text),
                label
            );
            ImGui::PopStyleColor();
            
            if (hovered && ImGui::IsMouseClicked(0))
                tab = 1;
                
            current_x += tab_width + tab_spacing;
        }
        
        // Tab: Skins
        {
            const char* label = "Skins";
            ImVec2 label_size = ImGui::CalcTextSize(label);
            const float tab_width = icon_size + icon_text_gap + label_size.x + 20 * dpi_scale;
            
            ImVec2 tab_pos = ImVec2(window_pos.x + current_x, window_pos.y + tab_y);
            bool is_selected = (tab == 2);
            bool hovered = ImGui::IsMouseHoveringRect(tab_pos, ImVec2(tab_pos.x + tab_width, tab_pos.y + tab_height));
            
            if (is_selected)
            {
                dl->AddRectFilled(
                    tab_pos,
                    ImVec2(tab_pos.x + tab_width, tab_pos.y + tab_height),
                    ImColor(255, 255, 255, 15),
                    2.0f
                );
            }
            
            // Icon placeholder (circle)
            dl->AddCircleFilled(
                ImVec2(tab_pos.x + 10 * dpi_scale + icon_size/2, tab_pos.y + tab_height/2),
                icon_size/2,
                ImColor(255, 255, 255, is_selected ? 204 : 102),
                12
            );
            
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, is_selected ? 0.8f : 0.4f));
            dl->AddText(
                ImVec2(tab_pos.x + 10 * dpi_scale + icon_size + icon_text_gap, tab_pos.y + (tab_height - label_size.y) / 2),
                ImGui::GetColorU32(ImGuiCol_Text),
                label
            );
            ImGui::PopStyleColor();
            
            if (hovered && ImGui::IsMouseClicked(0))
                tab = 2;
                
            current_x += tab_width + tab_spacing;
        }
        
        // Tab: Misc
        {
            const char* label = "Misc";
            ImVec2 label_size = ImGui::CalcTextSize(label);
            const float tab_width = icon_size + icon_text_gap + label_size.x + 20 * dpi_scale;
            
            ImVec2 tab_pos = ImVec2(window_pos.x + current_x, window_pos.y + tab_y);
            bool is_selected = (tab == 3);
            bool hovered = ImGui::IsMouseHoveringRect(tab_pos, ImVec2(tab_pos.x + tab_width, tab_pos.y + tab_height));
            
            if (is_selected)
            {
                dl->AddRectFilled(
                    tab_pos,
                    ImVec2(tab_pos.x + tab_width, tab_pos.y + tab_height),
                    ImColor(255, 255, 255, 15),
                    2.0f
                );
            }
            
            // Icon placeholder (circle)
            dl->AddCircleFilled(
                ImVec2(tab_pos.x + 10 * dpi_scale + icon_size/2, tab_pos.y + tab_height/2),
                icon_size/2,
                ImColor(255, 255, 255, is_selected ? 204 : 102),
                12
            );
            
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, is_selected ? 0.8f : 0.4f));
            dl->AddText(
                ImVec2(tab_pos.x + 10 * dpi_scale + icon_size + icon_text_gap, tab_pos.y + (tab_height - label_size.y) / 2),
                ImGui::GetColorU32(ImGuiCol_Text),
                label
            );
            ImGui::PopStyleColor();
            
            if (hovered && ImGui::IsMouseClicked(0))
                tab = 3;
                
            current_x += tab_width + tab_spacing;
        }
        
        // Tab: Config
        {
            const char* label = "Config";
            ImVec2 label_size = ImGui::CalcTextSize(label);
            const float tab_width = icon_size + icon_text_gap + label_size.x + 20 * dpi_scale;
            
            ImVec2 tab_pos = ImVec2(window_pos.x + current_x, window_pos.y + tab_y);
            bool is_selected = (tab == 4);
            bool hovered = ImGui::IsMouseHoveringRect(tab_pos, ImVec2(tab_pos.x + tab_width, tab_pos.y + tab_height));
            
            if (is_selected)
            {
                dl->AddRectFilled(
                    tab_pos,
                    ImVec2(tab_pos.x + tab_width, tab_pos.y + tab_height),
                    ImColor(255, 255, 255, 15),
                    2.0f
                );
            }
            
            // Icon placeholder (circle)
            dl->AddCircleFilled(
                ImVec2(tab_pos.x + 10 * dpi_scale + icon_size/2, tab_pos.y + tab_height/2),
                icon_size/2,
                ImColor(255, 255, 255, is_selected ? 204 : 102),
                12
            );
            
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, is_selected ? 0.8f : 0.4f));
            dl->AddText(
                ImVec2(tab_pos.x + 10 * dpi_scale + icon_size + icon_text_gap, tab_pos.y + (tab_height - label_size.y) / 2),
                ImGui::GetColorU32(ImGuiCol_Text),
                label
            );
            ImGui::PopStyleColor();
            
            if (hovered && ImGui::IsMouseClicked(0))
                tab = 4;
        }
        
        ImGui::PopFont();

        // Main content area
        const float content_padding = 10 * dpi_scale;
        const float content_y = top_bar_height + content_padding;
        const float content_width = window_size.x - content_padding * 2;
        const float content_height = window_size.y - content_y - content_padding;
        
        ImGui::SetCursorPos(ImVec2(content_padding, content_y));
        
        // Content child window: rgba(40,40,40,0.4) with border rgba(40,40,40,0.6)
        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(40.0f/255.0f, 40.0f/255.0f, 40.0f/255.0f, 0.4f));
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(40.0f/255.0f, 40.0f/255.0f, 40.0f/255.0f, 0.6f));
        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 4.0f);  // Reduced from 8.0f to 4.0f
        
        ImGui::BeginChild("##content", ImVec2(content_width, content_height), true, ImGuiWindowFlags_NoScrollbar);
        
        ImGui::PushFont(fonts::get(FONT_REGULAR));
        
        // Tab content
        switch (tab)
        {
            case 0: // Aimbot
                ImGui::SetCursorPos(ImVec2(20 * dpi_scale, 20 * dpi_scale));
                ImGui::Text("Aimbot Settings");
                break;
                
            case 1: // Visuals
                ImGui::SetCursorPos(ImVec2(20 * dpi_scale, 20 * dpi_scale));
                ImGui::Text("Visuals Settings");
                break;
                
            case 2: // Skins
                ImGui::SetCursorPos(ImVec2(20 * dpi_scale, 20 * dpi_scale));
                ImGui::Text("Skin Changer");
                break;
                
            case 3: // Misc
                ImGui::SetCursorPos(ImVec2(20 * dpi_scale, 20 * dpi_scale));
                ImGui::Text("Miscellaneous");
                break;
                
            case 4: // Config
                ImGui::SetCursorPos(ImVec2(20 * dpi_scale, 20 * dpi_scale));
                ImGui::Text("Configuration");
                break;
        }
        
        ImGui::PopFont();
        
        ImGui::EndChild();
        
        ImGui::PopStyleVar();
        ImGui::PopStyleColor(2);

        ImGui::End();
        ImGui::PopStyleVar(2); // WindowRounding and WindowPadding
    }
}
