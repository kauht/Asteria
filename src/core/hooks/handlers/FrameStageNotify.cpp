#include "../hooks.hpp"

namespace hooks::handlers {
    void __fastcall hkFrameStageNotify(void* client, int stage) {
        original::FrameStageNotify.fastcall<void>(client, stage);
    }
}
