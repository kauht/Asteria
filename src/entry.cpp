#include <windows.h>
#include "globals.hpp"
#include "menu/render/render.hpp"
#include "utils/utils.hpp"
#include "core/hooks/hooks.hpp"
#include "core/features/features.hpp"

DWORD WINAPI entry(LPVOID) {
    io::Initialize();
    modules::Initialize();
    config::Initialize();
    features::Initialize();
    hooks::Install();
    io::println("--- Asteria Initialized ---");

    while (!input::KeyDown(VK_DELETE)); // Wait for delete key to be pressed to exit

    io::println("--- Asteria Shutdown ---\n\nYou may now close this window...");
    // entity shutdown
    features::Shutdown();
    hooks::Uninstall();
    config::Shutdown();
    modules::Shutdown();
    io::Shutdown();

    Sleep(200);
    FreeLibraryAndExitThread(globals::module, 0);
}

BOOL WINAPI DllMain(HINSTANCE hinst, DWORD reason, LPVOID) {
    if (reason == DLL_PROCESS_ATTACH) {
        globals::module = hinst;
        DisableThreadLibraryCalls(hinst);
        CloseHandle(CreateThread(nullptr, 0, entry, nullptr, 0, nullptr));
    }
    return TRUE;
}
