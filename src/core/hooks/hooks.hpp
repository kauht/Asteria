#pragma once
#include <safetyhook.hpp>
#include "../../utils/utils.hpp"
#include <cs2.hpp>

namespace hooks {
    void Install();
    void Uninstall();

    namespace handlers {
        void __fastcall hkGeneratePrimitives(void* __this, scenesystem::CSceneAnimatableObject* object, void* a3, scenesystem::c_mesh_primitive_output_buffer* render_buf);
    }

    namespace original {
        inline SafetyHookInline Present;
        inline SafetyHookInline ResizeBuffers;
        inline SafetyHookInline CreateMove;
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
