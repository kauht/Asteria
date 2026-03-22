set_project("asteria")
set_version("1.0.0")
set_languages("cxx23")

add_rules("mode.debug", "mode.release")

-- add_rules("plugin.compile_commands.autoupdate", { outputdir = "build" })

set_targetdir("bin/$(mode)")

target("asteria")
set_kind("shared")
add_files("src/asteria/**.cpp")

if is_plat("windows") then
    add_includedirs("src/asteria/external/minhook/include")
    add_ldflags("src/asteria/external/minhook/lib/libMinHook.x64.lib", "link")
    add_syslinks("Psapi")
end

target("injector")
set_kind("binary")
add_files("src/injector/**.cpp")
