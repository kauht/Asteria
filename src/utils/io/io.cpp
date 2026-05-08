#include "io.hpp"
#include "io.hpp"
#include <cstring>

void io::Initialize() {
    #ifdef DEBUG
    AllocConsole();
    FILE* f{};
    freopen_s(&f, "CONOUT$", "w", stdout);
    SetConsoleTitleA("Asteria Debug");
    #endif

    hLogFile = CreateFileA("asteria.log", GENERIC_WRITE, FILE_SHARE_READ, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_WRITE_THROUGH, nullptr);
}

void io::Shutdown() {
    if (hLogFile) CloseHandle(hLogFile);
    #ifdef DEBUG
    FreeConsole();
    #endif
}
