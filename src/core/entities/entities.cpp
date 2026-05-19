#include "entities.hpp"
#include "../../utils/modules/modules.hpp"
#include "../../utils/memory/memory.hpp"
#include <signatures/signatures.hpp>
#include <sdk/offsets.hpp>

#include <mutex>
#include <shared_mutex>

namespace entities {
    EntityMap g_Entities{};
    std::shared_mutex g_EntitiesMutex{};

    void AddEntity(int index, sdk::client::C_BaseEntity* entity) {
        if (index < 0 || entity == nullptr) {
            return;
        }

        std::unique_lock lock(g_EntitiesMutex);
        g_Entities[index] = entity;
    }

    void RemoveEntity(int index) {
        std::unique_lock lock(g_EntitiesMutex);
        g_Entities.erase(index);
    }

    sdk::client::C_BaseEntity* GetEntityByIndex(int index) {
        std::shared_lock lock(g_EntitiesMutex);
        const auto it = g_Entities.find(index);
        if (it == g_Entities.end()) {
            return nullptr;
        }

        return it->second;
    }

    sdk::client::C_BaseEntity* GetLocalPlayer() {
        return GetLocalPlayerPointer();
    }

    sdk::client::C_BaseEntity* GetLocalPlayerPointer() {
        for (int i = 1; i <= 64; ++i) {
            auto* ctrl = GetEntityByIndex(i);
            if (!ctrl) continue;
            // CBasePlayerController::m_bIsLocalPlayerController at 0x788
            if (*reinterpret_cast<bool*>(reinterpret_cast<uint8_t*>(ctrl) + 0x788))
                return ctrl;
        }
        return nullptr;
    }

    int GetLocalPlayerIndex() {
        auto* local = GetLocalPlayerPointer();
        if (!local) return 0;
        try {
            return *reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(local) + 0x40);
        } catch (...) {
            return 0;
        }
    }

    void PopulateExistingEntities() {
        uintptr_t client_base = reinterpret_cast<uintptr_t>(modules::client);
        if (!client_base) return;

        auto entity_system = *reinterpret_cast<void**>(client_base + cs2::offsets::client::GameEntitySystemPtr);
        if (!entity_system) return;

        int highest = *reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(entity_system) + 0x1510);
        if (highest <= 0 || highest > 32768)
            highest = 16384;

        auto* chunks = reinterpret_cast<uintptr_t*>(reinterpret_cast<uint8_t*>(entity_system) + 0x10);
        for (int i = 0; i <= highest; ++i) {
            int nChunk = i / 512;
            int nSlot = i % 512;
            auto pChunk = *reinterpret_cast<uintptr_t*>(chunks + nChunk);
            if (!pChunk) continue;
            auto* identity = reinterpret_cast<uint8_t*>(pChunk + nSlot * 0x70);
            auto* entity = *reinterpret_cast<sdk::client::C_BaseEntity**>(identity);
            if (entity)
                AddEntity(i, entity);
        }
    }

}
