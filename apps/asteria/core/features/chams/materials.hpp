#pragma once
/// ! CAUTION | AI GENERATED | NEEDS MANUAL REVIEW !

// KV3 materials for chams styles
// Each style has two versions
//   _occ — occluded (through walls)
//   _vis — visible (visible)
//
//  Shaders:
//  csgo_character.vfx     - PBR character shader (metalness/roughness)
//  csgo_unlitgeneric.vfx  - flat unlit color, no lighting
//  csgo_effects.vfx       - effects shader (fresnel, translucency, additive blend)

#define KV3_HEADER "<!-- kv3 encoding:text:version{e21c7f3c-8a33-41c5-9977-a76d3a32aa0d} format:generic:version{7412167c-06e9-4698-aff2-e63eb59037e7} -->\n"

#define WHITE_TEX "materials/dev/primary_white_color_tga_21186c76.vtex"
#define DEFAULT_AO "materials/default/default_ao_tga_79a2e0d0.vtex"
#define DEFAULT_NM "materials/default/default_normal_tga_1b833b2a.vtex"
#define DEFAULT_MT "materials/default/default_metal_tga_8fbc2820.vtex"
#define DEFAULT_MK "materials/default/default_mask_tga_fde710a5.vtex"

// Applied to all occluded, disables depth so the mesh can render through walls
#define Z_DISABLE "    F_DISABLE_Z_BUFFERING = 1\n    F_DISABLE_Z_PREPASS = 1\n    F_DISABLE_Z_WRITE = 1\n"

namespace asteria::core::features::chams::materials {

// Glass
// The occluded variant uses Z_DISABLE so it shows through walls.
constexpr char glass_occ[] = KV3_HEADER R"({
    shader = "csgo_effects.vfx"
)" Z_DISABLE R"(    g_tColor = resource:")" WHITE_TEX R"("
    g_tMask1 = resource:")" DEFAULT_MK R"("
    g_tMask2 = resource:")" DEFAULT_MK R"("
    g_tMask3 = resource:")" DEFAULT_MK R"("
    g_flOpacityScale = 0.45
    g_flFresnelExponent = 0.75
    g_flFresnelFalloff = 1.0
    g_flFresnelMax = 0.0
    g_flFresnelMin = 1.0
    F_ADDITIVE_BLEND = 1
    F_TRANSLUCENT = 1
    g_vColorTint = [1.0, 1.0, 1.0, 1.0]
})";

constexpr char glass_vis[] = KV3_HEADER R"({
    shader = "csgo_effects.vfx"
    g_tColor = resource:")" WHITE_TEX R"("
    g_tMask1 = resource:")" DEFAULT_MK R"("
    g_tMask2 = resource:")" DEFAULT_MK R"("
    g_tMask3 = resource:")" DEFAULT_MK R"("
    g_flOpacityScale = 0.45
    g_flFresnelExponent = 0.75
    g_flFresnelFalloff = 1.0
    g_flFresnelMax = 0.0
    g_flFresnelMin = 1.0
    F_ADDITIVE_BLEND = 1
    F_TRANSLUCENT = 1
    g_vColorTint = [1.0, 1.0, 1.0, 1.0]
})";

// ---- Style 1: Flat ----
// csgo_unlitgeneric — no lighting, pure flat color.
constexpr char flat_occ[] = KV3_HEADER R"({
    shader = "csgo_unlitgeneric.vfx"
)" Z_DISABLE R"(    g_vColorTint = [1.0, 1.0, 1.0, 1.0]
    g_tColor = resource:")" WHITE_TEX R"("
})";

constexpr char flat_vis[] = KV3_HEADER R"({
    shader = "csgo_unlitgeneric.vfx"
    g_vColorTint = [1.0, 1.0, 1.0, 1.0]
    g_tColor = resource:")" WHITE_TEX R"("
})";

