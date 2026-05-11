#include "entities.hpp"

#include <mutex>

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
}
