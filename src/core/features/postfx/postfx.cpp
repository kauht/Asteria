#include "postfx.hpp"
#include "../../../utils/config/config.hpp"

namespace features::postfx {
    bool OnPostProcessQuery(std::uint32_t key, float* out) {
        // Depth of Field
        if (key == kDoFFocalKey) {
            const auto& dof = config::g_config.dof;
            if (!dof.enabled) return false;
            out[0] = dof.near_blurry;
            out[1] = dof.near_crisp;
            out[2] = dof.far_crisp;
            out[3] = dof.far_blurry;
            return true;
        }
        return false;
    }
}
