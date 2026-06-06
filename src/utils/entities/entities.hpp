#pragma once
#include <cstdint>
#include <mutex>
#include <vector>

namespace entities {
    enum class Type {
        Unknown = 0,
        PlayerController,
        Weapon,
        PlantedC4,
        GrenadeProjectile,
    };

    struct CachedEntity {
        uint32_t handle  = 0xFFFFFFFF;
        Type     type    = Type::Unknown;
        bool     draw    = false;
        bool     visible = false;
    };

    extern std::vector<CachedEntity> list;
    extern std::recursive_mutex      mutex;

    void OnAdd(void* sys, void* inst, uint32_t handle);
    void OnRemove(void* sys, void* inst, uint32_t handle);
}
