#include <windows.h>
#include <unordered_map>

namespace input {
    inline std::unordered_map<int, bool> key_states;

    inline void ProcessKey() {
        // Simple temporary key state tracking using GetAsyncKeyState, will use WndProc later where UINT msg is key state and WPARAM wParam is key
        while (true) {
            for (int key = 0; key < 256; ++key) {
                key_states[key] = (GetAsyncKeyState(key) & 0x8000) != 0;
            }
            Sleep(10);
        }
    }

    void Initialize();
    void Shutdown();

    bool KeyDown(int key);
}
