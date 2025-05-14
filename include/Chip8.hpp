// Chip8.hpp
#pragma once

#include <CPU.hpp>
#include <Decoder.hpp>
#include <Renderer.hpp>
#include <SDL_events.h>
#include <array>
#include <cstdint>
#include <string>

namespace chip8::chip8 {
class Chip8System {
    static constexpr uint16_t MEMSIZE = 4096;
    static constexpr uint16_t ROM_START = 0x200;

    std::array<uint8_t, MEMSIZE> memory = {0};
    uint16_t pc = ROM_START;
    std::array<std::array<uint8_t, 64>, 32> display = {{{0}}};
    uint8_t delay_timer = 0;
    uint8_t sound_timer = 0;
    std::array<bool, 16> keyPressed = {false};

    decoder::Decoder decoder;
    cpu::CPU cpu;
    renderer::Renderer renderer;

    bool running = false;

    bool tick();
    void register_keys(SDL_Event &event);

  public:
    Chip8System();

    int load_rom(const std::string &rom_path);
    int init();
    int run();
};
} // namespace chip8::chip8
