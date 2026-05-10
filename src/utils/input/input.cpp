#include "input.hpp"
#include <thread>
#include "../io/io.hpp"

void input::Initialize() {
    std::thread(ProcessKey).detach();
}

void input::Shutdown() {
    // No cleanup needed until WndProc is implemented
    running = false;
}

bool input::KeyDown(int key) {
    return key_states[key];
}

void input::ProcessKey() {
    // Simple temporary key state tracking using GetAsyncKeyState, will use WndProc later where UINT msg is key state and WPARAM wParam is key
    while (running) {
        for (int key = 0; key < 256; ++key) {
            bool down = (GetAsyncKeyState(key) & 0x8000) != 0;
            if (down != key_states[key]) {
                key_states[key] = down;
                // if (down && (key == VK_SPACE || key == VK_DELETE))
                //     io::println("[input] Key %d state: %s", key, down ? "PRESSED" : "RELEASED");
            }
        }
        Sleep(10);
    }
}
