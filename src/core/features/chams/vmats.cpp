#include "vmats.hpp"
#include "chams.hpp"
#include <array>
#include <format>

namespace features::chams {

    void* MakeMaterial(const char* name, const char* kv3_text) {
        std::array<uint8_t, 0x400> buf{};
        kv3_id_t id{ "generic", k_kv3Unk0, k_kv3Unk1 };

        if (!LoadKV3(buf.data() + 0x100, nullptr, kv3_text, &id, nullptr, 0)) return nullptr;

        void* handle{};
        CreateMaterial(material_system, &handle, name, buf.data() + 0x100, nullptr, 1);

        if (handle) return *reinterpret_cast<void**>(handle);
        return nullptr;
    }

    void* MakeWireMaterial(const char* name, float r, float g, float b, float a) {
        auto kv3 = std::format(VMat::WireframeTemplate, r, g, b, a);
        return MakeMaterial(name, kv3.c_str());
    }

}
