// Dear ImGui: standalone example application for DirectX 9
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

#define  IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include <d3d9.h>
#include <tchar.h>

#include "custom.hpp"

#include "blur.hpp"
#include "bytes.hpp"

using namespace ImGui;

#define ALPHA    ( ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoBorder )
#define NO_ALPHA ( ImGuiColorEditFlags_NoTooltip    | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoBorder )

IDirect3DTexture9* background = { nullptr };
IDirect3DTexture9* weather    = { nullptr };

// Data
static LPDIRECT3D9              g_pD3D = NULL;
static LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;
static D3DPRESENT_PARAMETERS    g_d3dpp = {};

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void ResetDevice();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Main code
int main(int, char**)
{
    // Create application window
    //ImGui_ImplWin32_EnableDpiAwareness();
    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, L"ImGui Example", NULL };
    ::RegisterClassExW(&wc);
    HWND hwnd = ::CreateWindowW(wc.lpszClassName, L"Dear ImGui DirectX9 Example", WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, NULL, NULL, wc.hInstance, NULL);

    // Initialize Direct3D
    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    // Show the window
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    ImFontConfig font_config;
    font_config.PixelSnapH = false;
    font_config.FontDataOwnedByAtlas = false;
    font_config.OversampleH = 5;
    font_config.OversampleV = 5;
    font_config.RasterizerMultiply = 1.2f;

    static const ImWchar ranges[ ] = {

        0x0020, 0x00FF, // Basic Latin + Latin Supplement
        0x0400, 0x052F, // Cyrillic + Cyrillic Supplement
        0x2DE0, 0x2DFF, // Cyrillic Extended-A
        0xA640, 0xA69F, // Cyrillic Extended-B
        0xE000, 0xE226, // icons
        0,
    };

    font_config.GlyphRanges = ranges;

    io.Fonts->AddFontFromMemoryTTF( font_medium_binary, sizeof font_medium_binary, 15, &font_config, ranges );
    io.Fonts->AddFontFromMemoryTTF( font_semi_binary,   sizeof font_semi_binary,   15, &font_config, ranges );
    io.Fonts->AddFontFromMemoryTTF( font_bold_binary,   sizeof font_bold_binary,   19, &font_config, ranges );

    io.Fonts->AddFontFromMemoryTTF( icons_binary,       sizeof icons_binary,       9,  &font_config, ranges );
    io.Fonts->AddFontFromMemoryTTF( icons_binary,       sizeof icons_binary,       13, &font_config, ranges );

    io.Fonts->AddFontFromMemoryTTF( font_semi_binary,   sizeof font_semi_binary,   17, &font_config, ranges );

    // Our state
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    bool done = false;
    while (!done)
    {
        // Poll and handle messages (inputs, window resize, etc.)
        // See the WndProc() function below for our to dispatch events to the Win32 backend.
        MSG msg;
        while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

        // Start the Dear ImGui frame
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        if ( !background )
            D3DXCreateTextureFromFileInMemoryEx( g_pd3dDevice, &dust_binary, sizeof dust_binary, 1920, 1080,
                D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &background );

        if ( !weather )
            D3DXCreateTextureFromFileInMemoryEx( g_pd3dDevice, &lightning_bolts_binary, sizeof lightning_bolts_binary, 256, 256,
                D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &weather );

        static bool  opened = false;
        static float alpha = 0.f, speed = 0.1f;

        alpha = ImLerp( alpha, opened ? 1.f : 0.f, 1.f * speed );

        if ( GetAsyncKeyState( VK_INSERT ) & 1 )
            opened = !opened;

        static bool checkbox[50];
        static bool multi[5];
        static int  slider = 0, combo = 0, combo_n = 0, key = 0, mode = 0;
        vector < const char* > combo_items = { "Item 1", "Item 2", "Item 3" };
        vector < const char* > multi_items = { "Item 1", "Item 2", "Item 3", "Item 4", "Item 5" };
        vector < const char* > combo_n_items = { "Enemy", "Friendly" };
        static vector < const char* > modes = { "Toggle", "Hold" };
        static char buf[64];
        static float color[4] = { 1.f, 1.f, 1.f, 1.f };

        static bool enableffi = false;
        static int  cur_lua = 0;
        static vector < const char* > lua_list = { "Weather", "Lua 1", "Lua 2", "Lua 3", "Lua 4", "Lua 5", "Lua 6", "Lua 7", "Lua 8", "Lua 9", "Lua 10", "Lua 11", "Lua 12" };

        static st_lua arr[ 50 ];

        GetBackgroundDrawList( )->AddImage( background, ImVec2( 0, 0 ), GetIO( ).DisplaySize );

        BlurData::device = g_pd3dDevice;

        PushStyleVar( ImGuiStyleVar_WindowPadding, ImVec2( 0, 0 ) );
        PushStyleVar( ImGuiStyleVar_Alpha, alpha );

        if ( opened || alpha >= 0.05f ) {

            ImGui::Begin( "Hello, world!", NULL, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground ); {

                auto window = GetCurrentWindow( );
                auto draw   = window->DrawList;
                auto pos    = window->Pos;
                auto size   = window->Size;
                auto style  = GetStyle( );
                // 740 x 593
                // SetWindowSize( ImVec2( 620, 480 ) );
                SetWindowSize( ImVec2( 740 * alpha, 593 * alpha ) );

                custom.m_anim = ImLerp( custom.m_anim, 1.f, 0.038f );
                draw->AddText( GetIO( ).Fonts->Fonts[2], GetIO( ).Fonts->Fonts[2]->FontSize, pos + ImVec2( 12, 12 ), ImColor( 1.f, 1.f, 1.f, 0.8f * GetStyle( ).Alpha ), "CHIMERA" );

                draw->AddRectFilled( pos + ImVec2( 0, 40 ), pos + ImVec2( size.x, 70 ), to_vec4( 19, 20, 23, GetStyle( ).Alpha ) );
                draw->AddText( GetIO( ).Fonts->Fonts[3], GetIO( ).Fonts->Fonts[3]->FontSize, pos + ImVec2( 10, 49 ), to_vec4( 118, 132, 151, GetStyle( ).Alpha ), "A" );
                draw->AddText( GetIO( ).Fonts->Fonts[0], GetIO( ).Fonts->Fonts[0]->FontSize - 1, pos + ImVec2( 27, 48 ), GetColorU32( ImGuiCol_Text, 0.5f ), "Welcome admin!" );

                SetCursorPosX( size.x - custom.get_label_sizes( custom.tabs ) - ( 40 * custom.tabs.size( ) ) );
                BeginGroup( );

                for ( int i = 0; i < custom.tabs.size( ); ++i ) {

                    if ( custom.tab( custom.tabs_icons.at( i ), custom.tabs.at( i ), custom.m_tab == i, i == custom.tabs.size( ) - 1 ? style.WindowRounding : 0, i == custom.tabs.size( ) - 1 ? ImDrawFlags_RoundCornersTopRight : 0 ) && custom.m_tab != i )
                        custom.m_tab = i, custom.m_anim = 0.f;

                    if ( i != custom.tabs.size( ) - 1 )
                        SameLine( );

                }

                EndGroup( );

                switch ( custom.m_tab ) {

                    case 0:

                        SetCursorPos( ImVec2( size.x - custom.get_label_sizes( custom.aimbot_sub_tabs ) - ( GetStyle( ).ItemSpacing.x * custom.aimbot_sub_tabs.size( ) ), 47 ) );
                        BeginGroup( );

                        for ( int i = 0; i < custom.aimbot_sub_tabs.size( ); ++i ) {

                            if ( custom.sub_tab( custom.aimbot_sub_tabs.at( i ), custom.m_aimbot_sub_tab == i ) && custom.m_aimbot_sub_tab != i )
                                custom.m_aimbot_sub_tab = i, custom.m_anim = 0.f;

                            if ( i != custom.aimbot_sub_tabs.size( ) - 1 )
                                SameLine( );

                        }

                        EndGroup( );

                        SetCursorPos( ImVec2( 10, 80 ) );
                        BeginChild( "##aimbot.groupboxes.area", ImVec2( size.x - 20, size.y - 90 ) ); {

                            custom.group_box_alternative( "##master_switch.aimbot", ImVec2( GetWindowWidth( ), 53 ) ); {

                                custom.checkbox( "Master switch##aimbot", &checkbox[3], "Toggle on all aimbot features", GetIO( ).Fonts->Fonts[1] );
                                SameLine( GetWindowWidth( ) - 120 );
                                custom.combo("##combo", &combo_n, combo_n_items.data( ), combo_n_items.size( ) );

                            } custom.end_group_box_alternative( );

                            custom.group_box( "General", ImVec2( GetWindowWidth( ) / 2 - GetStyle( ).ItemSpacing.x / 2, GetWindowHeight( ) - 53 - GetStyle( ).ItemSpacing.y ) ); {

                                custom.checkbox( "Enable", &checkbox[0], "Hint" ); SameLine( GetWindowWidth( ) - 64 ); if ( custom.settings_widget( "##aimbot.enable.settings" ) ) OpenPopup( "##aimbot.enable.popup" ); SameLine( GetWindowWidth( ) - 47 ); ColorEdit4( "##color", color, ALPHA );

                                custom.prepared_popup( "##aimbot.enable.popup", "Enable", [ ]( ) {

                                    Checkbox( "Checkbox 2", &checkbox[2] );
                                    SliderInt( "Slider", &slider, 0, 100 );
                                    Hotkey( "Key", &key );
                                    Combo( "Mode", &mode, modes.data( ), modes.size( ) );

                                } );

                                Checkbox( "Checkbox 1", &checkbox[1] );
                                SliderInt( "Slider", &slider, 0, 100 );
                                Combo( "Combo", &combo, combo_items.data( ), combo_items.size( ) );
                                InputText( "Input", buf, sizeof buf );
                                Button( "Button", ImVec2( GetWindowWidth( ) - 25, 25 ) );
                                MultiCombo( "Multi", multi, multi_items.data( ), multi_items.size( ) );
                                SliderFloat( "Speed", &speed, 0.05f, 1.f );

                            } custom.end_group_box( );

                            SameLine( );

                            custom.group_box( "Miscellaneous", ImVec2( GetWindowWidth( ) / 2 - GetStyle( ).ItemSpacing.x / 2, GetWindowHeight( ) - 53 - GetStyle( ).ItemSpacing.y ) ); {



                            } custom.end_group_box( );

                        } EndChild( );

                        break;

                    case 3:

                        SetCursorPos( ImVec2( 10, 80 ) );
                        BeginChild( "##scripts.groupboxes.area", ImVec2( size.x - 20, size.y - 90 ) ); {

                            custom.group_box_alternative( "##enable_ffi.scripts", ImVec2( GetWindowWidth( ), 53 ) ); {

                                custom.checkbox( "Enable Foreign Function Interface##scripts", &enableffi, "Allow scripts to use FFI.", GetIO( ).Fonts->Fonts[1] );
                                SameLine( GetWindowWidth( ) - 155 );
                                custom.button( "Get more scripts", "B", ImVec2( 130, 30 ) );

                            } custom.end_group_box_alternative( );

                            custom.list_box( "Available scripts", ImVec2( GetWindowWidth( ) / 2 - GetStyle( ).ItemSpacing.x / 2 - 70, GetWindowHeight( ) - 53 - GetStyle( ).ItemSpacing.y ), [ ]( ) {

                                for ( int i = 0; i < lua_list.size( ); ++i ) {

                                    arr[ i ] = custom.lua( lua_list.at( i ), cur_lua == i );

                                    if ( arr[ i ].pressed_whole )
                                        cur_lua = i;
                                }

                            }, ImVec2( 0, 0 ) );

                            SameLine( ), SetCursorPosY( 53 + GetStyle( ).ItemSpacing.y );

                            custom.group_box_alternative( "##lua.information", ImVec2( GetWindowWidth( ) / 2 + 66, GetWindowHeight( ) - 53 - GetStyle( ).ItemSpacing.y ), ImVec2( 1, 1 ) ); {

                                switch ( cur_lua ) {

                                case 0:

                                    custom.image( weather, ImVec2( GetWindowWidth( ) - 2, 150 ), 4, ImDrawFlags_RoundCornersTop );
                                    SetCursorPos( ImVec2( GetWindowWidth( ) - 20, 5 ) );
                                    custom.button_alternative( "G", ImVec2( 15, 16 ) );

                                    SetCursorPos( ImVec2( GetWindowWidth( ) - 40, 5 ) );
                                    custom.button_alternative( "D", ImVec2( 15, 16 ) );

                                    SetCursorPos( ImVec2( 10, 160 ) );
                                    BeginChild( "##weather.child", ImVec2( GetWindowWidth( ) - 20, GetWindowHeight( ) - 160 ) );

                                    PushFont( io.Fonts->Fonts[4] );
                                    TextColored( arr[ cur_lua ].active ? custom.get_accent_color( GetStyle( ).Alpha ) : to_vec4( 116, 129, 148, style.Alpha ), arr[ cur_lua ].active ? "E" : "F" );
                                    PopFont( );

                                    SameLine( ), SetCursorPosY( GetCursorPosY( ) - 2 );

                                    PushFont( io.Fonts->Fonts[5] );
                                    Text( lua_list.at( cur_lua ) );
                                    PopFont( );

                                    SetCursorPosY( GetCursorPosY( ) - 5 );
                                    Text( "Last updated: 16.02.2022" );

                                    Text( "Makes rain" );

                                    EndChild( );

                                    break;

                                }

                            } custom.end_group_box_alternative( );

                        } EndChild( );

                        break;

                }

            } ImGui::End( );

        }

        PopStyleVar( 2 );

        // Rendering
        ImGui::EndFrame();
        g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
        D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_color.x*clear_color.w*255.0f), (int)(clear_color.y*clear_color.w*255.0f), (int)(clear_color.z*clear_color.w*255.0f), (int)(clear_color.w*255.0f));
        g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0);
        if (g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            g_pd3dDevice->EndScene();
        }
        HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);

        // Handle loss of D3D9 device
        if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
            ResetDevice();
    }

    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);

    return 0;
}

// Helper functions

bool CreateDeviceD3D(HWND hWnd)
{
    if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
        return false;

    // Create the D3DDevice
    ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
    g_d3dpp.Windowed = TRUE;
    g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN; // Need to use an explicit format with alpha if needing per-pixel alpha composition.
    g_d3dpp.EnableAutoDepthStencil = TRUE;
    g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;           // Present with vsync
    //g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;   // Present without vsync, maximum unthrottled framerate
    if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
        return false;

    return true;
}

void CleanupDeviceD3D()
{
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
    if (g_pD3D) { g_pD3D->Release(); g_pD3D = NULL; }
}

void ResetDevice()
{
    ImGui_ImplDX9_InvalidateDeviceObjects();
    HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
    if (hr == D3DERR_INVALIDCALL)
        IM_ASSERT(0);
    ImGui_ImplDX9_CreateDeviceObjects();
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            g_d3dpp.BackBufferWidth = LOWORD(lParam);
            g_d3dpp.BackBufferHeight = HIWORD(lParam);
            ResetDevice();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}
