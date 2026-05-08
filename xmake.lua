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
    add_includedirs("src", "vendor/imgui", "vendor/imgui/backends")
    add_files("vendor/imgui/*.cpp", "vendor/imgui/backends/imgui_impl_win32.cpp", "vendor/imgui/backends/imgui_impl_dx11.cpp")
    add_includedirs("vendor/json/include")

    -- CS2 SDK
    add_includedirs("vendor/cs2-sdk/output")
    add_includedirs("vendor/safetyhook/include", "vendor/safetyhook/src")
    add_files("vendor/safetyhook/src/**.cpp")
    add_includedirs("vendor/zydis/src", "vendor/zydis", "vendor/zydis/include", "vendor/zydis/dependencies/zycore/include")
    add_files("vendor/zydis/src/**.c")
    add_defines("ZYDIS_STATIC_BUILD", "ZYCORE_STATIC_BUILD")