// ---- Style 2: Glow ----
// csgo_effects with fresnel — rim/outline glow effect.
constexpr char glow_occ[] = KV3_HEADER R"({
    Shader = "csgo_effects.vfx"
    g_flFresnelExponent = 7.0
    g_flFresnelFalloff = 10.0
    g_flFresnelMax = 0.1
    g_flFresnelMin = 1.0
    g_tColor = resource:")" WHITE_TEX R"("
    g_tMask1 = resource:")" DEFAULT_MK R"("
    g_tMask2 = resource:")" DEFAULT_MK R"("
    g_tMask3 = resource:")" DEFAULT_MK R"("
    g_tSceneDepth = resource:")" DEFAULT_MK R"("
    g_flToolsVisCubemapReflectionRoughness = 1.0
    g_flBeginMixingRoughness = 1.0
    g_vColorTint = [1.0, 1.0, 1.0, 0.0]
    F_IGNOREZ = 1
    F_DISABLE_Z_WRITE = 1
    F_DISABLE_Z_BUFFERING = 1
    F_RENDER_BACKFACES = 0
})";

constexpr char glow_vis[] = KV3_HEADER R"({
    Shader = "csgo_effects.vfx"
    g_flFresnelExponent = 7.0
    g_flFresnelFalloff = 10.0
    g_flFresnelMax = 0.1
    g_flFresnelMin = 1.0
    g_tColor = resource:")" WHITE_TEX R"("
    g_tMask1 = resource:")" DEFAULT_MK R"("
    g_tMask2 = resource:")" DEFAULT_MK R"("
    g_tMask3 = resource:")" DEFAULT_MK R"("
    g_tSceneDepth = resource:")" DEFAULT_MK R"("
    g_flToolsVisCubemapReflectionRoughness = 1.0
    g_flBeginMixingRoughness = 1.0
    g_vColorTint = [1.0, 1.0, 1.0, 0.0]
    F_IGNOREZ = 0
    F_DISABLE_Z_WRITE = 0
    F_DISABLE_Z_BUFFERING = 0
    F_RENDER_BACKFACES = 0
})";

// ---- Style 3: Latex ----
// csgo_character with zero metalness — shiny, reflective skin look.
constexpr char latex_occ[] = KV3_HEADER R"({
    shader = "csgo_character.vfx"
)" Z_DISABLE R"(    g_vColorTint = [1.0, 1.0, 1.0, 1.0]
    g_bFogEnabled = 0
    g_flMetalness = 0.0
    g_tColor = resource:")" WHITE_TEX R"("
    g_tAmbientOcclusion = resource:")" DEFAULT_AO R"("
    g_tNormal = resource:")" DEFAULT_NM R"("
    g_tMetalness = resource:")" DEFAULT_MT R"("
})";

constexpr char latex_vis[] = KV3_HEADER R"({
    shader = "csgo_character.vfx"
    g_vColorTint = [1.0, 1.0, 1.0, 1.0]
    g_bFogEnabled = 0
    g_flMetalness = 0.0
    g_tColor = resource:")" WHITE_TEX R"("
    g_tAmbientOcclusion = resource:")" DEFAULT_AO R"("
    g_tNormal = resource:")" DEFAULT_NM R"("
    g_tMetalness = resource:")" DEFAULT_MT R"("
})";

// ---- Style 4: Metallic ----
// csgo_character with max metalness — chrome mirror finish.
constexpr char metallic_occ[] = KV3_HEADER R"({
    shader = "csgo_character.vfx"
)" Z_DISABLE R"(    g_vColorTint = [1.0, 1.0, 1.0, 1.0]
    g_bFogEnabled = 0
    g_flMetalness = 1.0
    g_tColor = resource:")" WHITE_TEX R"("
    g_tAmbientOcclusion = resource:")" DEFAULT_AO R"("
    g_tNormal = resource:")" DEFAULT_NM R"("
    g_tMetalness = resource:")" WHITE_TEX R"("
})";

constexpr char metallic_vis[] = KV3_HEADER R"({
    shader = "csgo_character.vfx"
    g_vColorTint = [1.0, 1.0, 1.0, 1.0]
    g_bFogEnabled = 0
    g_flMetalness = 1.0
    g_tColor = resource:")" WHITE_TEX R"("
    g_tAmbientOcclusion = resource:")" DEFAULT_AO R"("
    g_tNormal = resource:")" DEFAULT_NM R"("
    g_tMetalness = resource:")" WHITE_TEX R"("
})";

} // namespace asteria::core::features::chams::materials
