#include <Decoder.hpp>
#include <Instruction.hpp>
#include <array>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>

constexpr uint16_t MEMSIZE = 4096;
constexpr uint16_t ROM_START = 0x200;

int load_rom(std::array<uint8_t, MEMSIZE> &memory,
             const std::string &rom_path) {
    std::ifstream rom(rom_path, std::ios::binary);
    if (!rom.is_open()) {
        std::cerr << "Failed to open file: " << rom_path << std::endl;
        return 1;
    }
    rom.seekg(0, std::ios::end);
    const size_t ROM_SIZE = rom.tellg();
    rom.seekg(0, std::ios::beg);

    rom.read(reinterpret_cast<char *>(&memory[ROM_START]), ROM_SIZE);
    rom.close();
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <rom_file>" << std::endl;
        return 1;
    }

    std::array<uint8_t, MEMSIZE> memory;
    uint16_t pc = ROM_START;

    std::string rom_path = argv[1];
    if (load_rom(memory, rom_path) > 0) {
        return 1;
    }

    chip8::decoder::Decoder decoder(memory, pc);

    while (true) {
        if (pc >= MEMSIZE) {
            break;
        }
        chip8::instruction::Instruction instruction = decoder.fetch();
        std::cout << instruction.to_string() << std::endl;
    }

    return 0;
}
