#include "modules.hpp"

namespace modules {
    namespace {
        struct Entry { const char* name; HMODULE* handle; };
        static const Entry kModules[] = {
            { "client.dll", &client },
            { "engine2.dll", &engine2 },
            { "inputsystem.dll", &inputsystem },
            { "materialsystem2.dll", &materialsystem2 },
            { "networksystem.dll", &networksystem },
            { "panorama.dll", &panorama },
            { "particles.dll", &particles        },
            { "pulse_system.dll", &pulse_system     },
            { "rendersystemdx11.dll", &rendersystemdx11 },
            { "resourcesystem.dll", &resourcesystem },
            { "scenesystem.dll", &scenesystem },
            { "schemasystem.dll", &schemasystem },
            { "server.dll", &server },
            { "tier0.dll", &tier0 },
            { "worldrenderer.dll", &worldrenderer },
        };
    }

    void Initialize() {
        for (auto& [name, handle] : kModules) {
            *handle = GetModuleHandleA(name);
            if (!*handle) {
                io::println("Failed to get {} module handle", name);
                return;
            }
        }
    }

    void Shutdown() {
        for (auto& [name, handle] : kModules)
            *handle = {};
    }
}
