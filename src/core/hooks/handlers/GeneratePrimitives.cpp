#include "../hooks.hpp"
#include "../../features/chams/chams.hpp"

namespace hooks::handlers {
    void __fastcall hkGeneratePrimitives(void* scene, scenesystem::CSceneAnimatableObject* object, void* a3, scenesystem::c_mesh_primitive_output_buffer* render_buf)
    {
        features::chams::Chams(scene, object, a3, render_buf);
    }
}
