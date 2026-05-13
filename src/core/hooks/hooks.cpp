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

        original::OnAddEntity = safetyhook::create_inline(memory::FindPattern(sdk::sigs::client::OnAddEntity, modules::client), render::hkPresent);
        original::OnRemoveEntity = safetyhook::create_inline(memory::FindPattern(sdk::sigs::client::OnRemoveEntity, modules::client), render::hkPresent);
    }

    void Uninstall() {
        render::Shutdown();
        original::Present       = {};
        original::ResizeBuffers = {};
        original::CreateMove = {};
        original::OnAddEntity   = {};
        original::OnRemoveEntity = {};
    }
}
