#include <Constants.hpp>
#include <Renderer.hpp>

#include <cstdint>

namespace chip8::frontend {
Renderer::Renderer() {}

Renderer::~Renderer() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

bool Renderer::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return false; // SDL initialization failed
    }

    // Create the SDL window
    window = SDL_CreateWindow("CHIP-8 Emulator", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
                              WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Quit();
        return false; // Window creation failed
    }

    // Create the SDL renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false; // Renderer creation failed
    }

    return true;
}

void Renderer::render(const std::array<std::array<uint8_t, DISPLAY_COLS>,
                                       DISPLAY_ROWS> &display) {
    // Clear the screen before drawing new pixels
    SDL_RenderClear(renderer);

    // Iterate over each pixel in the display array
    for (int y = 0; y < DISPLAY_ROWS; ++y) {
        for (int x = 0; x < DISPLAY_COLS; ++x) {
            // Set the color (white for on, black for off)
            SDL_SetRenderDrawColor(renderer, display[y][x] * 255, 0, 0, 255);

            // Draw a filled rectangle for each pixel
            SDL_Rect rect = {x * SCALE, y * SCALE, SCALE, SCALE};
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    // Present the renderer (update the window)
    SDL_RenderPresent(renderer);
}

} // namespace chip8::frontend
