#include <Decoder.hpp>
#include <Instruction.hpp>
#include <Memory.hpp>

#include <cstdint>

using namespace chip8::core;

Decoder::Decoder(Memory &memory, uint16_t &pc) : memory(memory), pc(pc) {}

Instruction Decoder::fetch() {
    uint16_t raw = memory.read(pc) << 8 | memory.read(pc + 1);
    pc += 2;
    return Instruction(raw);
}

Instruction Decoder::peek() {
    uint16_t raw = memory.read(pc) << 8 | memory.read(pc + 1);
    return Instruction(raw);
}
