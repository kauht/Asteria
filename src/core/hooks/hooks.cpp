#include "hooks.hpp"
#include "../../utils/utils.hpp"
#include <safetyhook.hpp>
#include "../../menu/render/render.hpp"
#include "safetyhook/easy.hpp"
#include <signatures/signatures.hpp>
#include "handlers/test.hpp"

namespace hooks {
    void Install() {
        render::GetDevice();
        original::Present = safetyhook::create_inline(vtables::pSwapChainVTable[vtables::PRESENT], render::hkPresent);
        original::ResizeBuffers = safetyhook::create_inline(vtables::pSwapChainVTable[vtables::RESIZE_BUFFERS], render::hkResizeBuffers);

        original::OnAddEntity = safetyhook::create_inline(memory::FindPattern(sdk::sigs::client::OnAddEntity, modules::client), handlers::OnAddEntity);
        original::OnRemoveEntity = safetyhook::create_inline(memory::FindPattern(sdk::sigs::client::OnRemoveEntity, modules::client), handlers::OnRemoveEntity);
        original::GeneratePrimitives = safetyhook::create_inline(memory::FindPattern(sdk::sigs::scenesystem::GeneratePrimitives, modules::scenesystem), handlers::hkGeneratePrimitives);

        test::Install();
    }

    void Uninstall() {
        render::Shutdown();
        original::Present.reset();
        original::ResizeBuffers.reset();
        original::CreateMove.reset();
        original::OnAddEntity.reset();
        original::OnRemoveEntity.reset();
        original::GeneratePrimitives.reset();
        test::Uninstall();
    }
}
