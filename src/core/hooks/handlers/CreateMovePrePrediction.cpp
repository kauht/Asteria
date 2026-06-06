#include "../hooks.hpp"

namespace hooks::handlers {
    bool __fastcall hkCreateMovePrePrediction(void* input, uint32_t slot, char mouse_input) {
        return original::CreateMovePrePrediction.fastcall<bool>(input, slot, mouse_input);
    }
}
