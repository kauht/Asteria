#include "util/logger.hpp"
#include <unordered_set>

#ifdef _WIN32
#include <windows.h>
#include <thread>
#endif

using namespace asteria::util;

using ConMsgFn = void (__cdecl *)(const char *, ...);

namespace asteria::util{
    // Memory
    // In memory.hpp or similar
    template<typename T>
    T read(uintptr_t addr) {
        return *reinterpret_cast<T*>(addr);
    }

    // Entity list
    uintptr_t getEntity(uintptr_t entityList, int index) {
        int ci = index & 0x7FFF;
        uintptr_t entry = read<uintptr_t>(entityList + 0x10 + 0x8 * (ci >> 9));
        if (!entry) return 0;
        return read<uintptr_t>(entry + 112 * (ci & 0x1FF));
    }


    // Modules
    struct Module {
        std::string name;
        HMODULE handle;

    };
    const std::vector<std::string> module_names = {
        "tier0.dll",
        "client.dll"
    };

    class Modules {
        public:
        Modules() {
            for (const auto& module : module_names) {
                HMODULE handle = GetModuleHandleA(module.c_str());
                if (handle) {
                    modules.push_back({module, handle});
                }
            }
        };
        ~Modules() = default;

        Module find(const std::string& name) {
            for (const auto& module : modules) {
                if (module.name == name) {
                    return module;
                }
            }
            info(std::format("Module not found: {}", name));
            return {name, 0};
        }

        private:
        std::vector<Module> modules{};
    };

}

void entry() {

    // Temp Offsets
    constexpr auto dwEntityList = 0x24AF268;
    constexpr auto dwLocalPlayerPawn = 0x2069B50;

    info("Asteria entry()");
    // Test Console
    {
        Modules modules;
        ConMsgFn ConMsg = reinterpret_cast<ConMsgFn>(GetProcAddress(modules.find("tier0.dll").handle, MAKEINTRESOURCEA(392)));
        if (!ConMsg) {
            debug("ConMsg not found");
            return;
        }
        ConMsg("Hello from Asteria!\n");

        uintptr_t client = (uintptr_t)modules.find("client.dll").handle;

        // Test Localplayer
        {
            if (!client) {
                debug("client.dll not found");
                return;
            }
            uintptr_t localPawn = *reinterpret_cast<uintptr_t*>(client + dwLocalPlayerPawn);
            if (!localPawn) {
                debug("localPlayerPawn not found");
                return;
            }
            int health = *reinterpret_cast<int*>(localPawn + 0x354);
            ConMsg(std::format("localPlayerPawn health: {}", health).c_str());
        }
        // Test Entity List
        {
            uintptr_t entityList = read<uintptr_t>(client + dwEntityList);
            if (!entityList) return;

            for (int i = 0; i < 64; i++) {
                uintptr_t controller = getEntity(entityList, i);
                if (!controller) continue;

                int health = read<int>(controller + 0x918);
                ConMsg(std::format("[{}] health: {}\n", i, health).c_str());

                char* name;
                name = read<char*>(controller + 0x860);
                if (name) {
                    ConMsg(std::format("[{}] name: {}\n", i, name).c_str());
                }

            }
        }
    }
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
