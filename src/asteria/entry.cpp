#include <print>
#include "util/logger.hpp"
#include <pthread.h>
#include <thread>
#include <unistd.h>
#include <dlfcn.h>
#include "util/hook/hook.hpp"

using namespace asteria::util;

void entry() {

}

__attribute__((constructor))
void init() {
    std::println("asteria: init() called\n");

    info(std::string("Asteria init() called - pid=") + std::to_string(static_cast<unsigned long>(getpid())) + " module=" + std::to_string(reinterpret_cast<std::uintptr_t>(dlopen(NULL, RTLD_NOW))));
    info("Asteria Initialized");

    std::thread(entry).detach();
}
__attribute__((destructor))
void exit() {
    info(std::string("Asteria exit() called"));
}

#ifdef _WIN32
#include <windows.h>
BOOL WINAPI DllMain(HINSTANCE hinst, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)entry, NULL, 0, NULL);
    }
    return TRUE;
}
#endif
