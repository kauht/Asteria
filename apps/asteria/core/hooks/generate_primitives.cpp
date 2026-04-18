#include "generate_primitives.hpp"
#include "../../util/logger.hpp"
#include "../../util/memory/memory.hpp"

namespace asteria::core::hooks {

SafetyHookInline g_generate_primitives_hook;

void __fastcall hk_generate_primitives(void* scene_system, features::chams::c_scene_animatable_object* object, void* render_ctx, features::chams::c_mesh_primitive_output_buffer* buf) {
    if (!features::chams::render(scene_system, object, render_ctx, buf)) g_generate_primitives_hook.call<void>(scene_system, object, render_ctx, buf);
}

static void call_original(void* scene_system, features::chams::c_scene_animatable_object* object, void* render_ctx, features::chams::c_mesh_primitive_output_buffer* buf) {
    g_generate_primitives_hook.call<void>(scene_system, object, render_ctx, buf);
}

bool install_generate_primitives_hook() {
    uintptr_t addr = asteria::util::find_pattern("48 8B C4 48 89 58 08 48 89 50 10 55 56 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ?", "scenesystem.dll");

    if (!addr) {
        asteria::util::error("GeneratePrimitives: pattern not found.");
        return false;
    }

    asteria::util::log("GeneratePrimitives found at: {:#x}", addr);

    g_generate_primitives_hook = safetyhook::create_inline(reinterpret_cast<void*>(addr), reinterpret_cast<void*>(hk_generate_primitives));

    if (!g_generate_primitives_hook) {
        asteria::util::error("GeneratePrimitives: hook failed.");
        return false;
    }

    features::chams::set_original(call_original);
    asteria::util::info("GeneratePrimitives: hook installed.");
    return true;
}

void uninstall_generate_primitives_hook() {
    features::chams::set_original(nullptr);
    g_generate_primitives_hook.reset();
    asteria::util::info("GeneratePrimitives: hook removed.");
}

} // namespace asteria::core::hooks
