#pragma once
#include <windows.h>
#include <unordered_map>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace config {
    void Initialize(const std::string& path = "config.json");
    void Shutdown();

    struct Keybind {
        int key = 0;        // VK_ key code
        bool enabled = true;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Keybind, key, enabled)
    };

    struct Config {
        float version = 1.0;

        std::unordered_map<std::string, Keybind> keybinds = {
            {"menu_toggle", {VK_INSERT, true}},
        };

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Config, version, keybinds)
        Config Load(const std::string& path = "config.json");
        bool Save(const std::string& path = "config.json") const;
    };

    extern Config g_config;
}
