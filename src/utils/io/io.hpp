#pragma once
#include <windows.h>
#include <string>

#define DEBUG

namespace io {
    void Initialize();
    void Shutdown();

    void print(const char* fmt, ...);
    void println(const char* fmt, ...);

    // Template wrappers for compatibility if needed, but using variadic for now
}
