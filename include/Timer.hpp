// Timer.hpp
#pragma once

#include <cstdint>

namespace chip8::core {
class Timer {
    uint8_t delay_timer = 0;
    uint8_t sound_timer = 0;

  public:
    Timer();

    uint8_t get_delay();
    uint8_t get_sound();
    void set_delay(uint8_t val);
    void set_sound(uint8_t val);
    bool tick();
};

} // namespace chip8::core
