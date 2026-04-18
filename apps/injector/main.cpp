#include <print>
#include <windows.h>
#include <TlHelp32.h>

class Injector {
  public:

  Injector(const std::string& name) noexcept : m_process_name(name) {
      if (!set_pid()) {
          std::println("Couldn't find process {}", m_process_name);
          return;
      }
      m_process = OpenProcess(PROCESS_ALL_ACCESS, 0, m_pid);
  }
  ~Injector() {
      if (m_process) {
          CloseHandle(m_process);
      }
  }

  void inject(const std::string& dll_path) {
      auto* addr = VirtualAllocEx(m_process, 0, dll_path.size()+1, MEM_COMMIT, PAGE_EXECUTE_READWRITE);

      if (!WriteProcessMemory(m_process, addr, dll_path.c_str(), dll_path.size()+1, nullptr)) {
          std::println("WriteProcessMemory Failed because: {}", GetLastError());
          return;
      }

      HANDLE a = CreateRemoteThreadEx(m_process, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, addr, 0, 0, 0);

  }

  private:
  bool set_pid() noexcept {
      auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

      PROCESSENTRY32 pe{};
      pe.dwSize = sizeof(PROCESSENTRY32);

      if (Process32First(snapshot, &pe)) {
          do {
              if (m_process_name == pe.szExeFile) {
                  m_pid = pe.th32ProcessID;
                  CloseHandle(snapshot);
                  return true;
              }
          } while(Process32Next(snapshot, &pe));
      }
      CloseHandle(snapshot);
      return false;

  }
  std::string m_process_name;
  DWORD m_pid;
  HANDLE m_process;

};


auto main() -> int {
    Injector injector("cs2.exe");
    injector.inject("C:\\Users\\macin\\Desktop\\Asteria\\bin\\release\\asteria.dll");
    // injector.inject("C:\\Users\\macin\\Desktop\\Asteria\\bin\\release\\asteria.dll");
}
