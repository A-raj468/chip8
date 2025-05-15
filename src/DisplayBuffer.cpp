#include <Constants.hpp>
#include <DisplayBuffer.hpp>

#include <cstdint>

using namespace chip8::core;

DisplayBuffer::DisplayBuffer() {}

void DisplayBuffer::clear() {
    for (auto &row : display) {
        row.fill(0);
    }
}

bool DisplayBuffer::set_pixel(uint8_t x, uint8_t y, uint8_t val) {
    if (x >= DISPLAY_COLS || y >= DISPLAY_ROWS) {
        return false;
    }
    display[y][x] = val;
    return true;
}

uint8_t DisplayBuffer::get_pixel(uint8_t x, uint8_t y) const {
    if (x >= DISPLAY_COLS || y >= DISPLAY_ROWS) {
        return 2;
    }
    return display[y][x];
}

const std::array<std::array<uint8_t, DISPLAY_COLS>, DISPLAY_ROWS> &
DisplayBuffer::data() const {
    return display;
}
