#include "input.hpp"
#include <thread>
#include "../io/io.hpp"

bool input::KeyDown(int key) {
    return key_states[key];
}

void input::ProcessKey(UINT msg, WPARAM wParam) {
    if (msg == WM_KEYDOWN) {
        key_states[wParam] = true;
    } else {
        key_states[wParam] = false;
    }

}
