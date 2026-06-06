#include "config.hpp"
#include <fstream>

namespace config {
    Config g_config;
    static std::string s_path = "config.json";

    void Initialize(const std::string& path) {
        s_path = path;
        g_config = Config::Load(path);
    }

    void Save() {
        g_config.Save(s_path);
    }

    Config Config::Load(const std::string& path) {
        std::ifstream f(path);
        if (!f.is_open()) return Config{};

        try {
            nlohmann::json j;
            f >> j;
            return j.get<Config>();
        } catch (...) {
            return Config{};
        }
    }

    bool Config::Save(const std::string& path) const {
        try {
            std::ofstream f(path);
            if (!f.is_open()) return false;

            nlohmann::json j = *this;
            f << j.dump(4);
            return true;
        } catch (...) {
            return false;
        }
    }
}
