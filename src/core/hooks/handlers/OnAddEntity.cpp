#include "../hooks.hpp"
#include "../../entities/entities.hpp"

namespace hooks::handlers {
    std::uintptr_t __fastcall OnAddEntity(void* pEntitySystem, sdk::client::C_BaseEntity* pEntity, CHandle<sdk::client::C_BaseEntity> handle) {
        auto original = hooks::original::OnAddEntity.fastcall<std::uintptr_t>(pEntitySystem, pEntity, handle);

        if (!pEntity || !handle) return original;
        entities::AddEntity(static_cast<uint16_t>(handle & 0x7FFF), pEntity); // Get index from handle by getting the lower 16 bits as a uint16_t

        return original;
    }
}
