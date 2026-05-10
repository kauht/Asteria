#pragma once
#include <safetyhook.hpp>
#include "../../utils/utils.hpp"

namespace hooks {
    void Install();
    void Uninstall();

    namespace handlers {
        void* __fastcall OnAddEntity(void* pEntitySystem, void* pEntity, uint32_t handle);
        void* __fastcall OnRemoveEntity(void* pEntitySystem, void* pEntity, uint32_t handle);
    }

    namespace original {
        inline SafetyHookInline GeneratePrimitives;
        inline SafetyHookInline CreateMoveInner;
        inline SafetyHookInline Prediction;
        inline SafetyHookInline CreateMove;
        inline SafetyHookInline OnAddEntity;
        inline SafetyHookInline OnRemoveEntity;
    }

}
