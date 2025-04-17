// CPU.hpp
#pragma once

#include <Instruction.hpp>
#include <array>
#include <cstdint>

namespace chip8::cpu {
class CPU {
    std::array<uint8_t, 4096> &memory;
    uint16_t &pc;
    uint16_t &I;
    std::array<uint8_t, 16> &V;
    std::array<uint16_t, 16> &stack;
    uint8_t &sp;

  public:
    CPU(std::array<uint8_t, 4096> &memory, uint16_t &pc, uint16_t &I,
        std::array<uint8_t, 16> &V, std::array<uint16_t, 16> &stack,
        uint8_t &sp);
    bool execute(instruction::Instruction instruction, int8_t key);
};
} // namespace chip8::cpu
