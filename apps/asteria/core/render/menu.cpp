#include "menu.hpp"
#include "../../globals.hpp"
#include "font/geist.hpp"
#include "shaders/blur.hpp"

#include <imgui.h>
/// ! CAUTION | AI GENERATED | NEEDS MANUAL REVIEW !

namespace asteria::core::render::menu {

static constexpr float WINDOW_W = 620.0f;
static constexpr float WINDOW_H = 460.0f;
static constexpr float TAB_H = 36.0f;

// ---- Helpers ----

// Section with a dim ALL-CAPS label and a hairline separator.
// ChildRounding is pushed before BeginChild and popped after EndChild — correct context.
static void begin_section(const char* title) {
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 0.0f);
    ImGui::BeginChild(title, ImVec2(0.0f, 0.0f), ImGuiChildFlags_AutoResizeY);
    ImGui::TextDisabled("%s", title);
    ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(1.0f, 1.0f, 1.0f, 0.06f));
    ImGui::Separator();
    ImGui::PopStyleColor();
    ImGui::Spacing();
}

static void end_section() {
    ImGui::Spacing();
    ImGui::EndChild();
    ImGui::PopStyleVar(); // matches the ChildRounding push in begin_section
    ImGui::Spacing();
}

// ---- Theme ----

static void apply_theme() {
    ImVec4* c = ImGui::GetStyle().Colors;

    const ImVec4 bg = {asteria::g_bg_color[0], asteria::g_bg_color[1], asteria::g_bg_color[2], asteria::g_bg_color[3]};
    const ImVec4 accent = {asteria::g_accent_color[0], asteria::g_accent_color[1], asteria::g_accent_color[2], asteria::g_accent_color[3]};
    const ImVec4 text = {asteria::g_text_color[0], asteria::g_text_color[1], asteria::g_text_color[2], asteria::g_text_color[3]};

    c[ImGuiCol_WindowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    c[ImGuiCol_TitleBg] = ImVec4(bg.x * 0.3f, bg.y * 0.3f, bg.z * 0.3f, 0.20f);
    c[ImGuiCol_TitleBgActive] = c[ImGuiCol_TitleBg];
    c[ImGuiCol_ChildBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    c[ImGuiCol_Border] = ImVec4(1.0f, 1.0f, 1.0f, 0.07f);
    c[ImGuiCol_FrameBg] = ImVec4(bg.x + 0.04f, bg.y + 0.04f, bg.z + 0.05f, 0.80f);
    c[ImGuiCol_FrameBgHovered] = ImVec4(bg.x + 0.08f, bg.y + 0.08f, bg.z + 0.09f, 0.90f);
    c[ImGuiCol_FrameBgActive] = ImVec4(bg.x + 0.11f, bg.y + 0.11f, bg.z + 0.13f, 1.00f);
    c[ImGuiCol_Header] = ImVec4(accent.x * 0.5f, accent.y * 0.5f, accent.z * 0.5f, 0.60f);
    c[ImGuiCol_HeaderHovered] = ImVec4(accent.x * 0.6f, accent.y * 0.6f, accent.z * 0.6f, 0.75f);
    c[ImGuiCol_HeaderActive] = accent;
    c[ImGuiCol_Button] = ImVec4(bg.x + 0.05f, bg.y + 0.05f, bg.z + 0.06f, 0.80f);
    c[ImGuiCol_ButtonHovered] = ImVec4(bg.x + 0.09f, bg.y + 0.09f, bg.z + 0.11f, 0.90f);
    c[ImGuiCol_ButtonActive] = ImVec4(accent.x * 0.7f, accent.y * 0.7f, accent.z * 0.7f, 1.00f);
    c[ImGuiCol_CheckMark] = accent;
    c[ImGuiCol_SliderGrab] = accent;
    c[ImGuiCol_SliderGrabActive] = ImVec4(accent.x + 0.08f, accent.y + 0.08f, accent.z + 0.08f, accent.w);
    c[ImGuiCol_Separator] = ImVec4(1.0f, 1.0f, 1.0f, 0.07f);
    c[ImGuiCol_Text] = text;
    c[ImGuiCol_TextDisabled] = ImVec4(text.x * 0.40f, text.y * 0.40f, text.z * 0.40f, 1.00f);
    c[ImGuiCol_ScrollbarBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    c[ImGuiCol_ScrollbarGrab] = ImVec4(1.0f, 1.0f, 1.0f, 0.10f);
    c[ImGuiCol_ScrollbarGrabHovered] = ImVec4(1.0f, 1.0f, 1.0f, 0.18f);
    c[ImGuiCol_ScrollbarGrabActive] = accent;
    c[ImGuiCol_PopupBg] = ImVec4(bg.x + 0.06f, bg.y + 0.06f, bg.z + 0.07f, 0.97f);
}

// ---- Tab bar ----
// Zed/Vercel style: plain text, active tab gets a 2px accent underline.

static void draw_tab_bar(int& active_tab) {
    struct Tab {
        const char* label;
        int id;
    };
    static constexpr Tab tabs[] = {
        {"aimbot", 0},
        {"visuals", 1},
        {"misc", 2},
        {"settings", 3},
    };

    const ImVec4 accent = {asteria::g_accent_color[0], asteria::g_accent_color[1], asteria::g_accent_color[2], 1.0f};
    const ImVec4 text_dim = ImGui::GetStyle().Colors[ImGuiCol_TextDisabled];
    const ImVec4 text_on = ImGui::GetStyle().Colors[ImGuiCol_Text];
    const float pad_x = 14.0f;
    const float pad_y = (TAB_H - ImGui::GetTextLineHeight()) * 0.5f;

    for (const auto& tab : tabs) {
        const bool active = (active_tab == tab.id);
        const ImVec2 label_size = ImGui::CalcTextSize(tab.label);
        const ImVec2 btn_size = ImVec2(label_size.x + pad_x * 2.0f, TAB_H);

        ImGui::PushID(tab.id);
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1, 1, 1, 0.04f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1, 1, 1, 0.07f));
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.0f);

        const ImVec2 btn_pos = ImGui::GetCursorScreenPos();
        if (ImGui::Button("##tab", btn_size)) active_tab = tab.id;

        ImGui::PopStyleVar(2);
        ImGui::PopStyleColor(3);
        ImGui::PopID();

        // Draw label text manually to control color
        ImGui::GetWindowDrawList()->AddText(ImVec2(btn_pos.x + pad_x, btn_pos.y + pad_y), ImGui::ColorConvertFloat4ToU32(active ? text_on : text_dim), tab.label);

        // Active underline
        if (active) {
            const float line_y = btn_pos.y + TAB_H - 2.0f;
            ImGui::GetWindowDrawList()->AddLine(ImVec2(btn_pos.x + pad_x * 0.5f, line_y), ImVec2(btn_pos.x + btn_size.x - pad_x * 0.5f, line_y), ImGui::ColorConvertFloat4ToU32(accent), 2.0f);
        }

        ImGui::SameLine(0.0f, 0.0f);
    }

    ImGui::NewLine();

    // Hairline bottom border
    const ImVec2 bar_min = ImGui::GetWindowPos();
    const float bar_y = bar_min.y + ImGui::GetCursorPosY();
    ImGui::GetWindowDrawList()->AddLine(ImVec2(bar_min.x, bar_y), ImVec2(bar_min.x + WINDOW_W, bar_y), IM_COL32(255, 255, 255, 15), 1.0f);

    ImGui::Spacing();
}

