set_project("asteria")
set_version("1.0.0")
set_languages("cxx23")

add_rules("mode.debug", "mode.release")

add_rules("plugin.compile_commands.autoupdate", { outputdir = "." })

set_targetdir("bin/$(mode)")

target("asteria")
set_kind("shared")
add_files("apps/asteria/**.cpp")

if is_plat("windows") then
    add_includedirs("external/")
    add_includedirs("external/safetyhook")
    add_files("external/safetyhook/safetyhook.cpp", "external/safetyhook/Zydis.c")
    add_syslinks("Psapi", "gdi32")
end

target("injector")
set_kind("binary")
add_files("apps/injector/**.cpp")
