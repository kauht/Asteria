#include "util/logger.hpp"

#ifdef _WIN32
#include <windows.h>
#include <thread>
#endif

using namespace asteria::util;

void entry() {
    info("Asteria entry()");


}

#ifdef _WIN32

BOOL WINAPI DllMain(HINSTANCE /*hinst*/, DWORD reason, LPVOID /*reserved*/) {
    switch (reason) {
    case DLL_PROCESS_ATTACH:
        info("Asteria Loaded");
        std::thread(entry).detach();
        break;
    case DLL_PROCESS_DETACH:
        info("Asteria unloading");
        break;
    default:
        break;
    }
    return TRUE;
}

#else

__attribute__((constructor))
static void asteria_start() {
    info("Asteria Loaded");
}

__attribute__((destructor))
static void asteria_end() {
    info("Asteria unloading");
}

#endif
