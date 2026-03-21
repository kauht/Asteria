#include <dlfcn.h>
#include <print>
#include <filesystem>
#include <thread>
#include <chrono>

namespace fs = std::filesystem;

int main() {
    std::println("Loading asteria module...");
    std::string name{};

    for (const auto& file : fs::directory_iterator(".")) {
        if (file.path().filename().string().ends_with(".so")) {
            name = file.path().filename().string();
            std::println("Found shared object: {}", name);
        }
    }

    if (name.empty()) {
        std::println("No shared object found.");
        return 1;
    }

    std::println("Loading module: {}", name);
    void* handle = dlopen(("./" + name).c_str(), RTLD_LAZY);
    if (!handle) {
        std::println("Failed to load module: {}", dlerror());
        return 1;
    }

    std::println("Module loaded successfully.");
    while (handle) {
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }
    dlclose(handle);

    return 0;
}
