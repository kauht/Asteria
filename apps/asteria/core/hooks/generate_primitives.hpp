#pragma once

#include <safetyhook.hpp>
#include "../features/chams/chams.hpp"

namespace asteria::core::hooks {

extern SafetyHookInline g_generate_primitives_hook;

void __fastcall hk_generate_primitives(void* scene_system, features::chams::c_scene_animatable_object* object, void* render_ctx, features::chams::c_mesh_primitive_output_buffer* buf);

bool install_generate_primitives_hook();
void uninstall_generate_primitives_hook();

} // namespace asteria::core::hooks
