// Chip8.hpp
#pragma once

#include <CPU.hpp>
#include <Constants.hpp>
#include <Decoder.hpp>
#include <Renderer.hpp>

#include <SDL_events.h>
#include <array>
#include <cstdint>
#include <string>

namespace chip8::core {
class Chip8System {
    std::array<uint8_t, MEM_SIZE> memory = {0};
    uint16_t pc = ROM_START;
    std::array<std::array<uint8_t, DISPLAY_COLS>, DISPLAY_ROWS> display = {
        {{0}}};
    uint8_t delay_timer = 0;
    uint8_t sound_timer = 0;
    std::array<bool, 16> keyPressed = {false};

    Decoder decoder;
    CPU cpu;
    frontend::Renderer renderer;

    bool running = false;

    bool tick();
    void register_keys(SDL_Event &event);

  public:
    Chip8System();

    int load_rom(const std::string &rom_path);
    int init();
    int run();
};
} // namespace chip8::core
