#pragma once
#include "sdk.hpp"
#include <cs2.hpp>
#include "../utils/modules/modules.hpp"

namespace sdk {

    inline client::CCSPlayerController* LocalController() noexcept {
        return GlobalPtr<client::CCSPlayerController>(modules::client, offsets::client::LocalPlayerController);
    }

    inline ifc::engine2::CEnginePVSManager* PVSManager() noexcept {
        return GlobalAt<ifc::engine2::CEnginePVSManager>(modules::engine2, offsets::engine2::PVSManager);
    }

    inline void* MaterialSystem() noexcept {
        if (!modules::materialsystem2) return nullptr;
        return *reinterpret_cast<void**>(
            iface::materialsystem2::VMaterialSystem2_001(reinterpret_cast<std::uintptr_t>(modules::materialsystem2)));
    }

}
