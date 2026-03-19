#include <print>
#include "utils/logger.hpp"

__attribute__((constructor))
void entry() {
    std::println("asteria: main_entry called\n");

    info(std::string("Asteria DLL_ATTACH - pid=") + std::to_string(static_cast<unsigned long>(GetCurrentProcessId())) + " module=" + std::to_string(reinterpret_cast<std::uintptr_t>(hInstance)));
    debug(std::string("DllMain ulReason=") + std::to_string(static_cast<unsigned long>(ulReason)) + " fImpLoad=" + std::to_string(reinterpret_cast<std::uintptr_t>(fImpLoad)));
    info("Asteria Initialized");
}
__attribute__((destructor))
void exit() {
    std::println("asteria: main_entry exiting\n");
}

#ifdef _WIN32
#include <windows.h>
BOOL WINAPI DllMain(HINSTANCE hinst, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        entry();
    }
    return TRUE;
}
#endif
