#pragma once
#include <windows.h>
#include <unordered_map>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace config {
    void Initialize(const std::string& path = "config.json");
    void Shutdown();


    struct ChamsColor {
        float r = 0.0f;
        float g = 0.0f;
        float b = 0.0f;
        float a = 1.0f;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(ChamsColor, r, g, b, a)
    };

    struct Chams {
        bool team_vis_enabled = true;
        bool team_occ_enabled = true;
        bool enemy_vis_enabled = true;
        bool enemy_occ_enabled = true;
        bool weapon_chams_enabled = true;
        bool hand_chams_enabled = true;
        ChamsColor enemy_vis_color = { 1.0f, 0.0f, 0.0f, 1.0f };   // red
        ChamsColor enemy_occ_color = { 0.5f, 0.0f, 0.0f, 0.6f };   // dark red
        ChamsColor team_vis_color = { 0.0f, 0.4f, 1.0f, 1.0f };    // blue
        ChamsColor team_occ_color = { 0.6f, 0.0f, 1.0f, 0.6f };    // purple
        ChamsColor viewmodel_color = { 1.0f, 0.5f, 0.0f, 1.0f };   // orange
        int enemy_vis_material = 0;
        int enemy_occ_material = 0;
        int team_vis_material = 0;
        int team_occ_material = 0;
        int viewmodel_material = 0;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Chams, team_vis_enabled, team_occ_enabled, enemy_vis_enabled, enemy_occ_enabled, weapon_chams_enabled, hand_chams_enabled, enemy_vis_color, enemy_occ_color, team_vis_color, team_occ_color, viewmodel_color, enemy_vis_material, enemy_occ_material, team_vis_material, team_occ_material, viewmodel_material)
    };

    struct Keybind {
        int key = 0;        // VK_ key code
        bool enabled = true;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Keybind, key, enabled)
    };

    struct Config {
        float version = 1.0;

        std::unordered_map<std::string, Keybind> keybinds = {
            {"toggle_menu", {VK_INSERT, true}},
        };

        Chams chams;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Config, version, keybinds, chams)
        Config Load(const std::string& path = "config.json");
        bool Save(const std::string& path = "config.json") const;
    };

    extern Config g_config;
}
