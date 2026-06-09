#include "../hooks.hpp"
#include "../../features/bhop/bhop.hpp"

namespace hooks::handlers {
    void __fastcall hkCreateMovePrePrediction( void* pThis, int nSlot, void* pCmd ) {
        features::bhop::Bhop(pCmd);
        original::CreateMovePrePrediction.fastcall<void>( pThis, nSlot, pCmd );
    }
}
