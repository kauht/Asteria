#include "entities.hpp"
#include "../../sdk/game.hpp"
#include <algorithm>
#include <string_view>

namespace entities {
    std::vector<CachedEntity> list;
    std::recursive_mutex mutex;

    static Type GetEntityType(int idx) {
        if (idx >= 1 && idx <= 64)
            return Type::PlayerController;

        auto* entity_system = sdk::EntitySystem();
        if (!entity_system) return Type::Unknown;

        const auto name = std::string(entity_system->GetDesignerName(idx));
        if (name.empty()) return Type::Unknown;

        if (name == "planted_c4")        return Type::PlantedC4;
        if (name.contains("projectile")) return Type::GrenadeProjectile;
        if (name.starts_with("weapon_")) return Type::Weapon;

        return Type::Unknown;
    }

    void OnAdd(void* sys, void* inst, uint32_t handle) {
        std::scoped_lock lock(mutex);

        auto* entity = static_cast<client::C_BaseEntity*>(inst);
        if (!entity) return;

        const Type type = GetEntityType(static_cast<int>(handle & 0x7FFF));
        if (type == Type::Unknown) return;

        auto it = std::find_if(list.begin(), list.end(), [handle](const CachedEntity& e) {
            return e.handle == handle;
        });

        if (it == list.end()) {
            list.push_back({ handle, type });
        } else {
            it->handle = handle;
            it->type   = type;
        }
    }

    void OnRemove(void* sys, void* inst, uint32_t handle) {
        std::scoped_lock lock(mutex);

        auto it = std::find_if(list.begin(), list.end(), [handle](const CachedEntity& e) {
            return e.handle == handle;
        });

        if (it != list.end()) {
            it->draw = false;
            it->type = Type::Unknown;
        }

        std::erase_if(list, [](const CachedEntity& e) {
            return e.type == Type::Unknown;
        });
    }
}
