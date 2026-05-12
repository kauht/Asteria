#pragma once
#include <windows.h>
#include <string>
#include <source_location>

#define DEBUG

namespace io {
    void Initialize();
    void Shutdown();

    struct LogLine {
        const char* fmt;
        std::source_location loc;
        LogLine(const char* fmt, std::source_location loc = std::source_location::current())
            : fmt(fmt), loc(loc) {}
    };

    void print(LogLine line, ...);
    void println(LogLine line, ...);
}
