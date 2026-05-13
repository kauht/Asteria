set_project("asteria")
set_version("1.0")
set_languages("cxx23")

add_rules("mode.debug", "mode.release")
set_targetdir("build/bin")
add_rules("plugin.compile_commands.autoupdate")

target("asteria")
    set_kind("shared")
    add_files("src/**.cpp")

    add_syslinks("Psapi", "gdi32", "Advapi32", "user32", "dxgi", "d3d11", "d3dcompiler", "Ole32")
    add_includedirs(
        "vendor/cs2-sdk/include",
        "vendor/json/include",
        "vendor/safetyhook/include",
        "vendor/safetyhook/src",
        "vendor/zydis/include",
        "vendor/zydis/dependencies/zycore/include",
        "vendor/zydis/src",
        "vendor/zdraw/zdraw/zdraw",
        "vendor/zdraw/zdraw/zdraw/external/freetype"
    )

    add_linkdirs("vendor/zdraw/zdraw/zdraw/external/freetype")
    add_links("freetype")

    add_files(
        "vendor/safetyhook/src/**.cpp",
        "vendor/zydis/src/*.c",
        "vendor/zdraw/zdraw/zdraw/zui/**.cpp",
        "vendor/zdraw/zdraw/zdraw/zscene/**.cpp",
        "vendor/zdraw/zdraw/zdraw/*.cpp"
    )

    add_defines("ZYDIS_STATIC_BUILD")
