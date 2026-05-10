#pragma once
#include <windows.h>
#include "../io/io.hpp"

namespace modules {
    void Initialize();
    void Shutdown();

    inline HMODULE client;
    inline HMODULE engine2;
    inline HMODULE inputsystem;
    inline HMODULE materialsystem2;
    inline HMODULE networksystem;
    inline HMODULE panorama;
    inline HMODULE particles;
    inline HMODULE pulse_system;
    inline HMODULE rendersystemdx11;
    inline HMODULE resourcesyystem;
    inline HMODULE scenesystem;
    inline HMODULE schemasystem;
    inline HMODULE server;
    inline HMODULE tier0;
    inline HMODULE worldrenderer;

    namespace patterns {



    }
}
