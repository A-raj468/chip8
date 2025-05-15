#include <Constants.hpp>
#include <Memory.hpp>

#include <cstdint>

using namespace chip8::core;

Memory::Memory() {}

uint8_t Memory::read(uint16_t addr) {
    if (addr >= MEM_SIZE) {
        return 0;
    }

    return memory[addr];
}

void Memory::write(uint16_t addr, uint8_t val) {
    if (addr >= MEM_SIZE) {
        return;
    }

    memory[addr] = val;
}
