#include "../hooks.hpp"
#include "../../entities/entities.hpp"

namespace hooks::handlers {
    std::uintptr_t __fastcall OnRemoveEntity(void* pEntitySystem, sdk::client::C_BaseEntity* pEntity, CHandle<sdk::client::C_BaseEntity> handle) {
        auto original = hooks::original::OnRemoveEntity.fastcall<std::uintptr_t>(pEntitySystem, pEntity, handle);

        if (!pEntity || !handle) return original;
        entities::RemoveEntity(static_cast<uint16_t>(handle & 0x7FFF));

        return original;
    }
}
