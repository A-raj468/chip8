#include "Display.hpp"
#include <CPU.hpp>
#include <Decoder.hpp>
#include <Instruction.hpp>

#include <array>
#include <chrono>
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

void updateTimers(uint8_t &delay_timer, uint8_t &sound_timer) {
    if (delay_timer > 0) {
        --delay_timer;
    }

    if (sound_timer > 0) {
        --sound_timer;
        if (sound_timer == 0) {
            // Stop sound here
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <rom_file>" << std::endl;
        return 1;
    }

    std::array<uint8_t, MEMSIZE> memory;
    uint16_t pc = ROM_START;
    uint16_t I = 0;
    std::array<uint8_t, 16> V;
    std::array<std::array<uint8_t, 64>, 32> display;
    uint8_t delay_timer = 0;
    uint8_t sound_timer = 0;
    std::array<bool, 16> keyPressed;

    std::string rom_path = argv[1];
    if (load_rom(memory, rom_path) > 0) {
        return 1;
    }

    chip8::decoder::Decoder decoder(memory, pc);
    chip8::cpu::CPU cpu(memory, pc, I, V, display, delay_timer, sound_timer);
    chip8::display::Display renderer(display);
    if (!renderer.init()) {
        std::cerr << "Failed to initialize SDL!" << std::endl;
        return 1;
    }

    const std::chrono::milliseconds timerUpdateInterval(16);

    std::chrono::steady_clock::time_point lastUpdateTime;
    auto currentTime = std::chrono::steady_clock::now();

    while (true) {
        if (pc >= MEMSIZE) {
            break;
        }
        chip8::instruction::Instruction instruction = decoder.fetch();
        cpu.execute(instruction, keyPressed);

        if (currentTime - lastUpdateTime >= timerUpdateInterval) {
            updateTimers(delay_timer, sound_timer);
            lastUpdateTime = currentTime;
            // Update display
            renderer.update();
        }
    }

    return 0;
}
