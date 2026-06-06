#pragma once
#include <cstdint>

namespace features::postfx {
    static constexpr std::uint32_t kDoFFocalKey    = 0x2ACAB07Cu;
    static constexpr std::uint32_t kDofApertureKey = 0xB0691300u;

    bool OnPostProcessQuery(std::uint32_t key, float* out);
}
