// Renderer.hpp
#pragma once

#include <SDL2/SDL.h>
#include <array>

namespace chip8::renderer {
class Renderer {
  private:
    std::array<std::array<uint8_t, 64>, 32> &display;

    SDL_Window *window;
    SDL_Renderer *renderer;

  public:
    Renderer(std::array<std::array<uint8_t, 64>, 32> &display);
    ~Renderer();

    bool init();

    void update();

    void clear();
};
} // namespace chip8::renderer
