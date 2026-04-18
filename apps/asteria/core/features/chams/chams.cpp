#include "chams.hpp"
#include "materials_init.hpp"
#include "../../../util/logger.hpp"
#include "../../../util/memory/memory.hpp"
#include "../../../globals.hpp"

namespace asteria::core::features::chams {

c_material2* g_mats[NUM_STYLES][2] = {};

// ---- Color ----

static uint32_t rgba_to_dword(const float* rgba) {
    uint8_t r = static_cast<uint8_t>(rgba[0] * 255.0f);
    uint8_t g = static_cast<uint8_t>(rgba[1] * 255.0f);
    uint8_t b = static_cast<uint8_t>(rgba[2] * 255.0f);
    uint8_t a = static_cast<uint8_t>(rgba[3] * 255.0f);
    return r | (g << 8) | (b << 16) | (a << 24);
}

// ---- Mesh ----

static void set_mesh_material(c_mesh_draw_primitive* mesh, c_material2* material, const float* color) {
    if (material) { mesh->m_material = material; mesh->m_material2 = material; }
    mesh->m_tint_color = rgba_to_dword(color);
    mesh->m_render_flags  &= ~static_cast<uint16_t>(0x0105);
    mesh->m_render_flags2 &= ~static_cast<uint16_t>(0x0001);
}

// ---- Original ----

static GeneratePrimitivesFn g_original = nullptr;
void set_original(GeneratePrimitivesFn fn) { g_original = fn; }

// ---- PVS ----

static bool try_disable_pvs() {
    uintptr_t site = asteria::util::find_pattern("48 8D 0D ? ? ? ? 33 D2 FF 50", "engine2.dll");
    if (!site) return false;
    void*  pvs_manager = reinterpret_cast<void*>(site + 7 + *reinterpret_cast<int32_t*>(site + 3));
    void** vtable      = *reinterpret_cast<void***>(pvs_manager);
    if (!vtable) return false;
    reinterpret_cast<void(__fastcall*)(void*, bool)>(vtable[6])(pvs_manager, false);
    return true;
}

// ---- Player identification ----
// +0xB0 == null     — world props always have a non-null internal scene ptr
// bit 49 of +0x80   — player-specific engine flag
// mesh_count == 5   — filters viewmodels and other player-owned objects

static bool is_player(c_scene_animatable_object* object, int mesh_count) {
    if (!object || mesh_count != 5) return false;
    auto*    base       = reinterpret_cast<uint8_t*>(object);
    void*    scene_ptr  = *reinterpret_cast<void**>(base + 0xB0);
    uint64_t flags      = *reinterpret_cast<uint64_t*>(base + 0x80);
    return scene_ptr == nullptr && (flags & 0x2000000000000ULL) != 0;
}

// ---- Local player detection ----
// The local player's scene object is called multiple times per frame (main view + shadow passes).
// We track which objects we've seen this frame and skip any that appear more than once.

static constexpr int MAX_SEEN = 64;
static void*         g_seen_this_frame[MAX_SEEN] = {};
static int           g_seen_count                = 0;
static void*         g_local_obj                 = nullptr;
static void*         g_last_render_buf            = nullptr;

static void new_frame(void* render_buf) {
    if (render_buf == g_last_render_buf) return;
    g_last_render_buf = render_buf;
    g_seen_count      = 0;
}

// Returns true if this is the first time we've seen this object this frame.
// If it's the second time, it's the local player — record it and skip.
static bool first_time_this_frame(void* object) {
    for (int i = 0; i < g_seen_count; i++) {
        if (g_seen_this_frame[i] == object) {
            g_local_obj = object; // seen twice = local player
            return false;
        }
    }
    if (g_seen_count < MAX_SEEN) g_seen_this_frame[g_seen_count++] = object;
    return true;
}

// ---- Render ----

bool render(void* scene_system, c_scene_animatable_object* object, void* render_ctx, c_mesh_primitive_output_buffer* render_buf) {
    if (!asteria::g_chams_enabled || !object || !render_buf || !g_original) return false;

    // Skip shadow passes — bit 24 of *(*(render_ctx+16) + 0x48)
    if (render_ctx) {
        auto* view_desc = *reinterpret_cast<uint8_t**>(reinterpret_cast<uint8_t*>(render_ctx) + 16);
        if (view_desc && ((*reinterpret_cast<uint64_t*>(view_desc + 0x48) >> 24) & 1)) return false;
    }

    new_frame(render_buf->m_out);

    if (object == g_local_obj) return false;
    if (!first_time_this_frame(object)) return false;

    // Probe: call original once to get mesh count, then check if it's a player
    int mesh_start = render_buf->m_start_primitive;
    g_original(scene_system, object, render_ctx, render_buf);
    int mesh_count = render_buf->m_start_primitive - mesh_start;

    if (!is_player(object, mesh_count)) return true;

    // Apply occluded material to the probe meshes, then call original again for visible pass
    int occ_style = asteria::g_chams_occ_style;
    if (occ_style < 0 || occ_style >= NUM_STYLES) occ_style = 0;
    int vis_style = asteria::g_chams_vis_style;
    if (vis_style < 0 || vis_style >= NUM_STYLES) vis_style = 0;

    if (asteria::g_chams_visible_only) {
        for (int i = mesh_start; i < render_buf->m_start_primitive; ++i)
            set_mesh_material(&render_buf->m_out[i], g_mats[vis_style][1], asteria::g_chams_vis_color);
    } else {
        for (int i = mesh_start; i < render_buf->m_start_primitive; ++i)
            set_mesh_material(&render_buf->m_out[i], g_mats[occ_style][0], asteria::g_chams_occ_color);

        int vis_start = render_buf->m_start_primitive;
        g_original(scene_system, object, render_ctx, render_buf);
        for (int i = vis_start; i < render_buf->m_start_primitive; ++i)
            set_mesh_material(&render_buf->m_out[i], g_mats[vis_style][1], asteria::g_chams_vis_color);
    }
    return true;
}

// ---- Init / Unload ----

bool init() {
    asteria::util::info("Chams: initializing...");
    if (try_disable_pvs()) asteria::util::info("Chams: PVS disabled.");
    else                   asteria::util::error("Chams: PVS disable failed.");
    init_materials();
    return true;
}

void unload() { asteria::util::info("Chams: unloaded."); }

} // namespace asteria::core::features::chams
