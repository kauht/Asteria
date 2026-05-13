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

    static const char* basename(const char* path) {
        const char* s = path;
        for (const char* p = path; *p; ++p)
            if (*p == '/' || *p == '\\') s = p + 1;
        return s;
    }

    void print(LogLine line, ...) {
        char msg[1024];
        va_list args;
        va_start(args, line);
        vsprintf_s(msg, line.fmt, args);
        va_end(args);

        char out[1280];
        sprintf_s(out, "[%s] [%s:%d] %s",
            timestamp().c_str(),
            basename(line.loc.file_name()),
            line.loc.line(),
            msg);

#ifdef DEBUG
        printf("%s", out);
#endif
        if (hLogFile)
            WriteFile(hLogFile, out, (DWORD)strlen(out), nullptr, nullptr);
    }

    void println(LogLine line, ...) {
        char msg[1024];
        va_list args;
        va_start(args, line);
        vsprintf_s(msg, line.fmt, args);
        va_end(args);

        char out[1280];
        sprintf_s(out, "[%s] [%s:%d] %s\n",
            timestamp().c_str(),
            basename(line.loc.file_name()),
            line.loc.line(),
            msg);

#ifdef DEBUG
        printf("%s", out);
#endif
        if (hLogFile)
            WriteFile(hLogFile, out, (DWORD)strlen(out), nullptr, nullptr);
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
