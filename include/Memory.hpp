// Memory.hpp
#pragma once

#include <Constants.hpp>
#include <array>
#include <cstdint>

namespace chip8::core {
class Memory {
    std::array<uint8_t, MEM_SIZE> memory = {0};

  public:
    Memory();

    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t val);
};
} // namespace chip8::core
