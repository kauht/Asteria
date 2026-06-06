#pragma once
#include <safetyhook.hpp>
#include "../../utils/utils.hpp"
#include <cs2.hpp>

namespace hooks {
    void Install();
    void Uninstall();

    namespace handlers {
        void __fastcall hkGeneratePrimitives(void* __this, scenesystem::CSceneAnimatableObject* object, void* a3, scenesystem::c_mesh_primitive_output_buffer* render_buf);
        float* __fastcall hkDrawViewPunch2(__int64 a1, __int64 a2, __int64 a3, float* a4, float* a5, float* a6);
        void* __fastcall hkPostProcessQuery(void* state, void* out, unsigned int key, void* def);
        void __fastcall hkAddEntity(void* sys, void* inst, uint32_t handle);
        void __fastcall hkRemoveEntity(void* sys, void* inst, uint32_t handle);
        bool __fastcall hkCreateMovePrePrediction(void* input, uint32_t slot, char mouse_input);
        void __fastcall hkFrameStageNotify(void* client, int stage);
        void __fastcall hkRunPrediction(void* thisptr, unsigned int reason);
        void* __fastcall hkPostProcessQueryWriter(void* attr_table, uint32_t hash, void* value);
    }

    namespace original {
        inline SafetyHookInline Present;
        inline SafetyHookInline ResizeBuffers;
        inline SafetyHookInline GeneratePrimitives;
        inline SafetyHookInline DrawViewPunch2;
        inline SafetyHookInline PostProcessQuery;
        inline SafetyHookInline AddEntity;
        inline SafetyHookInline RemoveEntity;
        inline SafetyHookInline CreateMovePrePrediction;
        inline SafetyHookInline FrameStageNotify;
        inline SafetyHookInline RunPrediction;
        inline SafetyHookInline PostProcessQueryWriter;
    }

    namespace vtables {
        inline void** pSwapChainVTable;

        inline constexpr int PRESENT = 8;
        inline constexpr int RESIZE_BUFFERS = 13;
    }
}
