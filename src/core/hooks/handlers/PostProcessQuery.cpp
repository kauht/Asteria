#include "../hooks.hpp"
#include "../../features/postfx/postfx.hpp"

namespace hooks::handlers {
    void* __fastcall hkPostProcessQuery(void* state, void* out, unsigned int key, void* def) {
        if (features::postfx::OnPostProcessQuery(key, static_cast<float*>(out)))
            return out;
        return original::PostProcessQuery.fastcall<void*>(state, out, key, def);
    }
}
