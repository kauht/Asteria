#pragma once
#include <safetyhook.hpp>
#include "../../utils/utils.hpp"
#include <sdk/cs2sdk.hpp>

namespace hooks {
    void Install();
    void Uninstall();

    namespace handlers {
        std::uintptr_t __fastcall OnAddEntity(void* pEntitySystem, sdk::client::C_BaseEntity* pEntity, CHandle<sdk::client::C_BaseEntity> handle);
        std::uintptr_t __fastcall OnRemoveEntity(void* pEntitySystem, sdk::client::C_BaseEntity* pEntity, CHandle<sdk::client::C_BaseEntity> handle);
    }

    namespace original {
        inline SafetyHookInline Present;
        inline SafetyHookInline ResizeBuffers;
        inline SafetyHookInline CreateMove;
        inline SafetyHookInline OnAddEntity;
        inline SafetyHookInline OnRemoveEntity;
        inline SafetyHookInline GeneratePrimitives;
    }

    namespace vtables {
        inline void** pSwapChainVTable;

        enum {
            PRESENT        = 8,
            RESIZE_BUFFERS = 13,
        };
    }
}
