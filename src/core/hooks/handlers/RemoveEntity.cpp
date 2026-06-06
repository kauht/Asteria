#include "../hooks.hpp"
#include "../../../utils/entities/entities.hpp"

namespace hooks::handlers {
    void __fastcall hkRemoveEntity(void* sys, void* inst, uint32_t handle) {
        entities::OnRemove(sys, inst, handle);
        original::RemoveEntity.fastcall<void>(sys, inst, handle);
    }
}
