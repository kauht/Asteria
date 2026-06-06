#pragma once
#include <cs2.hpp>
#include "../utils/modules/modules.hpp"
#include "../utils/memory/memory.hpp"

class CGameEntitySystem {
public:
    template <typename T = void>
    T* GetBaseEntity(int index) noexcept {
        using Fn = T* (*)(void*, int);
        static auto fn = reinterpret_cast<Fn>(
            memory::FindPattern(pattern::client::GetBaseEntity, modules::client));
        return fn ? fn(this, index) : nullptr;
    }

    client::CEntityIdentity* GetIdentityByIndex(int index) noexcept {
        if (index < 0) return nullptr;
        auto chunk = *reinterpret_cast<uintptr_t*>(
            reinterpret_cast<uintptr_t>(this) + 0x10 + (index >> 9) * 8);
        if (!chunk) return nullptr;
        return reinterpret_cast<client::CEntityIdentity*>(chunk + (index & 0x1FF) * 0x70);
    }

    const char* GetDesignerName(int index) noexcept {
        auto* identity = GetIdentityByIndex(index);
        if (!identity || !GetBaseEntity(index)) return nullptr;
        return *reinterpret_cast<const char**>(&identity->m_designerName());
    }
};

namespace sdk {
    inline CGameEntitySystem* EntitySystem() noexcept {
        if (!modules::client) return nullptr;
        return *reinterpret_cast<CGameEntitySystem**>(
            reinterpret_cast<uintptr_t>(modules::client) + offsets::client::GameEntitySystem);
    }
}

template <typename T>
T* CHandle<T>::Get() const noexcept {
    if (!IsValid()) return nullptr;
    auto* entity_system = sdk::EntitySystem();
    if (!entity_system) return nullptr;
    return entity_system->GetBaseEntity<T>(static_cast<int>(GetIndex()));
}
