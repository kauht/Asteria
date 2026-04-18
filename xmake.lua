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
        add_includedirs("external/imgui")
        add_files("external/safetyhook/safetyhook.cpp", "external/safetyhook/Zydis.c")
        add_files("external/imgui/*.cpp")
        add_syslinks("Psapi", "gdi32")
        add_links("dxgi", "d3d11", "d3dcompiler", "user32.lib")
    end

target("injector")
    set_optimize("none")
    set_kind("binary")
    add_files("apps/injector/**.cpp")

-- Run: xmake fmt
-- Formats all source files under apps/asteria using clang-format.
-- Finds clang-format from PATH or the Visual Studio LLVM installation.
task("fmt")
    set_menu {
        usage = "xmake fmt",
        description = "Format all source files with clang-format"
    }
    on_run(function()
        import("lib.detect.find_program")

        -- Try PATH first, then common VS install locations
        local cf = find_program("clang-format")
        if not cf then
            local vs_paths = {
                "C:\\Program Files\\Microsoft Visual Studio\\18\\Community\\VC\\Tools\\Llvm\\x64\\bin\\clang-format.exe",
                "C:\\Program Files\\Microsoft Visual Studio\\17\\Community\\VC\\Tools\\Llvm\\x64\\bin\\clang-format.exe",
                "C:\\Program Files (x86)\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\bin\\clang-format.exe",
            }
            for _, p in ipairs(vs_paths) do
                if os.isfile(p) then cf = p; break end
            end
        end

        if not cf then
            print("clang-format not found. Add it to PATH or install via VS Installer -> C++ Clang tools.")
            return
        end

        local files = os.files("apps/asteria/**.cpp")
        for _, f in ipairs(os.files("apps/asteria/**.hpp")) do
            table.insert(files, f)
        end

        for _, f in ipairs(files) do
            os.execv(cf, { "-i", f })
        end

        print(string.format("Formatted %d files.", #files))
    end)
