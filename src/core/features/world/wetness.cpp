#include "wetness.hpp"
#include "../../../utils/config/config.hpp"
#include "../../../utils/memory/memory.hpp"
#include "../../../utils/modules/modules.hpp"
#include <Patterns/patterns.hpp>
#include <windows.h>
#include <utility>

namespace features::wetness {
    namespace {
        auto get_hashes() {
            static auto GetHash = reinterpret_cast<uint32_t(__fastcall*)(const uint8_t*, int)>(memory::FindPattern(pattern::client::GetMurmur2Hash, modules::client));
            static const uint32_t kWetness = GetHash(reinterpret_cast<const uint8_t*>("RainExposureToSkyWetness"), 0x31415926);
            static const uint32_t kTimer = GetHash(reinterpret_cast<const uint8_t*>("RainExposureLocalTimer"), 0x31415926);
            return std::pair<uint32_t, uint32_t>{kWetness, kTimer};
        }

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

        const auto [kWetness, kTimer] = get_hashes();

        if (key == kWetness) {
            value[0] = value[1] = value[2] = value[3] = cfg.density;
        } else if (key == kTimer) {
            const float timer = static_cast<float>(now - s_start_ms) * cfg.speed / 1000.0f;
            value[0] = value[1] = value[2] = value[3] = timer;
        }
    }
}
