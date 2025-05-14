// Keypad.hpp
#pragma once

#include <Constants.hpp>
#include <array>

namespace chip8::core {
class Keypad {
    std::array<bool, NUM_KEYS> keys = {false};

  public:
    Keypad();

    bool set_state(int key_idx, bool state);
    bool is_pressed(int key_idx) const;
    int get_pressed() const;
    void reset();
};
} // namespace chip8::core
