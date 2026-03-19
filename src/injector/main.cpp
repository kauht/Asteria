#include <print>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    std::println("Loading asteria module...");

    for (const auto& file : fs::directory_iterator(".")) {
        if (file.path().filename().string().ends_with(".so")) {
            std::println("Found shared object: {}", file.path().filename().string());
        }
    }


    return 0;
}
