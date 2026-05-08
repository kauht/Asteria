#pragma once
#include <windows.h>
#include <fstream>
#include <format>
#include <print>
#include <chrono>

#define DEBUG

namespace io {
    inline HANDLE hLogFile{};

    inline std::string timestamp() {
        auto now  = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        std::tm tm{};
        localtime_s(&tm, &time);
        return std::format("{:02}:{:02}:{:02}", tm.tm_hour, tm.tm_min, tm.tm_sec);
    }

    void Initialize();
    void Shutdown();

    template<typename... Args>
    void print(std::format_string<Args...> fmt, Args&&... args) {
        std::string message = std::format("[{}] {}", timestamp(), std::format(fmt, std::forward<Args>(args)...));
        #ifdef DEBUG
        std::print("{}\n", message);
        #endif

        message += "\n";
        WriteFile(hLogFile, message.c_str(), static_cast<DWORD>(message.size()), nullptr, nullptr);
    }

    template<typename... Args>
    void println(std::format_string<Args...> fmt, Args&&... args) {
        io::print(fmt, std::forward<Args>(args)...);
        const char* newline = "\n";
        WriteFile(hLogFile, newline, 1, nullptr, nullptr);
        #ifdef DEBUG
        std::print("\n");
        #endif
    }
}
