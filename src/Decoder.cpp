#include <Decoder.hpp>
#include <Instruction.hpp>
#include <cstdint>

namespace chip8::decoder {

Decoder::Decoder(std::array<uint8_t, 4096> &memory, uint16_t &pc)
    : memory(memory), pc(pc) {}

instruction::Instruction Decoder::fetch() {
    uint16_t raw = memory[pc] << 8 | memory[pc + 1];
    pc += 2;
    return instruction::Instruction(raw);
}

instruction::Instruction Decoder::peek() {
    uint16_t raw = memory[pc] << 8 | memory[pc + 1];
    return instruction::Instruction(raw);
}
} // namespace chip8::decoder
