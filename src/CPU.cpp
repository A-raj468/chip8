#include <CPU.hpp>
#include <Instruction.hpp>
#include <cstdint>

namespace chip8::cpu {
CPU::CPU(std::array<uint8_t, 4096> &memory, uint16_t &pc, uint16_t &I,
         std::array<uint8_t, 16> &V, std::array<uint16_t, 16> &stack,
         uint8_t &sp)
    : memory(memory), pc(pc), I(I), V(V), stack(stack), sp(sp) {}

bool CPU::execute(instruction::Instruction instruction, int8_t key) {
    switch (instruction.opp) {
    default: {
        break;
    }
    }
    return true;
}
} // namespace chip8::cpu
