#pragma once

namespace features::chams {
    void* MakeMaterial(const char* name, const char* kv3_text);
    void* MakeWireMaterial(const char* name, float r, float g, float b, float a);
}

namespace VMat
{

    static constexpr char Flat[] =
        R"(<!-- kv3 encoding:text:version{e21c7f3c-8a33-41c5-9977-a76d3a32aa0d} format:generic:version{7412167c-06e9-4698-aff2-e63eb59037e7} -->
{
    shader = "csgo_unlitgeneric.vfx"
    F_RENDER_BACKFACES = 0
    F_UNLIT = 1
    F_TRANSLUCENT = 1
    F_BLEND_MODE = 1
    g_vColorTint = [1.0, 1.0, 1.0, 1.0]
    g_tColor = resource:"materials/dev/primary_white_color_tga_21186c76.vtex"
})";

    static constexpr char Glow[] =
        R"(<!-- kv3 encoding:text:version{e21c7f3c-8a33-41c5-9977-a76d3a32aa0d} format:generic:version{7412167c-06e9-4698-aff2-e63eb59037e7} -->
{
    shader = "csgo_effects.vfx"
    g_tColor = resource:"materials/dev/primary_white_color_tga_21186c76.vtex"
    g_tMask1 = resource:"materials/default/default_mask_tga_344101f8.vtex"
    g_tMask2 = resource:"materials/default/default_mask_tga_344101f8.vtex"
    g_tMask3 = resource:"materials/default/default_mask_tga_344101f8.vtex"
    g_flColorBoost = 8
    g_flOpacityScale = 0.5
    g_flFresnelExponent = 10
    g_flFresnelFalloff = 10
    g_flFresnelMax = 0
    g_flFresnelMin = 1
    F_ADDITIVE_BLEND = 1
    F_BLEND_MODE = 1
    F_TRANSLUCENT = 1
    F_IGNOREZ = 1
    F_DISABLE_Z_BUFFERING = 0
    F_RENDER_BACKFACES = 0
    g_vColorTint = [1.0, 1.0, 1.0, 0.5]
})";

    static constexpr char Electric[] =
        R"(<!-- kv3 encoding:text:version{e21c7f3c-8a33-41c5-9977-a76d3a32aa0d} format:generic:version{7412167c-06e9-4698-aff2-e63eb59037e7} -->
{
    shader = "csgo_unlitgeneric.vfx"
    F_TRANSLUCENT = 1
    F_ADDITIVE_BLEND = 1
    F_NO_CULLING = 1
    F_UNLIT = 1
    F_DISABLE_Z_PREPASS = 0
    F_DISABLE_Z_WRITE = 0
    F_DISABLE_Z_BUFFERING = 0
    g_tColor = resource:"materials/particle/tile/tile_electric_01.vtex"
    g_vTexCoordScale = [2.0, 2.0]
    g_vTexCoordOffset = [0.0, 0.0]
    g_vTexCoordScrollSpeed = [0.45, 0.25]
    g_flFresnelExponent = 1.0
    g_flFresnelFalloff = 1.0
    g_flFresnelMax = 1.0
    g_vOverrideColor = [1.0, 1.0, 1.0, 1.0]
})";

    static constexpr char Chrome[] =
        R"(<!-- kv3 encoding:text:version{e21c7f3c-8a33-41c5-9977-a76d3a32aa0d} format:generic:version{7412167c-06e9-4698-aff2-e63eb59037e7} -->
{
    shader = "csgo_complex.vfx"
    F_PAINT_VERTEX_COLORS = 1
    F_TRANSLUCENT = 1
    F_SPECULAR = 1
    F_RENDER_BACKFACES = 0
    g_flAmbientOcclusionDirectSpecular = 1.000000
    g_flMetalness = 0.000000
    g_flRoughness = 0.050000
    g_vColorTint = [1.0, 1.0, 1.0, 1.0]
    g_tColor = resource:"materials/dev/primary_white_color_tga_21186c76.vtex"
    g_tNormal = resource:"materials/default/default_normal_tga_7652cb.vtex"
    g_tAmbientOcclusion = resource:"materials/default/default_ao_tga_79a2e0d0.vtex"
})";

    static constexpr char FlatOCC[] =
        R"(<!-- kv3 encoding:text:version{e21c7f3c-8a33-41c5-9977-a76d3a32aa0d} format:generic:version{7412167c-06e9-4698-aff2-e63eb59037e7} -->
{
    shader = "csgo_unlitgeneric.vfx"
    F_RENDER_BACKFACES = 0
    F_UNLIT = 1
    F_TRANSLUCENT = 1
    F_BLEND_MODE = 1
    F_DISABLE_Z_BUFFERING = 1
    F_DISABLE_Z_PREPASS = 1
    F_DISABLE_Z_WRITE = 1
    g_vColorTint = [1.0, 1.0, 1.0, 1.0]
    g_tColor = resource:"materials/dev/primary_white_color_tga_21186c76.vtex"
})";

    static constexpr char GlowOCC[] =
        R"(<!-- kv3 encoding:text:version{e21c7f3c-8a33-41c5-9977-a76d3a32aa0d} format:generic:version{7412167c-06e9-4698-aff2-e63eb59037e7} -->
{
    shader = "csgo_effects.vfx"
    g_tColor = resource:"materials/dev/primary_white_color_tga_21186c76.vtex"
    g_tMask1 = resource:"materials/default/default_mask_tga_344101f8.vtex"
    g_tMask2 = resource:"materials/default/default_mask_tga_344101f8.vtex"
    g_tMask3 = resource:"materials/default/default_mask_tga_344101f8.vtex"
    g_flColorBoost = 8
    g_flOpacityScale = 0.5
    g_flFresnelExponent = 10
    g_flFresnelFalloff = 10
    g_flFresnelMax = 0
    g_flFresnelMin = 1
    F_IGNOREZ = 1
    F_ADDITIVE_BLEND = 1
    F_BLEND_MODE = 1
    F_TRANSLUCENT = 1
    F_DISABLE_Z_BUFFERING = 1
    F_DISABLE_Z_PREPASS = 0
    F_DISABLE_Z_WRITE = 1
    F_RENDER_BACKFACES = 0
    g_vColorTint = [1.0, 1.0, 1.0, 0.5]
})";

    static constexpr char ElectricOCC[] =
        R"(<!-- kv3 encoding:text:version{e21c7f3c-8a33-41c5-9977-a76d3a32aa0d} format:generic:version{7412167c-06e9-4698-aff2-e63eb59037e7} -->
{
    shader = "csgo_unlitgeneric.vfx"
    F_TRANSLUCENT = 1
    F_ADDITIVE_BLEND = 1
    F_NO_CULLING = 1
    F_UNLIT = 1
    F_DISABLE_Z_BUFFERING = 1
    F_DISABLE_Z_PREPASS = 0
    F_DISABLE_Z_WRITE = 1
    g_tColor = resource:"materials/particle/tile/tile_electric_01.vtex"
    g_vTexCoordScale = [2.0, 2.0]
    g_vTexCoordOffset = [0.0, 0.0]
    g_vTexCoordScrollSpeed = [0.45, 0.25]
    g_flFresnelExponent = 1.0
    g_flFresnelFalloff = 1.0
    g_flFresnelMax = 1.0
    g_vOverrideColor = [1.0, 1.0, 1.0, 1.0]
})";

    static constexpr char ChromeOCC[] =
        R"(<!-- kv3 encoding:text:version{e21c7f3c-8a33-41c5-9977-a76d3a32aa0d} format:generic:version{7412167c-06e9-4698-aff2-e63eb59037e7} -->
{
    shader = "csgo_complex.vfx"
    F_PAINT_VERTEX_COLORS = 1
    F_TRANSLUCENT = 1
    F_SPECULAR = 1
    F_RENDER_BACKFACES = 0
    F_DISABLE_Z_BUFFERING = 1
    F_DISABLE_Z_PREPASS = 0
    F_DISABLE_Z_WRITE = 1
    g_flAmbientOcclusionDirectSpecular = 1.000000
    g_flMetalness = 0.000000
    g_flRoughness = 0.050000
    g_tColor = resource:"materials/dev/primary_white_color_tga_21186c76.vtex"
    g_tNormal = resource:"materials/default/default_normal_tga_7652cb.vtex"
    g_tAmbientOcclusion = resource:"materials/default/default_ao_tga_79a2e0d0.vtex"
})";

    static constexpr char WireframeTemplate[] =
        R"(<!-- kv3 encoding:text:version{{e21c7f3c-8a33-41c5-9977-a76d3a32aa0d}} format:generic:version{{7412167c-06e9-4698-aff2-e63eb59037e7}} -->
{{
    shader = "tools_wireframe.vfx"
    F_RENDER_BACKFACES = 0
    F_DISABLE_Z_BUFFERING = 1
    F_DISABLE_Z_PREPASS = 1
    F_DISABLE_Z_WRITE = 1
    F_UNLIT = 1
    F_WIREFRAME = 1
    g_DepthBiasAmount = 0.0
    g_LineThickness = 0.25
    g_OverrideColorFactor = 1.0
    g_vOverrideColor = [{}, {}, {}, {}]
}})";

}
