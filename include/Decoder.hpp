// Decoder.hpp
#pragma once

#include <Constants.hpp>
#include <Instruction.hpp>
#include <Memory.hpp>

#include <cstdint>

namespace chip8::core {
class Decoder {
  private:
    Memory &memory;
    uint16_t &pc;

  public:
    Decoder(Memory &memory, uint16_t &pc);

    Instruction fetch();
    Instruction peek();
};
} // namespace chip8::core
