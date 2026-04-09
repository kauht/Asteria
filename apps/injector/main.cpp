#include "nt.h"
#include <TlHelp32.h>
#include <print>
#include <string>

class Injector {
  public:
    Injector(std::string name) : process_name(name) {}
    ~Injector() {
        if (process_handle) {
            NtClose(process_handle);
        }
    }

    void inject(std::wstring module_path) {
        set_pid();
        std::println("{} PID: {}", process_name, process_id);
        if (!process_id) {
            std::println("Process not found!");
            return;
        }
        if (module_path.empty()) {
            std::println("Module path is empty!");
            return;
        }
        // process_handle = OpenProcess(PROCESS_ALL_ACCESS, 0, process_id);
        CLIENT_ID id{};
        id.UniqueProcess = reinterpret_cast<HANDLE>(process_id);
        OBJECT_ATTRIBUTES obj_attr{};
        obj_attr.Length = sizeof(OBJECT_ATTRIBUTES);
        long error = NtOpenProcess(&process_handle, PROCESS_ALL_ACCESS, &obj_attr, &id);
        std::println("{}", error);
        // LPVOID path_ptr = VirtualAllocEx(process_handle, 0, module_path.size(), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
        LPVOID path_ptr{};
        SIZE_T size = module_path.size();
        if (!size) {
            std::println("Module path is empty!");
        }
        long status = NtAllocateVirtualMemory(process_handle, &path_ptr, 0, &size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
        if (status != STATUS_SUCCESS) {
            std::println("Failed to allocate memory in target process!\n Error: {}", status);
        }
        status = NtWriteVirtualMemory(process_handle, path_ptr, module_path.data(), module_path.size(), 0);
        if (status != STATUS_SUCCESS) {
            std::println("Failed to write to target process memory!\n Error: {}", status);
        }

        // HANDLE thread = CreateRemoteThreadEx(process_handle, 0, 0,
        // (LPTHREAD_START_ROUTINE)LoadLibraryA, path_ptr, 0, 0, 0);

        OBJECT_ATTRIBUTES thread_obj_attr{};
        thread_obj_attr.Length = sizeof(OBJECT_ATTRIBUTES);
        HANDLE thread{};
        status = NtCreateThreadEx(&thread, THREAD_ALL_ACCESS, &thread_obj_attr, process_handle, (PUSER_THREAD_START_ROUTINE) load_lib, path_ptr, 0, 0, 0, 0, 0);
        if (status != STATUS_SUCCESS) {
            std::println("Failed to create remote thread!\n Error: {}", status);
        }

        LdrUnloadDll(thread);
        if (thread) {
            NtWaitForSingleObject(thread, 0, PLARGE_INTEGER(MAXLONG));
            NtClose(thread);
        }
        NtFreeVirtualMemory(process_handle, &path_ptr, 0, MEM_RELEASE);

    }

  private:
    void set_pid() {
        HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        PROCESSENTRY32 pe{};
        pe.dwSize = sizeof(PROCESSENTRY32);
        if (Process32First(hsnap, &pe)) {
            do {
                if (process_name.compare(pe.szExeFile) == 0) {
                    process_id = pe.th32ProcessID;
                    break;
                }
            } while (Process32Next(hsnap, &pe));
        }
    }
    std::string process_name{};
    DWORD process_id{};
    HANDLE process_handle{};
};

auto main() -> int {
    Injector injector("Zed.exe");
    injector.inject(L"C:\\Users\\0\\Downloads\\msg.dll");

    return 0;
}
