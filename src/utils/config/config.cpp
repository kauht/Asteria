
#include "config.hpp"
#include <fstream>

namespace config {
    Config g_config;

    void Initialize(const std::string& path) {
        g_config.Load(path);
    }

    void Shutdown() {

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
