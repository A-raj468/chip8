// Timer.hpp
#pragma once

#include <cstdint>

namespace chip8::core {
class Timer {
    uint8_t delay_timer = 0;
    uint8_t sound_timer = 0;

  public:
    Timer();

    uint8_t get();
    bool set(uint8_t val);
    bool tick();
};

} // namespace chip8::core
