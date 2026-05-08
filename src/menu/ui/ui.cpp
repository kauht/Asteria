#include "ui.hpp"
#include "fonts.hpp"

namespace ui
{
    // -------------------------------------------------------------------------
    // style initialization
    // -------------------------------------------------------------------------

    void init_style()
    {
        ImGuiStyle& style = ImGui::GetStyle();
        ImVec4* colors = style.Colors;

        // Window styling - minimal, no title bar
        style.WindowPadding = ImVec2(0, 0);
        style.WindowRounding = 2.0f;
        style.WindowBorderSize = 0.0f;
        style.WindowMinSize = ImVec2(32, 32);
        style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
        style.WindowMenuButtonPosition = ImGuiDir_None;

        // Child window styling
        style.ChildRounding = 2.0f;
        style.ChildBorderSize = 1.0f;

        // Popup styling
        style.PopupRounding = 2.0f;
        style.PopupBorderSize = 0.0f;

        // Frame styling
        style.FramePadding = ImVec2(10, 6);
        style.FrameRounding = 2.0f;
        style.FrameBorderSize = 0.0f;

        // Item styling
        style.ItemSpacing = ImVec2(12, 10);
        style.ItemInnerSpacing = ImVec2(4, 4);
        style.IndentSpacing = 20.0f;

        // Scrollbar styling
        style.ScrollbarSize = 10.0f;
        style.ScrollbarRounding = 2.0f;
        style.GrabMinSize = 10.0f;
        style.GrabRounding = 2.0f;

        // Tab styling
        style.TabRounding = 2.0f;
        style.TabBorderSize = 0.0f;

        // Button styling
        style.ButtonTextAlign = ImVec2(0.5f, 0.5f);

        // Selectable styling
        style.SelectableTextAlign = ImVec2(0.0f, 0.5f);

        // Color scheme - Exact Figma colors
        // Main window background: TRANSPARENT - we draw our own rounded background
        colors[ImGuiCol_WindowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);  // Fully transparent
        colors[ImGuiCol_ChildBg] = ImVec4(40.0f/255.0f, 40.0f/255.0f, 40.0f/255.0f, 0.4f);
        colors[ImGuiCol_PopupBg] = ImVec4(5.0f/255.0f, 5.0f/255.0f, 5.0f/255.0f, 0.9f);
        
        // Border: rgba(40,40,40,0.6)
        colors[ImGuiCol_Border] = ImVec4(40.0f/255.0f, 40.0f/255.0f, 40.0f/255.0f, 0.6f);
        colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);

        // Frame colors
        colors[ImGuiCol_FrameBg] = ImVec4(40.0f/255.0f, 40.0f/255.0f, 40.0f/255.0f, 0.4f);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(40.0f/255.0f, 40.0f/255.0f, 40.0f/255.0f, 0.5f);
        colors[ImGuiCol_FrameBgActive] = ImVec4(40.0f/255.0f, 40.0f/255.0f, 40.0f/255.0f, 0.6f);

