#include "io.hpp"
#include <cstdio>
#include <cstdarg>
#include <chrono>

namespace io {
    HANDLE hLogFile = nullptr;

    static std::string timestamp() {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        std::tm tm{};
        localtime_s(&tm, &time);
        char buf[32];
        sprintf_s(buf, "%02d:%02d:%02d", tm.tm_hour, tm.tm_min, tm.tm_sec);
        return std::string(buf);
    }

    void Initialize() {
        #ifdef DEBUG
        AllocConsole();
        FILE* f{};
        freopen_s(&f, "CONOUT$", "w", stdout);
        SetConsoleTitleA("Asteria Debug");
        #endif

        hLogFile = CreateFileA("asteria.log", GENERIC_WRITE, FILE_SHARE_READ, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_WRITE_THROUGH, nullptr);
        io::println("--- Asteria Log Initialized ---");
    }

    void Shutdown() {
        if (hLogFile) {
            CloseHandle(hLogFile);
            hLogFile = nullptr;
        }
        #ifdef DEBUG
        FreeConsole();
        #endif
    }

    void print(const char* fmt, ...) {
        char buf[1024];
        va_list args;
        va_start(args, fmt);
        vsprintf_s(buf, fmt, args);
        va_end(args);

        std::string message = "[" + timestamp() + "] " + buf;
        
        #ifdef DEBUG
        printf("%s", message.c_str());
        #endif

        if (hLogFile)
            WriteFile(hLogFile, message.c_str(), (DWORD)message.size(), nullptr, nullptr);
    }

    void println(const char* fmt, ...) {
        char buf[1024];
        va_list args;
        va_start(args, fmt);
        vsprintf_s(buf, fmt, args);
        va_end(args);

        std::string message = "[" + timestamp() + "] " + buf + "\n";
        
        #ifdef DEBUG
        printf("%s", message.c_str());
        #endif

        if (hLogFile)
            WriteFile(hLogFile, message.c_str(), (DWORD)message.size(), nullptr, nullptr);
    }
}
