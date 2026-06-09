#include "hooks.hpp"
#include "../../utils/utils.hpp"
#include <safetyhook.hpp>
#include "../../menu/render/render.hpp"
#include "safetyhook/easy.hpp"

namespace hooks {
    void Install() {
        render::GetDevice();
        original::Present       = safetyhook::create_inline(vtables::pSwapChainVTable[vtables::PRESENT],        render::hkPresent);
        original::ResizeBuffers = safetyhook::create_inline(vtables::pSwapChainVTable[vtables::RESIZE_BUFFERS], render::hkResizeBuffers);

        original::GeneratePrimitives      = safetyhook::create_inline(memory::FindPattern(pattern::scenesystem::GeneratePrimitives,  modules::scenesystem), handlers::hkGeneratePrimitives);
        original::DrawViewPunch2          = safetyhook::create_inline(memory::FindPattern(pattern::client::DrawViewPunch2,           modules::client),      handlers::hkDrawViewPunch2);
        original::PostProcessQuery        = safetyhook::create_inline(memory::FindPattern(pattern::client::PostProcessQuery,         modules::client),      handlers::hkPostProcessQuery);
        original::AddEntity               = safetyhook::create_inline(memory::FindPattern(pattern::client::AddEntity,               modules::client),      handlers::hkAddEntity);
        original::RemoveEntity            = safetyhook::create_inline(memory::FindPattern(pattern::client::RemoveEntity,            modules::client),      handlers::hkRemoveEntity);
        original::CreateMovePrePrediction = safetyhook::create_inline(memory::FindPattern(pattern::client::CreateMovePrePrediction, modules::client), handlers::hkCreateMovePrePrediction);
        original::FrameStageNotify        = safetyhook::create_inline(memory::FindPattern(pattern::client::FrameStageNotify,        modules::client),      handlers::hkFrameStageNotify);
        original::RunPrediction           = safetyhook::create_inline(memory::FindPattern(pattern::engine2::RunPrediction,          modules::engine2),     handlers::hkRunPrediction);
        original::PostProcessQueryWriter  = safetyhook::create_inline(memory::FindPattern(pattern::client::PostProcessQueryWriter,  modules::client),      handlers::hkPostProcessQueryWriter);
    }

    void Uninstall() {
        render::Shutdown();
        original::Present.reset();
        original::ResizeBuffers.reset();
        original::GeneratePrimitives.reset();
        original::DrawViewPunch2.reset();
        original::PostProcessQuery.reset();
        original::AddEntity.reset();
        original::RemoveEntity.reset();
        original::CreateMovePrePrediction.reset();
        original::FrameStageNotify.reset();
        original::RunPrediction.reset();
        original::PostProcessQueryWriter.reset();
    }
}
