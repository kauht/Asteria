#pragma once
#include <cstdint>

namespace features::postfx {
    static constexpr std::uint32_t kDoFFocalKey = 0x2ACAB07C;

    bool OnPostProcessQuery(std::uint32_t key, float* out);
}
