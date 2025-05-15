#include <Constants.hpp>
#include <Keypad.hpp>

using namespace chip8::core;

Keypad::Keypad() {}

bool Keypad::set_state(int key_idx, bool state) {
    if (key_idx >= NUM_KEYS) {
        return false;
    }
    keys[key_idx] = state;
    return true;
}

bool Keypad::is_pressed(int key_idx) const {
    if (key_idx >= NUM_KEYS) {
        return false;
    }
    return keys[key_idx];
}

uint8_t Keypad::get_pressed() const {
    int i = 0;
    for (i = 0; i < NUM_KEYS; i++) {
        if (keys[i]) {
            break;
        }
    }
    return i;
}

void Keypad::reset() {
    for (int i = 0; i < NUM_KEYS; i++) {
        keys[NUM_KEYS] = false;
    }
}
