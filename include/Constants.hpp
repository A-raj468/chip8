// Constants.hpp
#pragma once

#include <cstdint>

constexpr uint16_t MEM_SIZE = 4096;
constexpr uint16_t ROM_START = 0x200;
constexpr uint8_t DISPLAY_ROWS = 32;
constexpr uint8_t DISPLAY_COLS = 64;
constexpr uint8_t NUM_KEYS = 16;
constexpr uint8_t REG_SIZE = 16;
constexpr uint8_t STACK_SIZE = 16;

constexpr int32_t SCALE = 10;
constexpr uint32_t WINDOW_HEIGHT = DISPLAY_ROWS * SCALE;
constexpr uint32_t WINDOW_WIDTH = DISPLAY_COLS * SCALE;
