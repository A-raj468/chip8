// Decoder.hpp
#pragma once

#include <Instruction.hpp>
#include <array>
#include <cstdint>

namespace chip8::decoder {
class Decoder {
  private:
    std::array<uint8_t, 4096> &memory;
    uint16_t &pc;

  public:
    Decoder(std::array<uint8_t, 4096> &memory, uint16_t &pc);
    instruction::Instruction fetch();
    instruction::Instruction peek();
};
} // namespace chip8::decoder
