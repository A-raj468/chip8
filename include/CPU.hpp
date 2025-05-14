// CPU.hpp
#pragma once

#include <Constants.hpp>
#include <DisplayBuffer.hpp>
#include <Instruction.hpp>
#include <Keypad.hpp>
#include <Memory.hpp>
#include <Timer.hpp>

#include <array>
#include <cstdint>

namespace chip8::core {
class CPU {
    uint16_t &pc;
    Memory &memory;
    DisplayBuffer &display;
    Timer &timer;

    uint16_t I = 0;
    std::array<uint8_t, REG_SIZE> V = {0};
    std::array<uint16_t, STACK_SIZE> stack = {0};
    uint8_t sp = 0;

  public:
    CPU(uint16_t &pc, Memory &memory, DisplayBuffer &display, Timer &timer);

    bool execute(const Instruction &instruction, const Keypad &keys);
};
} // namespace chip8::core
