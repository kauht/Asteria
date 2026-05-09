#include <Windows.h>
#include <print>

#include "hooks/d3d11_hook.hpp"

namespace globals
{
    HMODULE module = nullptr;
}

DWORD WINAPI entry(LPVOID)
{
    // Allocate console for debugging
    AllocConsole();
    FILE* f{};
    freopen_s(&f, "CONOUT$", "w", stdout);
    SetConsoleTitleA("p2c Debug"); 
    
    std::println("[+] DLL Injected");
    std::println("[+] Initializing D3D11 hooks...");
    
    // Initialize D3D11 hooks
    if (hooks::d3d11::init())
    {
        std::println("[+] D3D11 hooks initialized successfully");
    }
    else
    {
        std::println("[-] Failed to initialize D3D11 hooks");
    }
    
    // Keep thread alive
    while (true)
    {
        if (GetAsyncKeyState(VK_DELETE) & 1)
        {
            std::println("[+] Unloading...");
            break;
        }
        Sleep(100);
    }
    
    // Cleanup
    hooks::d3d11::shutdown();
    
    if (f) fclose(f);
    FreeConsole();
    
    std::println("Exiting...");
    std::println("You can now close this window.");
    
    FreeLibraryAndExitThread(globals::module, 0);
    return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinst, DWORD reason, LPVOID)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hinst);
        globals::module = hinst;
        CloseHandle(CreateThread(nullptr, 0, entry, nullptr, 0, nullptr));
    }
    return TRUE;
}

