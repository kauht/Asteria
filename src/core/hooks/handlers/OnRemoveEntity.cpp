#include "../hooks.hpp"

void* __fastcall OnRemoveEntity(void* pEntitySystem, void* pEntity, uint32_t handle) {
    // Remove from local entity list cache
    // return call original
    return 0;
}
