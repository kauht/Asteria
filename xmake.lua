set_project("asteria")
set_version("1.0.0")
set_languages("cxx23")

add_rules("mode.debug", "mode.release")

add_rules("plugin.compile_commands.autoupdate", { outputdir = "build" })

set_targetdir("bin/$(mode)")

target("asteria")
    set_kind("shared")
    add_files("src/asteria/**.cpp")
    add_cxxflags("-fmodules", { force = true })

target("injector")
    set_kind("binary")
    add_files("src/injector/**.cpp")
