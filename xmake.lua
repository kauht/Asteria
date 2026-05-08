set_project("menu")
set_version("1.0")
set_languages("cxx23")

add_rules("mode.debug", "mode.release")
set_targetdir("build/bin")
add_rules("plugin.compile_commands.autoupdate")

target("menu")
    set_kind("binary")
    add_files("src/**.cpp")

    add_syslinks("Psapi", "gdi32", "Advapi32")
    add_links("dxgi", "d3d11", "d3dcompiler", "user32.lib")

    -- Vendor Libraries
    add_includedirs("vendor/imgui", "vendor/imgui/backends")
    add_files("vendor/imgui/*.cpp", "vendor/imgui/backends/imgui_impl_win32.cpp", "vendor/imgui/backends/imgui_impl_dx11.cpp")
