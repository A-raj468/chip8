// Core.hpp
#pragma once

#include <CPU.hpp>
#include <Constants.hpp>
#include <Decoder.hpp>
#include <DisplayBuffer.hpp>
#include <Keypad.hpp>
#include <Memory.hpp>
#include <Timer.hpp>

#include <array>
#include <cstdint>
#include <string>

namespace chip8::core {
class Core {
    uint16_t pc = ROM_START;

    Memory memory;
    Decoder decoder;
    Keypad keypad;
    Timer timer;
    CPU cpu;
    DisplayBuffer display;

  public:
    Core();

    int load_rom(const std::string &rom_path);
    int step();
    bool tick();

    const DisplayBuffer &get_display() const;
    void register_keys(const std::array<bool, NUM_KEYS> &input_buffer);
};
} // namespace chip8::core
