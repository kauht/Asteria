#pragma once

#include <shared_mutex>
#include <unordered_map>

#include <sdk/client_dll.hpp>
#include <sdk/cs2sdk.hpp>

namespace entities {
    using EntityMap = std::unordered_map<int, sdk::client::C_BaseEntity*>;

    extern EntityMap g_Entities;
    extern std::shared_mutex g_EntitiesMutex;

    void AddEntity(int index, sdk::client::C_BaseEntity* entity);
    void RemoveEntity(int index);
    sdk::client::C_BaseEntity* GetEntityByIndex(int index);
    sdk::client::C_BaseEntity* GetLocalPlayerPointer();
    sdk::client::C_BaseEntity* GetLocalPlayer();
    int GetLocalPlayerIndex();
    void PopulateExistingEntities();
}
