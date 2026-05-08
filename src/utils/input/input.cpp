#include "input.hpp"
#include <thread>

void input::Initialize() {
    std::thread(ProcessKey).detach();
}

void input::Shutdown() {
    // No cleanup needed until WndProc is implementedd
}

bool input::KeyDown(int key) {
    return key_states[key];
}
