// CPU.hpp
#pragma once

#include <Instruction.hpp>
#include <array>
#include <atomic>
#include <cstdint>

namespace chip8::cpu {
class CPU {
    std::array<uint8_t, 4096> &memory;
    uint16_t &pc;
    uint16_t &I;
    std::array<uint8_t, 16> &V;
    std::array<uint16_t, 16> stack = {0};
    uint8_t sp = 0;
    std::array<std::array<uint8_t, 64>, 32> &display;
    uint8_t &delay_timer;
    uint8_t &sound_timer;

  public:
    CPU(std::array<uint8_t, 4096> &memory, uint16_t &pc, uint16_t &I,
        std::array<uint8_t, 16> &V,
        std::array<std::array<uint8_t, 64>, 32> &display, uint8_t &delay_timer,
        uint8_t &sound_timer);

    bool execute(const instruction::Instruction &instruction,
                 const std::array<bool, 16> &keyPressed);
};
} // namespace chip8::cpu
