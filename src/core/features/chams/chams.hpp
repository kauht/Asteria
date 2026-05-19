#pragma once
#include "vmats.hpp"
#include "materials.hpp"
#include "../../../utils/config/config.hpp"
#include "../../../core/entities/entities.hpp"
#include <sdk/scenesystem_dll.hpp>

namespace features::chams {
    void Initialize();
    void OnGeneratePrimitives(void* scene, sdk::scenesystem::CSceneAnimatableObject* sceneObject, void* ctx, sdk::scenesystem::c_mesh_primitive_output_buffer* render_buf);
}
