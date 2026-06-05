#include "hooks.hpp"
#include "../../utils/utils.hpp"
#include <safetyhook.hpp>
#include "../../menu/render/render.hpp"
#include "safetyhook/easy.hpp"
namespace hooks {
    void Install() {
        render::GetDevice();
        original::Present = safetyhook::create_inline(vtables::pSwapChainVTable[vtables::PRESENT], render::hkPresent);
        original::ResizeBuffers = safetyhook::create_inline(vtables::pSwapChainVTable[vtables::RESIZE_BUFFERS], render::hkResizeBuffers);

        original::GeneratePrimitives = safetyhook::create_inline(memory::FindPattern(sig::scenesystem::GeneratePrimitives, modules::scenesystem), handlers::hkGeneratePrimitives);
        original::DrawViewPunch2 = safetyhook::create_inline(memory::FindPattern(sig::client::DrawViewPunch2, modules::client), handlers::hkDrawViewPunch2);
        original::PostProcessQuery = safetyhook::create_inline(memory::FindPattern(sig::client::PostProcessQuery, modules::client), handlers::hkPostProcessQuery);
    }

    void Uninstall() {
        render::Shutdown();
        original::Present.reset();
        original::ResizeBuffers.reset();
        original::CreateMove.reset();
        original::GeneratePrimitives.reset();
        original::DrawViewPunch2.reset();
        original::PostProcessQuery.reset();
    }
}
