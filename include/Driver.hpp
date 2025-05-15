// Driver.hpp
#pragma once

#include <Constants.hpp>
#include <Core.hpp>
#include <array>
#include <string>

namespace chip8::frontend {
class Driver {
    core::Core vm;

    std::string rom_path;
    std::array<bool, NUM_KEYS> input_buffer = {false};

  public:
    Driver(const std::string &rom_path);

    int init();
    int run();
};
} // namespace chip8::frontend
