#include "hooks.hpp"
#include "../../utils/utils.hpp"
#include <safetyhook.hpp>
#include "../../menu/render/render.hpp"
#include "safetyhook/easy.hpp"
#include <signatures/signatures.hpp>
namespace hooks {
    void Install() {
        render::GetDevice();
        original::Present = safetyhook::create_inline(vtables::pSwapChainVTable[vtables::PRESENT], render::hkPresent);
        original::ResizeBuffers = safetyhook::create_inline(vtables::pSwapChainVTable[vtables::RESIZE_BUFFERS], render::hkResizeBuffers);

        original::GeneratePrimitives = safetyhook::create_inline(memory::FindPattern(sdk::sigs::scenesystem::GeneratePrimitives, modules::scenesystem), handlers::hkGeneratePrimitives);
    }

    void Uninstall() {
        render::Shutdown();
        original::Present.reset();
        original::ResizeBuffers.reset();
        original::CreateMove.reset();
        original::GeneratePrimitives.reset();
    }
}
