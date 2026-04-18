#include "util/logger.hpp"
#include "globals.hpp"
#include "core/hooks/hook_manager.hpp"
#include "core/features/manager.hpp"
#include "core/render/render.hpp"

#include <windows.h>
#include <thread>

void entry() {
    asteria::util::info("Asteria initializing...");

    if (!asteria::core::hooks::install()) return;
    if (!asteria::core::features::init()) asteria::util::error("Failed to init features.");

    asteria::util::info("Asteria hooked. Press DELETE to unload.");

    while (!(GetAsyncKeyState(VK_DELETE) & 1) && !asteria::g_request_unload) std::this_thread::sleep_for(std::chrono::milliseconds(100));

    asteria::util::info("Asteria unloading...");

    asteria::core::features::unload();
    asteria::core::hooks::uninstall();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    asteria::core::render::shutdown();
}

BOOL WINAPI DllMain(HINSTANCE, DWORD reason, LPVOID) {
    if (reason == DLL_PROCESS_ATTACH) std::thread(entry).detach();
    return TRUE;
}
