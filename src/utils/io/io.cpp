#include "io.hpp"
#include <chrono>

namespace io {
    HANDLE hLogFile = nullptr;

    static std::string timestamp() {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        std::tm tm{};
        localtime_s(&tm, &time);
        return std::format("{:02}:{:02}:{:02}", tm.tm_hour, tm.tm_min, tm.tm_sec);
    }

    static const char* basename(const char* path) {
        const char* s = path;
        for (const char* p = path; *p; ++p)
            if (*p == '/' || *p == '\\') s = p + 1;
        return s;
    }

    namespace detail {
        void write(std::string_view msg, const std::source_location& loc) {
            auto out = std::format("[{}] [{}:{}] {}", timestamp(), basename(loc.file_name()), loc.line(), msg);
#ifdef DEBUG
            printf("%s", out.c_str());
#endif
            if (hLogFile)
                WriteFile(hLogFile, out.data(), (DWORD)out.size(), nullptr, nullptr);
        }

        void writeln(std::string_view msg, const std::source_location& loc) {
            auto out = std::format("[{}] [{}:{}] {}\n", timestamp(), basename(loc.file_name()), loc.line(), msg);
#ifdef DEBUG
            printf("%s", out.c_str());
#endif
            if (hLogFile)
                WriteFile(hLogFile, out.data(), (DWORD)out.size(), nullptr, nullptr);
        }
    }

    void Initialize() {
#ifdef DEBUG
        AllocConsole();
        FILE* f{};
        freopen_s(&f, "CONOUT$", "w", stdout);
        SetConsoleTitleA("Asteria Debug");
#endif
        hLogFile = CreateFileA("asteria.log", GENERIC_WRITE, FILE_SHARE_READ, nullptr,
            CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_WRITE_THROUGH, nullptr);
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
}
