#include <windows.h>
#include "globals.hpp"
#include "utils/modules/modules.hpp"
#include "utils/utils.hpp"
#include "core/hooks/hooks.hpp"
#include "core/entities/entities.hpp"

DWORD WINAPI entry(LPVOID) {
    io::Initialize();
    modules::Initialize();
    input::Initialize();
    config::Initialize();
    hooks::Install();
    // Entity initialize
    io::println("--- Asteria Initialized ---");

    while (!input::KeyDown(VK_DELETE)); // Wait for delete key to be pressed to exit

    io::println("--- Asteria Shutdown ---");
    // entity shutdown
    hooks::Uninstall();
    config::Shutdown();
    input::Shutdown();
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
