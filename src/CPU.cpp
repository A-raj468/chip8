#include <CPU.hpp>
#include <Instruction.hpp>
#include <cstdint>
#include <cstdlib>

namespace chip8::cpu {
CPU::CPU(std::array<uint8_t, 4096> &memory, uint16_t &pc, uint16_t &I,
         std::array<uint8_t, 16> &V,
         std::array<std::array<uint8_t, 64>, 32> &display,
         std::atomic<uint8_t> &delay_timer, std::atomic<uint8_t> &sound_timer)
    : memory(memory), pc(pc), I(I), V(V), display(display),
      delay_timer(delay_timer), sound_timer(sound_timer) {}

bool CPU::execute(const instruction::Instruction &instruction,
                  const std::array<bool, 16> &keyPressed) {
    switch (instruction.opp) {
    case instruction::OPP::CALL: {
        // Log warning
        break;
    }
    case instruction::OPP::DISPLAY_CLEAR: {
        for (auto &row : display) {
            row.fill(0);
        }
        break;
    }
    case instruction::OPP::FLOW_RETURN: {
        sp--;
        pc = stack[sp];
        break;
    }
    case instruction::OPP::FLOW_GOTO: {
        pc = instruction.nnn;
        break;
    }
    case instruction::OPP::FLOW_CALL: {
        stack[sp] = pc;
        sp++;
        pc = instruction.nnn;
        break;
    }
    case instruction::OPP::COND_EQ_CONST: {
        if (V[instruction.X] == instruction.nn) {
            pc += 2;
        }
        break;
    }
    case instruction::OPP::COND_NEQ_CONST: {
        if (V[instruction.X] != instruction.nn) {
            pc += 2;
        }
        break;
    }
    case instruction::OPP::COND_EQ_REG: {
        if (V[instruction.X] == V[instruction.Y]) {
            pc += 2;
        }
        break;
    }
    case instruction::OPP::CONST_SET: {
        V[instruction.X] = instruction.nn;
        break;
    }
    case instruction::OPP::CONST_ADD: {
        V[instruction.X] += instruction.nn;
        break;
    }
    case instruction::OPP::ASSIG_REG: {
        V[instruction.X] = V[instruction.Y];
        break;
    }
    case instruction::OPP::BOP_OR: {
        V[instruction.X] |= V[instruction.Y];
        break;
    }
    case instruction::OPP::BOP_ADD: {
        V[instruction.X] &= V[instruction.Y];
        break;
    }
    case instruction::OPP::BOP_XOR: {
        V[instruction.X] ^= V[instruction.Y];
        break;
    }
    case instruction::OPP::MATH_ADD: {
        V[instruction.X] += V[instruction.Y];
        break;
    }
    case instruction::OPP::MATH_SUB: {
        V[instruction.X] -= V[instruction.Y];
        break;
    }
    case instruction::OPP::BOP_SR: {
        V[instruction.X] >>= 1;
        break;
    }
    case instruction::OPP::MATH_RSUB: {
        V[instruction.X] = V[instruction.Y] - V[instruction.X];
        break;
    }
    case instruction::OPP::BOP_SL: {
        V[instruction.X] <<= 1;
        break;
    }
    case instruction::OPP::COND_NEQ_REG: {
        if (V[instruction.X] != V[instruction.Y]) {
            pc += 2;
        }
        break;
    }
    case instruction::OPP::MEM_SET: {
        I = instruction.nnn;
        break;
    }
    case instruction::OPP::FLOW_PC: {
        pc = V[0] + instruction.nnn;
        break;
    }
    case instruction::OPP::RAND: {
        V[instruction.X] = (rand() % 256) & instruction.nn;
        break;
    }
    case instruction::OPP::DISPLAY_DRAW: {
        int x = V[instruction.X];
        int y = V[instruction.Y];
        int n = instruction.n;
        V[0xF] = 0;
        for (int i = 0; i < n; i++) {
            uint8_t row = memory[I + i];
            for (int j = 0; j < 8; j++) {
                int screenX = (x + j) % 64;
                int screenY = (y + i) % 32;
                uint8_t pixel = (row >> (7 - j)) & 0x1;
                if (pixel == 1 && display[screenX][screenY] == 1) {
                    V[0xF] = 1;
                }
                display[screenX][screenY] ^= pixel;
            }
        }
        break;
    }
    case instruction::OPP::KEY_EQ: {
        if (keyPressed[V[instruction.X]]) {
            pc += 2;
        }
        break;
    }
    case instruction::OPP::KEY_NEQ: {
        if (!keyPressed[V[instruction.X]]) {
            pc += 2;
        }
        break;
    }
    case instruction::OPP::TIMER_GET: {
        V[instruction.X] = delay_timer;
        break;
    }
    case instruction::OPP::KEY_SET: {
        int i = 0;
        for (i = 0; i < 16; i++) {
            if (keyPressed[i]) {
                break;
            }
        }
        if (i < 16) {
            V[instruction.X] = i;
        } else {
            pc -= 2;
        }
        break;
    }
    case instruction::OPP::TIMER_SET: {
        delay_timer = V[instruction.X];
        break;
    }
    case instruction::OPP::SOUND_SET: {
        sound_timer = V[instruction.X];
        break;
    }
    case instruction::OPP::MEM_ADD: {
        I += V[instruction.X];
        break;
    }
    case instruction::OPP::MEM_SPRITE: {
        uint8_t character = V[instruction.X];
        I = 0x050 + (character * 5);
        break;
    }
    case instruction::OPP::BCD: {
        int value = V[instruction.X];
        memory[I] = value / 100;
        memory[I + 1] = (value / 10) % 10;
        memory[I + 2] = value % 10;
        break;
    }
    case instruction::OPP::MEM_DUMP: {
        for (int i = 0; i < instruction.X; i++) {
            memory[I + i] = V[i];
        }
        break;
    }
    case instruction::OPP::MEM_LOAD: {
        for (int i = 0; i < instruction.X; i++) {
            V[i] = memory[I + i];
        }
        break;
    }
    case instruction::OPP::UNREACHABLE: {
        return false;
        break;
    }
    default: {
        break;
    }
    }
    return true;
}
} // namespace chip8::cpu