// ---- Tab content ----

static void tab_aimbot() { ImGui::TextDisabled("Nothing here yet."); }

static void tab_visuals() {
    begin_section("CHAMS");

    ImGui::Checkbox("Enabled", &asteria::g_chams_enabled);
    ImGui::SameLine();
    ImGui::Checkbox("Visible Only", &asteria::g_chams_visible_only);

    if (asteria::g_chams_enabled) {
        static const char* styles[] = {"Glass", "Flat", "Glow", "Latex", "Metallic"};
        static constexpr int NUM_STYLES = 5;

        ImGui::Spacing();
        ImGui::TextDisabled("Through Walls");
        ImGui::SetNextItemWidth(140.0f);
        ImGui::Combo("##occ_style", &asteria::g_chams_occ_style, styles, NUM_STYLES);
        ImGui::SameLine();
        ImGui::ColorEdit4("##occ_color", asteria::g_chams_occ_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoLabel);

        ImGui::Spacing();
        ImGui::TextDisabled("Visible");
        ImGui::SetNextItemWidth(140.0f);
        ImGui::Combo("##vis_style", &asteria::g_chams_vis_style, styles, NUM_STYLES);
        ImGui::SameLine();
        ImGui::ColorEdit4("##vis_color", asteria::g_chams_vis_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoLabel);
    }

    end_section();
}

static void tab_misc() { ImGui::TextDisabled("Nothing here yet."); }

