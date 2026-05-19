#pragma once
#include "../hooks.hpp"
#include "safetyhook.hpp"
#include "safetyhook/easy.hpp"
#include "../../../globals.hpp"

namespace test {

    namespace original {
        inline SafetyHookInline Test;
    }

    void __fastcall hkTest(__int64 a1, __int64 *a2, __int64 a3, __int64 a4, __int64 a5) {

        if (globals::bTest) original::Test.fastcall<uintptr_t>(a1, a2, a3, a4, a5);

        return;
    }

    void Install() {
        original::Test = safetyhook::create_inline(memory::FindPattern("48 8B C4 4C 89 48 ? 4C 89 40 ? 48 89 48 ? 55 53", modules::scenesystem), hkTest);
    }
    void Uninstall() {
        original::Test.reset();
    }

}