        // Title bar (not used but set anyway)
        colors[ImGuiCol_TitleBg] = ImVec4(40.0f/255.0f, 40.0f/255.0f, 40.0f/255.0f, 0.4f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(40.0f/255.0f, 40.0f/255.0f, 40.0f/255.0f, 0.4f);
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4(40.0f/255.0f, 40.0f/255.0f, 40.0f/255.0f, 0.4f);

        // Menu bar
        colors[ImGuiCol_MenuBarBg] = ImVec4(40.0f/255.0f, 40.0f/255.0f, 40.0f/255.0f, 0.4f);

        // Scrollbar
        colors[ImGuiCol_ScrollbarBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.2f);
        colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.3f, 0.3f, 0.3f, 0.5f);
        colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.4f, 0.4f, 0.4f, 0.6f);
        colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.5f, 0.5f, 0.5f, 0.7f);

        // Checkmark
        colors[ImGuiCol_CheckMark] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

        // Slider
        colors[ImGuiCol_SliderGrab] = get_accent(1.0f);
        colors[ImGuiCol_SliderGrabActive] = get_accent(1.0f);

        // Button
        colors[ImGuiCol_Button] = ImVec4(40.0f/255.0f, 40.0f/255.0f, 40.0f/255.0f, 0.4f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(40.0f/255.0f, 40.0f/255.0f, 40.0f/255.0f, 0.5f);
        colors[ImGuiCol_ButtonActive] = ImVec4(40.0f/255.0f, 40.0f/255.0f, 40.0f/255.0f, 0.6f);

        // Header
        colors[ImGuiCol_Header] = ImVec4(40.0f/255.0f, 40.0f/255.0f, 40.0f/255.0f, 0.4f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(40.0f/255.0f, 40.0f/255.0f, 40.0f/255.0f, 0.5f);
        colors[ImGuiCol_HeaderActive] = ImVec4(40.0f/255.0f, 40.0f/255.0f, 40.0f/255.0f, 0.6f);

        // Separator
        colors[ImGuiCol_Separator] = ImVec4(40.0f/255.0f, 40.0f/255.0f, 40.0f/255.0f, 0.6f);
        colors[ImGuiCol_SeparatorHovered] = get_accent(0.7f);
        colors[ImGuiCol_SeparatorActive] = get_accent(1.0f);

        // Resize grip
        colors[ImGuiCol_ResizeGrip] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
        colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
        colors[ImGuiCol_ResizeGripActive] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);

        // Tab
        colors[ImGuiCol_Tab] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
        colors[ImGuiCol_TabHovered] = ImVec4(1.0f, 1.0f, 1.0f, 0.06f);
        colors[ImGuiCol_TabActive] = ImVec4(1.0f, 1.0f, 1.0f, 0.06f);
        colors[ImGuiCol_TabUnfocused] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4(1.0f, 1.0f, 1.0f, 0.06f);

        // Table
        colors[ImGuiCol_TableHeaderBg] = ImVec4(40.0f/255.0f, 40.0f/255.0f, 40.0f/255.0f, 0.4f);
        colors[ImGuiCol_TableBorderStrong] = ImVec4(40.0f/255.0f, 40.0f/255.0f, 40.0f/255.0f, 0.6f);
        colors[ImGuiCol_TableBorderLight] = ImVec4(40.0f/255.0f, 40.0f/255.0f, 40.0f/255.0f, 0.4f);
        colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
        colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.02f);

        // Text - white with varying opacity
        colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        colors[ImGuiCol_TextDisabled] = ImVec4(1.0f, 1.0f, 1.0f, 0.4f);
        colors[ImGuiCol_TextSelectedBg] = ImVec4(1.0f, 1.0f, 1.0f, 0.2f);

        // Drag and drop
        colors[ImGuiCol_DragDropTarget] = get_accent(0.9f);

        // Navigation
        colors[ImGuiCol_NavHighlight] = get_accent(1.0f);
        colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 0.7f);
        colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.5f);

        // Modal
        colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.7f);
    }

    // -------------------------------------------------------------------------
    // helpers
    // -------------------------------------------------------------------------

    static ImFont* font(int idx)
    {
        // Map font indices to new font system
        switch (idx)
        {
            case 0: return fonts::get(FONT_REGULAR);
            case 1: return fonts::get(FONT_MEDIUM);
            case 2: return fonts::get(FONT_BOLD);
            case 3: return fonts::get(FONT_SMALL);
            case 4: return fonts::get(FONT_TINY);
            case 5: return fonts::get(FONT_SEMI_BOLD);
            default: return ImGui::GetFont();
        }
    }


    static float& lerp_val(ImGuiID id, float init = 0.f)
    {
        static std::unordered_map<ImGuiID, float> map;

        auto [it, inserted] = map.emplace(id, init);

        return it->second;
    }

    // -------------------------------------------------------------------------
    // layout
    // -------------------------------------------------------------------------

    void group_box(const char* name, ImVec2 size, std::function<void()> content)
    {
        ImGuiWindow* w = ImGui::GetCurrentWindow();

        ImVec2 pos = w->DC.CursorPos;

        ImDrawList* dl = ImGui::GetWindowDrawList();

        ImGui::BeginChild(
            std::string(name).append(".outer").c_str(),
            size,
            false,
            ImGuiWindowFlags_NoScrollbar
        );

        // Main background - slightly elevated
        dl->AddRectFilled(
            pos,
            pos + size,
            to_vec4(17, 17, 22, anim * ImGui::GetStyle().Alpha),
            6
        );

        // Header background with subtle gradient effect
        dl->AddRectFilled(
            pos,
            pos + ImVec2(size.x, 32),
            to_vec4(20, 20, 26, anim * ImGui::GetStyle().Alpha),
            6,
            ImDrawFlags_RoundCornersTop
        );

        // Subtle border
        dl->AddRect(
            pos,
            pos + size,
            to_vec4(30, 30, 36, anim * ImGui::GetStyle().Alpha * 0.6f),
            6,
            0,
            1.0f
        );

        // Title text
        dl->AddText(
            font(1),
            font(1)->LegacySize,
            pos + ImVec2(14, 8),
            ImGui::GetColorU32(ImGuiCol_Text, anim),
            name
        );

        ImGui::SetCursorPosY(40);

        ImGui::BeginChild(
            name,
            ImVec2(size.x, size.y - 40)
        );

        ImGui::SetCursorPosX(14);

        ImGui::BeginGroup();

        ImGui::PushStyleVar(
            ImGuiStyleVar_ItemSpacing,
            ImVec2(10, 10)
        );

        ImGui::PushStyleVar(
            ImGuiStyleVar_Alpha,
            anim * ImGui::GetStyle().Alpha
        );

        content();

        ImGui::PopStyleVar(2);

        ImGui::EndGroup();

        ImGui::EndChild();

        ImGui::EndChild();
    }

    void group_box_alt(const char* name, ImVec2 size, std::function<void()> content, ImVec2 padding)
    {
        ImGuiWindow* w = ImGui::GetCurrentWindow();

        ImVec2 pos = w->DC.CursorPos;

        ImDrawList* dl = ImGui::GetWindowDrawList();

        ImGui::BeginChild(
            std::string(name).append(".outer").c_str(),
            size,
            false,
            ImGuiWindowFlags_NoScrollbar
        );

        // Background
        dl->AddRectFilled(
            pos,
            pos + size,
            to_vec4(17, 17, 22, anim * ImGui::GetStyle().Alpha),
            6
        );

        // Subtle border
        dl->AddRect(
            pos,
            pos + size,
            to_vec4(30, 30, 36, anim * ImGui::GetStyle().Alpha * 0.6f),
            6,
            0,
            1.0f
        );

        ImGui::SetCursorPosY(padding.y);

        ImGui::BeginChild(
            name,
            ImVec2(size.x, size.y - padding.y)
        );

        ImGui::SetCursorPosX(padding.x);

        ImGui::BeginGroup();

        ImGui::PushStyleVar(
            ImGuiStyleVar_ItemSpacing,
            ImVec2(10, 10)
        );

        ImGui::PushStyleVar(
            ImGuiStyleVar_Alpha,
            anim * ImGui::GetStyle().Alpha
        );

        content();

        ImGui::PopStyleVar(2);

        ImGui::EndGroup();

        ImGui::EndChild();

        ImGui::EndChild();
    }

    void list_box(const char* name, ImVec2 size, std::function<void()> content, ImVec2 padding)
    {
        ImGuiWindow* w = ImGui::GetCurrentWindow();

        ImVec2 pos = w->DC.CursorPos;

        ImDrawList* dl = w->DrawList;

        ImGuiID id = w->GetID(name);

        ImRect bb(pos, pos + size);

        ImGui::ItemAdd(bb, id);

        ImGui::ItemSize(bb, ImGui::GetStyle().FramePadding.y);

        dl->AddRectFilled(
            bb.Min,
            bb.Max,
            to_vec4(25, 25, 31, anim),
            3
        );

        dl->AddRectFilled(
            bb.Min,
            bb.Min + ImVec2(size.x, 26),
            to_vec4(38, 38, 44, anim),
            3,
            ImDrawFlags_RoundCornersTop
        );

        dl->AddRect(
            bb.Min,
            bb.Max,
            to_vec4(38, 38, 44, anim),
            3
        );

        dl->AddText(
            font(1),
            font(1)->LegacySize,
            bb.Min + ImVec2(10, 6),
            ImGui::GetColorU32(ImGuiCol_Text, anim),
            name
        );

        ImGui::SetCursorPos(
            ImVec2(
                ImGui::GetCursorPos().x + padding.x,
                ImGui::GetCursorPos().y
                - ImGui::GetStyle().ItemSpacing.y
                - size.y
                + padding.y
                + 26
            )
        );

        ImGui::PushStyleVar(
            ImGuiStyleVar_Alpha,
            anim
        );

        ImGui::BeginChild(
            std::string(name).append(".child").c_str(),
            ImVec2(
                size.x - padding.x * 2,
                size.y - padding.y * 2 - 26
            )
        );

        content();

        ImGui::EndChild();

        ImGui::PopStyleVar();

        w->DC.CursorPos = ImVec2(
            bb.Min.x,
            bb.Max.y + ImGui::GetStyle().ItemSpacing.y
        );
    }

    void popup(const char* id, const char* name, std::function<void()> content)
    {
        ImGui::SetNextWindowSize(ImVec2(230, 230));

        ImGui::PushStyleVar(
            ImGuiStyleVar_ItemSpacing,
            ImVec2(8, 11)
        );

        ImGui::PushStyleVar(
            ImGuiStyleVar_PopupRounding,
            4
        );

        ImGui::PushStyleColor(
            ImGuiCol_PopupBg,
            ImVec4(ImColor(27, 28, 31))
        );

        ImGui::PushStyleColor(
            ImGuiCol_Border,
            ImVec4(1.f, 1.f, 1.f, 0.05f)
        );

        if (ImGui::BeginPopup(id))
        {
            ImGuiWindow* w = ImGui::GetCurrentWindow();

            ImVec2 pos = w->Pos;

            ImVec2 sz = w->Size;

            ImDrawList* dl = w->DrawList;

            dl->AddText(
                font(2),
                font(2)->LegacySize - 2,
                ImVec2(pos.x + 15, pos.y + 10),
                ImColor(1.f, 1.f, 1.f),
                name
            );

            dl->AddLine(
                ImVec2(pos.x + 10, pos.y + 35),
                ImVec2(pos.x + sz.x - 10, pos.y + 35),
                ImColor(1.f, 1.f, 1.f, 0.1f),
                2
            );

            ImGui::SetCursorPos(ImVec2(10, 45));

            group_box_alt(
                id,
                ImVec2(sz.x - 20, sz.y - 55),
                content
            );

            ImGui::EndPopup();
        }

        ImGui::PopStyleColor(2);

        ImGui::PopStyleVar(2);
    }

    void colored_rect(const char* id, ImColor color, ImVec2 size)
    {
        ImGuiWindow* w = ImGui::GetCurrentWindow();

        ImGuiID gid = w->GetID(id);

        ImVec2 pos = w->DC.CursorPos;

        ImRect bb(pos, pos + size);

        ImGui::ItemAdd(bb, gid);

        ImGui::ItemSize(bb);

        ImGui::RenderFrame(
            bb.Min,
            bb.Max,
            color,
            false,
            4
        );
    }

    void separator(const char* label)
    {
        ImGui::Spacing();

        if (label)
        {
            ImGui::PushStyleColor(
                ImGuiCol_Text,
                ImVec4(get_accent())
            );

            ImGui::SeparatorText(label);

            ImGui::PopStyleColor();
        }
        else
        {
            ImGui::Separator();
        }

        ImGui::Spacing();
    }

    // -------------------------------------------------------------------------
    // controls
    // -------------------------------------------------------------------------

    bool checkbox(const char* label, bool* v, const char* hint)
    {
        ImGuiWindow* w = ImGui::GetCurrentWindow();

        if (w->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;

        const ImGuiStyle& style = g.Style;

        ImGuiID id = w->GetID(label);

        ImFont* fnt = font(0);

        const ImVec2 label_size =
            fnt->CalcTextSizeA(
                fnt->LegacySize,
                FLT_MAX,
                0,
                label
            );

        const ImVec2 hint_size =
            hint[0]
            ? font(0)->CalcTextSizeA(
                font(0)->LegacySize - 1.f,
                FLT_MAX,
                0,
                hint
            )
            : ImVec2();

        const float sq = 16.f;

        const float rnd = 4.f;

        const ImVec2 pos = w->DC.CursorPos;

        ImRect frame_bb(
            pos,
            pos + ImVec2(sq, sq)
        );

        ImRect total_bb(
            pos,
            pos + ImVec2(
                sq
                + ImMax(label_size.x, hint_size.x)
                + style.ItemInnerSpacing.x
                + 4,
                hint_size.x > 0
                ? sq + 2 + hint_size.y
                : sq
            )
        );

        ImGui::ItemAdd(total_bb, id, &frame_bb);

        ImGui::ItemSize(total_bb, style.FramePadding.y);

        bool hov, held;

        bool pressed =
            ImGui::ButtonBehavior(
                total_bb,
                id,
                &hov,
                &held
            );

        if (pressed)
        {
            *v = !*v;

            ImGui::MarkItemEdited(id);
        }

        float& val = lerp_val(id);

        val = ImLerp(
            val,
            *v ? 1.f : 0.f,
            0.08f
        );

        // Background
        ImGui::RenderFrame(
            frame_bb.Min,
            frame_bb.Max,
            to_vec4(14, 14, 18, style.Alpha),
            false,
            rnd
        );

        // Border when not checked
        if (val < 0.99f)
        {
            w->DrawList->AddRect(
                frame_bb.Min,
                frame_bb.Max,
                to_vec4(30, 30, 36, (1.0f - val) * style.Alpha),
                rnd,
                0,
                1.0f
            );
        }

        // Accent fill when checked
        ImGui::RenderFrame(
            frame_bb.Min,
            frame_bb.Max,
            ImColor(
                get_accent().Value.x,
                get_accent().Value.y,
                get_accent().Value.z,
                val * style.Alpha
            ),
            false,
            rnd
        );

        // Checkmark
        w->DrawList->PushClipRect(
            frame_bb.GetCenter() - ImVec2(5, 5),
            frame_bb.GetCenter() + ImVec2(7 * val, 9)
        );

        ImGui::RenderCheckMark(
            w->DrawList,
            frame_bb.GetCenter() - ImVec2(5, 5),
            ImColor(1.f, 1.f, 1.f, val * style.Alpha),
            10
        );

        w->DrawList->PopClipRect();

        ImVec2 lp = ImVec2(
            frame_bb.Max.x
            + style.ItemInnerSpacing.x
            + 4,
            frame_bb.GetCenter().y
            - label_size.y / 2
        );

        w->DrawList->AddText(
            fnt,
            fnt->LegacySize,
            lp,
            to_vec4(240, 242, 245, style.Alpha),
            label,
            ImGui::FindRenderedTextEnd(label)
        );

        if (hint[0])
        {
            w->DrawList->AddText(
                font(0),
                font(0)->LegacySize - 1.f,
                ImVec2(lp.x, lp.y + label_size.y + 2),
                ImGui::GetColorU32(ImGuiCol_TextDisabled, 0.8f),
                hint,
                ImGui::FindRenderedTextEnd(hint)
            );
        }

        return pressed;
    }

    bool button(const char* label, const char* icon, ImVec2 size_arg)
    {
        ImGuiWindow* w = ImGui::GetCurrentWindow();

        if (w->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;

        const ImGuiStyle& style = g.Style;

        ImGuiID id = w->GetID(label);

        const ImVec2 label_size =
            font(1)->CalcTextSizeA(
                font(1)->LegacySize,
                FLT_MAX,
                0,
                label
            );

        const ImVec2 icon_size =
            icon[0]
            ? font(4)->CalcTextSizeA(
                font(4)->LegacySize,
                FLT_MAX,
                0,
                icon
            )
            : ImVec2();

        ImVec2 pos = w->DC.CursorPos;

        ImVec2 size =
            ImGui::CalcItemSize(
                size_arg,
                label_size.x + style.FramePadding.x * 2,
                label_size.y + style.FramePadding.y * 2
            );

        ImRect bb(pos, pos + size);

        ImGui::ItemSize(size, style.FramePadding.y);

        if (!ImGui::ItemAdd(bb, id))
            return false;

        bool hov, held;

        bool pressed =
            ImGui::ButtonBehavior(
                bb,
                id,
                &hov,
                &held
            );

        ImGui::RenderNavHighlight(bb, id);

        // Smooth hover animation
        float& hover_val = lerp_val(id);
        hover_val = ImLerp(
            hover_val,
            (held && hov) ? 1.0f : hov ? 0.5f : 0.0f,
            0.12f
        );

        // Background with hover effect
        ImU32 bg_col;
        if (held && hov)
            bg_col = to_vec4(30, 30, 36, style.Alpha);
        else if (hov)
            bg_col = to_vec4(25, 25, 31, style.Alpha);
        else
            bg_col = to_vec4(20, 20, 26, style.Alpha);

        ImGui::RenderFrame(
            bb.Min,
            bb.Max,
            bg_col,
            false,
            6
        );

        // Subtle border
        w->DrawList->AddRect(
            bb.Min,
            bb.Max,
            to_vec4(30, 30, 36, style.Alpha * 0.6f),
            6,
            0,
            1.0f
        );

        if (icon_size.x > 0)
        {
            w->DrawList->AddText(
                font(4),
                font(4)->LegacySize,
                bb.GetCenter()
                - icon_size / 2
                - ImVec2(label_size.x / 2 + 4, 0),
                ImGui::GetColorU32(ImGuiCol_Text),
                icon
            );
        }

        w->DrawList->AddText(
            font(1),
            font(1)->LegacySize,
            bb.GetCenter()
            - label_size / 2
            + (icon_size.x > 0
            ? ImVec2(icon_size.x / 2 + 4, 0)
            : ImVec2()),
            ImColor(1.f, 1.f, 1.f, style.Alpha),
            label
        );

        return pressed;
    }

    bool button_alt(const char* icon, ImVec2 size_arg)
    {
        ImGuiWindow* w = ImGui::GetCurrentWindow();

        if (w->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;

        const ImGuiStyle& style = g.Style;

        ImGuiID id = w->GetID(icon);

        const ImVec2 icon_size =
            font(4)->CalcTextSizeA(
                font(4)->LegacySize,
                FLT_MAX,
                0,
                icon
            );

        ImVec2 pos = w->DC.CursorPos;

        ImVec2 size =
            ImGui::CalcItemSize(
                size_arg,
                icon_size.x + style.FramePadding.x * 2,
                icon_size.y + style.FramePadding.y * 2
            );

        ImRect bb(pos, pos + size);

        ImGui::ItemSize(size, style.FramePadding.y);

        if (!ImGui::ItemAdd(bb, id))
            return false;

        bool hov, held;

        bool pressed =
            ImGui::ButtonBehavior(
                bb,
                id,
                &hov,
                &held
            );

        ImGui::RenderNavHighlight(bb, id);

        ImGui::RenderFrame(
            bb.Min,
            bb.Max,
            ImGui::GetColorU32(
                held && hov
                ? ImGuiCol_ButtonActive
                : hov
                ? ImGuiCol_ButtonHovered
                : ImGuiCol_Button
            ),
            false,
            5
        );

        w->DrawList->AddRect(
            bb.Min,
            bb.Max,
            to_vec4(38, 38, 44, style.Alpha),
            5
        );

        w->DrawList->AddText(
            font(4),
            font(4)->LegacySize,
            bb.GetCenter() - icon_size / 2,
            ImGui::GetColorU32(ImGuiCol_Text),
            icon
        );

        return pressed;
    }

    bool sub_tab(const char* label, bool selected)
    {
        ImGuiWindow* w = ImGui::GetCurrentWindow();

        ImGuiID id = w->GetID(label);

        ImVec2 label_size =
            ImGui::CalcTextSize(label, nullptr, true);

        ImVec2 pos = w->DC.CursorPos;

        ImVec2 size = ImVec2(label_size.x + 24, 32);

        ImRect bb(pos, pos + size);

        ImGui::ItemAdd(bb, id);

        ImGui::ItemSize(
            ImRect(
                bb.Min.x,
                bb.Min.y,
                bb.Max.x - 6,
                bb.Max.y
            )
        );

        bool hov, held;

        bool pressed =
            ImGui::ButtonBehavior(
                bb,
                id,
                &hov,
                &held
            );

        float& val = lerp_val(id);

        val = ImLerp(
            val,
            selected ? 1.f : 0.f,
            0.06f
        );

        // Background
        w->DrawList->AddRectFilled(
            bb.Min,
            bb.Max,
            to_vec4(
                20,
                20,
                26,
                val * ImGui::GetStyle().Alpha
            ),
            5
        );

        // Accent underline when selected
        if (val > 0.01f)
        {
            w->DrawList->AddRectFilled(
                ImVec2(bb.Min.x + 6, bb.Max.y - 2),
                ImVec2(bb.Max.x - 6, bb.Max.y),
                ImColor(
                    get_accent().Value.x,
                    get_accent().Value.y,
                    get_accent().Value.z,
                    val * ImGui::GetStyle().Alpha
                ),
                1.0f
            );
        }

        ImGui::PushStyleColor(
            ImGuiCol_Text,
            ImVec4(
                1.f,
                1.f,
                1.f,
                selected ? 1.f : 0.6f
            )
        );

        w->DrawList->AddText(
            ImVec2(
                bb.GetCenter().x - label_size.x / 2,
                bb.GetCenter().y - label_size.y / 2
            ),
            ImGui::GetColorU32(ImGuiCol_Text),
            label
        );

        ImGui::PopStyleColor();

        return pressed;
    }

    bool combo(const char* label, int* current, const char* const items[], int count)
    {
        const char* preview =
            (*current >= 0 && *current < count)
            ? items[*current]
            : nullptr;

        if (!ImGui::BeginCombo(label, preview))
            return false;

        bool changed = false;

        for (int i = 0; i < count; i++)
        {
            ImGui::PushID(i);

            if (selectable(items[i], i == *current, 0, ImVec2(0, 30)))
            {
                *current = i;
                changed = true;
            }

            if (i == *current)
                ImGui::SetItemDefaultFocus();

            ImGui::PopID();
        }

        ImGui::EndCombo();

        return changed;
    }
    bool combo(const char* label, int* current, const char* items_null_separated)
    {
        int count = 0;

        const char* p = items_null_separated;

        while (*p)
        {
            p += strlen(p) + 1;
            count++;
        }

        const char* preview = nullptr;

        p = items_null_separated;

        for (int i = 0; i <= *current && *p; i++, p += strlen(p) + 1)
        {
            if (i == *current)
                preview = p;
        }

        if (!ImGui::BeginCombo(label, preview))
            return false;

        bool changed = false;

        p = items_null_separated;

        for (int i = 0; *p; i++, p += strlen(p) + 1)
        {
            ImGui::PushID(i);

            if (selectable(p, i == *current, 0, ImVec2(0, 30)))
            {
                *current = i;
                changed = true;
            }

            if (i == *current)
                ImGui::SetItemDefaultFocus();

            ImGui::PopID();
        }

        ImGui::EndCombo();

        return changed;
    }
    bool tab(const char* icon, const char* label, bool selected, float rounding, ImDrawFlags draw_flags)
    {
        ImGuiWindow* w = ImGui::GetCurrentWindow();

        ImGuiID id = w->GetID(icon);

        ImVec2 label_size =
            ImGui::CalcTextSize(label, nullptr, true);

        ImVec2 icon_size =
            font(4)->CalcTextSizeA(
                font(4)->LegacySize,
                FLT_MAX,
                0,
                icon
            );

        ImVec2 pos = w->DC.CursorPos;

        ImVec2 size = ImVec2(label_size.x + 50, 44);

        ImRect bb(pos, pos + size);

        ImGui::ItemAdd(bb, id);

        ImGui::ItemSize(
            ImRect(
                bb.Min.x,
                bb.Min.y,
                bb.Max.x - 10,
                bb.Max.y
            )
        );

        bool hov, held;

        bool pressed =
            ImGui::ButtonBehavior(
                bb,
                id,
                &hov,
                &held
            );

        float& val = lerp_val(id);

        val = ImLerp(
            val,
            selected ? 1.f : 0.f,
            0.06f
        );

        // Background with smooth transition
        w->DrawList->AddRectFilled(
            bb.Min,
            bb.Max,
            to_vec4(
                17,
                17,
                22,
                val * ImGui::GetStyle().Alpha
            ),
            rounding,
            draw_flags
        );

        // Accent indicator on left side when selected
        if (val > 0.01f)
        {
            w->DrawList->AddRectFilled(
                ImVec2(bb.Min.x, bb.Min.y + 8),
                ImVec2(bb.Min.x + 3, bb.Max.y - 8),
                ImColor(
                    get_accent().Value.x,
                    get_accent().Value.y,
                    get_accent().Value.z,
                    val * ImGui::GetStyle().Alpha
                ),
                2.0f
            );
        }

        // Icon
        w->DrawList->AddText(
            font(4),
            font(4)->LegacySize,
            ImVec2(
                bb.Min.x + 16,
                bb.GetCenter().y - icon_size.y / 2
            ),
            ImGui::GetColorU32(
                ImGuiCol_Text,
                selected ? 1.0f : 0.6f
            ),
            icon
        );

        // Label
        w->DrawList->AddText(
            ImVec2(
                bb.Min.x + 38,
                bb.GetCenter().y - label_size.y / 2
            ),
            ImGui::GetColorU32(
                ImGuiCol_Text,
                selected ? 1.0f : 0.6f
            ),
            label
        );

        return pressed;
    }
    bool selectable(const char* label, bool selected, ImGuiSelectableFlags flags, ImVec2 size_arg)
    {
        ImGuiWindow* w = ImGui::GetCurrentWindow();

        if (w->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;

        const ImGuiStyle& style = g.Style;

        ImGuiID id = w->GetID(label);

        ImVec2 label_size =
            ImGui::CalcTextSize(label, nullptr, true);

        ImVec2 size(
            size_arg.x != 0 ? size_arg.x : label_size.x,
            size_arg.y != 0 ? size_arg.y : label_size.y
        );

        ImVec2 pos = w->DC.CursorPos;

        pos.y += w->DC.CurrLineTextBaseOffset;

        ImGui::ItemSize(size, 0.f);

        const float max_x = w->WorkRect.Max.x;

        if (size_arg.x == 0 ||
            (flags & ImGuiSelectableFlags_SpanAvailWidth))
        {
            size.x = ImMax(label_size.x, max_x - pos.x);
        }

        ImRect bb(
            pos.x,
            pos.y,
            pos.x + size.x,
            pos.y + size.y
        );

        if (!(flags & ImGuiSelectableFlags_NoPadWithHalfSpacing))
        {
            float sx = style.ItemSpacing.x;
            float sy = style.ItemSpacing.y;

            bb.Min.x -= ImFloor(sx * 0.5f);
            bb.Min.y -= ImFloor(sy * 0.5f);

            bb.Max.x += sx - ImFloor(sx * 0.5f);
            bb.Max.y += sy - ImFloor(sy * 0.5f);
        }

        if (!ImGui::ItemAdd(bb, id))
            return false;

        bool hov, held;

        bool pressed =
            ImGui::ButtonBehavior(
                bb,
                id,
                &hov,
                &held
            );

        if (pressed)
            ImGui::MarkItemEdited(id);

        float& val = lerp_val(id);

        val = ImLerp(
            val,
            selected ? 1.f : hov ? 0.5f : 0.f,
            0.05f
        );

        ImGui::RenderFrame(
            bb.Min,
            bb.Max,
            to_vec4(38, 38, 44, val),
            false,
            5
        );

        ImGui::PushStyleColor(
            ImGuiCol_Text,
            ImVec4(
                1.f,
                1.f,
                1.f,
                selected ? 1.f : 0.5f
            )
        );

        ImGui::RenderText(
            ImVec2(
                bb.Min.x + 10,
                bb.GetCenter().y - label_size.y / 2
            ),
            label
        );

        ImGui::PopStyleColor();

        if (pressed &&
            (w->Flags & ImGuiWindowFlags_Popup) &&
            !(flags & ImGuiSelectableFlags_DontClosePopups))
        {
            ImGui::CloseCurrentPopup();
        }

        return pressed;
    }
    bool selectable(const char* label, bool* p_selected, ImGuiSelectableFlags flags, ImVec2 size_arg)
    {
        if (selectable(label, *p_selected, flags, size_arg))
        {
            *p_selected = !*p_selected;

            return true;
        }

        return false;
    }

    void image(
        ImTextureID tex,
        ImVec2 size,
        float rounding,
        ImDrawFlags flags,
        ImVec2 uv0,
        ImVec2 uv1,
        ImVec4 tint,
        ImVec4 border
    )
    {
        ImGuiWindow* w = ImGui::GetCurrentWindow();

        if (w->SkipItems)
            return;

        ImRect bb(w->DC.CursorPos, w->DC.CursorPos + size);

        ImGui::ItemSize(bb);

        if (!ImGui::ItemAdd(bb, 0))
            return;

        if (border.w > 0.0f)
        {
            w->DrawList->AddRect(
                bb.Min,
                bb.Max,
                ImGui::GetColorU32(border),
                rounding,
                flags,
                1.0f
            );
        }

        w->DrawList->AddImageRounded(
            tex,
            bb.Min,
            bb.Max,
            uv0,
            uv1,
            ImGui::GetColorU32(tint),
            rounding,
            flags
        );
    }
}
