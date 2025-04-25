// Display.hpp
#pragma once

#include <SDL2/SDL.h>
#include <array>

namespace chip8::display {
class Display {
  private:
    std::array<std::array<uint8_t, 64>, 32> &display;

    SDL_Window *window;
    SDL_Renderer *renderer;

  public:
    Display(std::array<std::array<uint8_t, 64>, 32> &display);
    ~Display();

    bool init();

    void update();

    void clear();
};
} // namespace chip8::display
