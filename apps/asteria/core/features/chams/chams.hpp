#pragma once

#include <cstdint>

namespace asteria::core::features::chams {

// handle to a Source2 material object (materialsystem2.dll)
struct c_material2 {};

// 'object' param in GeneratePrimitives
struct c_scene_animatable_object {};

// GeneratePrimitives fills an array of these
// in sub_180073700 in scenesystem.dll
struct c_mesh_draw_primitive {
    char pad_0000[32];
    c_material2* m_material;  // 0x20 — primary material slot
    c_material2* m_material2; // 0x28 — secondary material slot (usually same as primary)
    char pad_0030[32];
    uint32_t m_tint_color; // 0x50 — packed sRGB RGBA
    float m_alpha_scale;   // 0x54
    char pad_0058[4];
    uint16_t m_id;            // 0x5C — entity/team outline ID
    uint16_t m_lod_dist;      // 0x5E — LOD distance threshold
    uint8_t m_flag0;          // 0x60
    uint8_t m_flag1;          // 0x61
    uint16_t m_render_flags;  // 0x62 — controls shadow/depth pass participation
    uint16_t m_render_flags2; // 0x64
    char pad_0066[2];

    // returns the scene object that owns this mesh (+0x18)
    template <typename T> T* get_scene_object() { return *reinterpret_cast<T**>(reinterpret_cast<uint8_t*>(this) + 0x18); }
};
static_assert(sizeof(c_mesh_draw_primitive) == 104, "c_mesh_draw_primitive size mismatch");

// output buffer passed to GeneratePrimitives.
struct c_mesh_primitive_output_buffer {
    c_mesh_draw_primitive* m_out;
    int m_max_output_primitives;
    int m_start_primitive;
};

// called from the GeneratePrimitives hook for each scene object
// TRUE if the hook should NOT call the original again
bool render(void* scene_system, c_scene_animatable_object* object, void* render_ctx, c_mesh_primitive_output_buffer* render_buf);

using GeneratePrimitivesFn = void(__fastcall*)(void*, c_scene_animatable_object*, void*, c_mesh_primitive_output_buffer*);
void set_original(GeneratePrimitivesFn fn);

bool init();
void unload();

} // namespace asteria::core::features::chams
