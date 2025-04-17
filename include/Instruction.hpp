// Instruction.hpp
#pragma once

#include <cstdint>
#include <string>
namespace chip8::instruction {
enum class OPP {
    CALL,
    DISPLAY_CLEAR,
    FLOW_RETURN,
    FLOW_GOTO,
    FLOW_CALL,
    COND_EQ_CONST,
    COND_NEQ_CONST,
    COND_EQ_REG,
    CONST_SET,
    CONST_ADD,
    ASSIG_REG,
    BOP_OR,
    BOP_ADD,
    BOP_XOR,
    MATH_ADD,
    MATH_SUB,
    BOP_SR,
    MATH_RSUB,
    BOP_SL,
    COND_NEQ_REG,
    MEM_SET,
    FLOW_PC,
    RAND,
    DISPLAY_DRAW,
    KEY_EQ,
    KEY_NEQ,
    TIMER_GET,
    KEY_SET,
    TIMER_SET,
    SOUND_SET,
    MEM_ADD,
    MEM_SPRITE,
    BCD,
    MEM_DUMP,
    MEM_LOAD,
    UNREACHABLE,
};

struct Instruction {
    uint16_t raw;
    OPP opp;
    uint16_t nnn;
    uint8_t nn;
    uint8_t n;
    uint8_t X, Y;
    Instruction(uint16_t raw);

    std::string to_string();
};
} // namespace chip8::instruction
