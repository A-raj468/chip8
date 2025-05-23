#include <CPU.hpp>
#include <Constants.hpp>
#include <Core.hpp>
#include <Decoder.hpp>
#include <DisplayBuffer.hpp>

#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace chip8::core;

Core::Core() : decoder(memory, pc), cpu(pc, memory, display, timer) {}

int Core::load_rom(const std::string &rom_path) {
    std::ifstream rom(rom_path, std::ios::binary);
    if (!rom.is_open()) {
        rom.close();
        return 1;
    }
    rom.seekg(0, std::ios::end);
    const size_t ROM_SIZE = rom.tellg();
    if (ROM_SIZE + 0x200 > MEM_SIZE) {
        rom.close();
        return 1;
    }
    rom.seekg(0, std::ios::beg);

    std::vector<uint8_t> r(ROM_SIZE);
    rom.read(reinterpret_cast<char *>(r.data()), ROM_SIZE);
    rom.close();
    for (int i = 0; i < ROM_SIZE; i++) {
        memory.write(ROM_START + i, r[i]);
    }
    return 0;
}

int Core::step() {
    if (pc >= MEM_SIZE) {
        return 1;
    }
    Instruction instruction = decoder.fetch();
    // std::cerr << instruction.to_string() << std::endl;
    cpu.execute(instruction, keypad);
    return 0;
}

bool Core::tick() { return timer.tick(); }

const DisplayBuffer &Core::get_display() const { return display; }

void Core::register_keys(const std::array<bool, NUM_KEYS> &input_buffer) {
    for (int i = 0; i < NUM_KEYS; i++) {
        keypad.set_state(i, input_buffer[i]);
    }
}
