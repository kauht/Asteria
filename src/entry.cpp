#include <windows.h>
#include "globals.hpp"
#include "utils/modules/modules.hpp"
#include "utils/utils.hpp"

DWORD WINAPI entry(LPVOID) {
    io::Initialize();
    modules::Initialize();
    input::Initialize();
    config::Initialize();
    io::println("--- Asteria Initialized ---");

    while (!input::KeyDown(VK_DELETE)); // Wait for delete key to be pressed to exit

    io::println("--- Asteria Shutdown ---");
    config::Shutdown();
    input::Shutdown();
    modules::Shutdown();
    io::Shutdown();

    FreeLibraryAndExitThread(globals::module, 0);
}

BOOL WINAPI DllMain(HINSTANCE hinst, DWORD reason, LPVOID) {
    if (reason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(globals::module);
        globals::module = hinst;
        CloseHandle(CreateThread(nullptr, 0, entry, nullptr, 0, nullptr));
    }
    return TRUE;
}
