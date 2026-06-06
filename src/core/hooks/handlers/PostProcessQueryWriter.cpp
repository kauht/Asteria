#include "../hooks.hpp"
#include "../../features/world/wetness.hpp"

namespace hooks::handlers {
    void* __fastcall hkPostProcessQueryWriter(void* store, uint32_t key, void* value) {
        features::wetness::OnPostProcessQueryWriter(key, static_cast<float*>(value));
        return original::PostProcessQueryWriter.fastcall<void*>(store, key, value);
    }
}
