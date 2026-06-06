#include "../hooks.hpp"
#include "../../../utils/entities/entities.hpp"

namespace hooks::handlers {
    void __fastcall hkAddEntity(void* sys, void* inst, uint32_t handle) {
        entities::OnAdd(sys, inst, handle);
        original::AddEntity.fastcall<void>(sys, inst, handle);
    }
}
