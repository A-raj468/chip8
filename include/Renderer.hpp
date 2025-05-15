// Renderer.hpp
#pragma once

#include <Constants.hpp>

#include <SDL2/SDL.h>
#include <array>
#include <cstdint>

namespace chip8::frontend {
class Renderer {
  private:
    SDL_Window *window;
    SDL_Renderer *renderer;

  public:
    Renderer();
    ~Renderer();

    bool init();

    void render(const std::array<std::array<uint8_t, 64>, 32> &display);
};
} // namespace chip8::frontend
