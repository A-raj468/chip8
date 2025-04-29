#include <CPU.hpp>
#include <Decoder.hpp>
#include <Instruction.hpp>

#include <array>
#include <atomic>
#include <chrono>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>

constexpr uint16_t MEMSIZE = 4096;
constexpr uint16_t ROM_START = 0x200;

std::array<uint8_t, MEMSIZE> memory = {0};
uint16_t pc = ROM_START;
uint16_t I = 0;
std::array<uint8_t, 16> V = {0};
std::array<std::array<uint8_t, 64>, 32> display = {{{0}}};
std::atomic<uint8_t> delay_timer = 0;
std::atomic<uint8_t> sound_timer = 0;
std::array<bool, 16> keyPressed = {false};

std::atomic<bool> running = true;

int load_rom(const std::string &rom_path) {
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

void updateTimers() {
    while (running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
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
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <rom_file>" << std::endl;
        return 1;
    }

    std::string rom_path = argv[1];
    if (load_rom(rom_path) > 0) {
        return 1;
    }

    chip8::decoder::Decoder decoder(memory, pc);
    chip8::cpu::CPU cpu(memory, pc, I, V, display, delay_timer, sound_timer);

    std::thread t(updateTimers);
    while (running) {
        if (pc >= MEMSIZE) {
            running = false;
            break;
        }
        chip8::instruction::Instruction instruction = decoder.fetch();
        std::cout << instruction.to_string() << std::endl;
        cpu.execute(instruction, keyPressed);
    }

    t.join();

    return 0;
}
