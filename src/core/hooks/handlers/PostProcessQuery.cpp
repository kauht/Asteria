#include "../hooks.hpp"
#include "../../features/postfx/postfx.hpp"

namespace hooks::handlers {
    void* __fastcall hkPostProcessQuery(void* state, void* out, unsigned int key, void* def) {
        auto* original = original::PostProcessQuery.fastcall<void*>(state, out, key, def);
        features::postfx::OnPostProcessQuery(key, static_cast<float*>(out));
        return original;
    }
}