static void tab_settings() {
    const float col_w = (ImGui::GetContentRegionAvail().x - ImGui::GetStyle().ItemSpacing.x) * 0.5f;
    const auto no_scroll = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;

    ImGui::BeginChild("##settings_left", ImVec2(col_w, 0.0f), false, no_scroll);
    begin_section("APPEARANCE");
    ImGui::ColorEdit4("Accent", asteria::g_accent_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
    ImGui::ColorEdit4("Background", asteria::g_bg_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
    ImGui::ColorEdit4("Text", asteria::g_text_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
    ImGui::Spacing();
    ImGui::SetNextItemWidth(-1.0f);
    ImGui::SliderFloat("##blur", &asteria::g_blur_radius, 0.0f, 40.0f, "Blur: %.0f");
    end_section();
    begin_section("SESSION");
    if (ImGui::Button("Uninject", ImVec2(-1.0f, 0.0f))) asteria::g_request_unload = true;
    end_section();
    ImGui::EndChild();

    ImGui::SameLine();

    ImGui::BeginChild("##settings_right", ImVec2(col_w, 0.0f), false, no_scroll);
    begin_section("CONFIG");
    ImGui::TextDisabled("No configs found");
    ImGui::Dummy(ImVec2(0.0f, 18.0f));
    ImGui::Spacing();
    const float btn_w = (col_w - ImGui::GetStyle().ItemSpacing.x) * 0.5f - 1.0f;
    if (ImGui::Button("Load", ImVec2(btn_w, 0.0f))) {}
    ImGui::SameLine();
    if (ImGui::Button("Save", ImVec2(btn_w, 0.0f))) {}
    if (ImGui::Button("Create", ImVec2(btn_w, 0.0f))) {}
    ImGui::SameLine();
    if (ImGui::Button("Delete", ImVec2(btn_w, 0.0f))) {}
    end_section();
    ImGui::EndChild();
}

// ---- Public API ----

void setup_style() {
    ImGui::StyleColorsDark();
    ImGuiStyle& s = ImGui::GetStyle();
    ImGuiIO& io = ImGui::GetIO();

    ImFontConfig font_cfg;
    font_cfg.FontDataOwnedByAtlas = false;
    io.Fonts->AddFontFromMemoryTTF(const_cast<void*>(static_cast<const void*>(geist_data.data())), static_cast<int>(geist_data.size()), 14.0f, &font_cfg);

    s.WindowPadding = ImVec2(14.0f, 0.0f);
    s.WindowRounding = 2.0f;
    s.FramePadding = ImVec2(7.0f, 3.0f);
    s.FrameRounding = 2.0f;
    s.ItemSpacing = ImVec2(8.0f, 5.0f);
    s.ItemInnerSpacing = ImVec2(4.0f, 3.0f);
    s.ScrollbarSize = 5.0f;
    s.ScrollbarRounding = 2.0f;
    s.GrabMinSize = 6.0f;
    s.GrabRounding = 2.0f;
    s.ChildRounding = 2.0f;
    s.ChildBorderSize = 0.0f;
    s.PopupRounding = 3.0f;
    s.WindowBorderSize = 1.0f;

    asteria::g_blur_radius = 38.0f;
}

void draw() {
    if (!asteria::g_show_menu) return;

    apply_theme();

    ImGui::SetNextWindowSize(ImVec2(WINDOW_W, WINDOW_H), ImGuiCond_Always);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(6.0f, 7.0f));
    ImGui::Begin("asteria", &asteria::g_show_menu, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    ImGui::PopStyleVar();

    // Blurred background
    const ImVec2 win_pos = ImGui::GetWindowPos();
    const ImVec2 win_size = ImGui::GetWindowSize();
    ImDrawList* bg_dl = ImGui::GetBackgroundDrawList();
    bg_dl->PushClipRect(win_pos, ImVec2(win_pos.x + win_size.x, win_pos.y + win_size.y));
    shaders::blur::apply_blur(bg_dl, asteria::g_blur_radius, 4.0f, 16.0f, ImColor(asteria::g_bg_color[0], asteria::g_bg_color[1], asteria::g_bg_color[2], asteria::g_bg_color[3]));
    bg_dl->PopClipRect();

    static int active_tab = 1;
    draw_tab_bar(active_tab);

    // Content area — offset cursor for padding instead of using PushStyleVar(WindowPadding)
    // which would require careful push/pop context management across BeginChild
    const ImVec2 avail = ImGui::GetContentRegionAvail();
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 14.0f);
    ImGui::BeginChild("##content", ImVec2(avail.x - 14.0f, avail.y), false, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 6.0f);

    switch (active_tab) {
        case 0: tab_aimbot(); break;
        case 1: tab_visuals(); break;
        case 2: tab_misc(); break;
        case 3: tab_settings(); break;
    }

    ImGui::EndChild();
    ImGui::End();
}

} // namespace asteria::core::render::menu
