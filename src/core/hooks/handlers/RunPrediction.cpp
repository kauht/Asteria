#include "../hooks.hpp"

namespace hooks::handlers {
    void __fastcall hkRunPrediction(void* thisptr, unsigned int reason) {
        original::RunPrediction.fastcall<void>(thisptr, reason);
    }
}
