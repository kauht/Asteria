#pragma once
#include <windows.h>
#include <format>
#include <source_location>
#include <string_view>

namespace io {
    void Initialize();
    void Shutdown();

    namespace detail {
        void write  (std::string_view msg, const std::source_location& loc);
        void writeln(std::string_view msg, const std::source_location& loc);
    }

    struct LogLine {
        std::string_view     fmt;
        std::source_location loc;
        LogLine(const char* f, std::source_location l = std::source_location::current())
            : fmt(f), loc(l) {}
        LogLine(std::string_view f, std::source_location l = std::source_location::current())
            : fmt(f), loc(l) {}
    };

    template<typename... Args>
    void print(LogLine line, Args&&... args) {
        detail::write(std::vformat(line.fmt, std::make_format_args(args...)), line.loc);
    }

    template<typename... Args>
    void println(LogLine line, Args&&... args) {
        detail::writeln(std::vformat(line.fmt, std::make_format_args(args...)), line.loc);
    }
}
