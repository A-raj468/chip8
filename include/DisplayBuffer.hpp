// DisplayBuffer.hpp
#pragma once

#include <Constants.hpp>
#include <array>
#include <cstdint>

namespace chip8::core {
class DisplayBuffer {
    std::array<std::array<uint8_t, DISPLAY_COLS>, DISPLAY_ROWS> display = {
        {{0}}};

  public:
    DisplayBuffer();

    void clear();
    bool set_pixel(uint8_t x, uint8_t y, uint8_t val);
    bool get_pixel(uint8_t x, uint8_t y) const;
    const std::array<std::array<uint8_t, DISPLAY_COLS>, DISPLAY_ROWS> &
    data() const;
};
} // namespace chip8::core
