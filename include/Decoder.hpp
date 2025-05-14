// Decoder.hpp
#pragma once

#include <Constants.hpp>
#include <Instruction.hpp>
#include <array>
#include <cstdint>

namespace chip8::core {
class Decoder {
  private:
    std::array<uint8_t, MEM_SIZE> &memory;
    uint16_t &pc;

  public:
    Decoder(std::array<uint8_t, MEM_SIZE> &memory, uint16_t &pc);

    Instruction fetch();
    Instruction peek();
};
} // namespace chip8::core
