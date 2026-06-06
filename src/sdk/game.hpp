#pragma once
#include "sdk.hpp"
#include "entity_system.hpp"
#include "../utils/modules/modules.hpp"

namespace sdk {

    inline ifc::inputsystem::CInputSystem* InputSystem() noexcept {
        return GetInterface<ifc::inputsystem::CInputSystem>(modules::inputsystem, "InputSystemVersion001");
    }

    inline ifc::materialsystem2::CMaterialSystem2* MaterialSystem() noexcept {
        return GetInterface<ifc::materialsystem2::CMaterialSystem2>(modules::materialsystem2, "VMaterialSystem2_001");
    }

    inline ifc::engine2::CEnginePVSManager* PVSManager() noexcept {
        return GlobalAt<ifc::engine2::CEnginePVSManager>(modules::engine2, offsets::engine2::pPVSManager);
    }

    inline client::CCSPlayerController* LocalController() noexcept {
        return GlobalPtr<client::CCSPlayerController>(modules::client, offsets::client::LocalPlayerController);
    }

    inline client::C_CSPlayerPawn* LocalPawn() noexcept {
        return static_cast<client::C_CSPlayerPawn*>(LocalController()->m_hPawn().Get());
    }

}
