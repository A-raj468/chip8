// Driver.hpp
#pragma once

#include <Constants.hpp>
#include <Core.hpp>
#include <Renderer.hpp>

#include <SDL_events.h>
#include <array>
#include <string>

namespace chip8::frontend {
class Driver {
    core::Core vm;
    frontend::Renderer renderer;

    std::string rom_path;
    std::array<bool, NUM_KEYS> input_buffer = {false};

    bool input(SDL_Event &event);

  public:
    Driver(const std::string &rom_path);

    int init();
    int run();
};
} // namespace chip8::frontend
