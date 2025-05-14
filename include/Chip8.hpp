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
class Chip8 {
    static constexpr uint16_t MEMSIZE = 4096;
    static constexpr uint16_t ROM_START = 0x200;

    std::array<uint8_t, MEMSIZE> memory = {0};
    uint16_t pc = ROM_START;
    uint16_t I = 0;
    std::array<uint8_t, 16> V = {0};
    std::array<std::array<uint8_t, 64>, 32> display = {{{0}}};
    uint8_t delay_timer = 0;
    uint8_t sound_timer = 0;
    std::array<bool, 16> keyPressed = {false};

    decoder::Decoder decoder;
    cpu::CPU cpu;
    renderer::Renderer renderer;

    bool running = false;

    void update_timers();
    void register_keys(SDL_Event &event);

  public:
    Chip8();

    int load_rom(const std::string &rom_path);
    int init();
    int run();
};
} // namespace chip8::chip8
