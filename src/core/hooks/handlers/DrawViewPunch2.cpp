#include "../hooks.hpp"

namespace hooks::handlers {
    float* __fastcall hkDrawViewPunch2(__int64 a1, __int64 a2, __int64 a3, float* a4, float* a5, float* a6) {
        return original::DrawViewPunch2.fastcall<float*>(a1, a2, a3, a4, a5, a6);
    }
}
