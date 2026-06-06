#include "wetness.hpp"
#include "../../../utils/murmur2.hpp"
#include "../../../utils/config/config.hpp"
#include <windows.h>

namespace features::wetness {
    namespace {
        constexpr uint32_t kWetness = murmur2::hash_a1_const("RainExposureToSkyWetness", murmur2::kSeed);
        constexpr uint32_t kTimer   = murmur2::hash_a1_const("RainExposureLocalTimer",   murmur2::kSeed);

        ULONGLONG s_start_ms = 0;
    }

    void OnPostProcessQueryWriter(uint32_t key, float* value) {
        const auto& cfg = config::g_config.wetness;

        if (!cfg.enabled) {
            s_start_ms = 0;
            return;
        }

        if (!value) return;

        const ULONGLONG now = GetTickCount64();
        if (s_start_ms == 0) s_start_ms = now;

        if (key == kWetness) {
            value[0] = value[1] = value[2] = value[3] = cfg.density;
        } else if (key == kTimer) {
            const float timer = static_cast<float>(now - s_start_ms) * cfg.speed / 1000.0f;
            value[0] = value[1] = value[2] = value[3] = timer;
        }
    }
}
