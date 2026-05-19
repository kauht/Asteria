#include "../hooks.hpp"
#include "../../features/chams/chams.hpp"

namespace hooks::handlers {
    void __fastcall hkGeneratePrimitives(void* scene, sdk::scenesystem::CSceneAnimatableObject* object, void* a3, sdk::scenesystem::c_mesh_primitive_output_buffer* render_buf)
    {
        features::chams::OnGeneratePrimitives(scene, object, a3, render_buf);
    }
}
