// Keypad.hpp
#pragma once

#include <Constants.hpp>
#include <array>
#include <cstdint>

namespace chip8::core {
class Keypad {
    std::array<bool, NUM_KEYS> keys = {false};

  public:
    Keypad();

    bool set_state(int key_idx, bool state);
    bool is_pressed(int key_idx) const;
    uint8_t get_pressed() const;
    void reset();
};
} // namespace chip8::core
