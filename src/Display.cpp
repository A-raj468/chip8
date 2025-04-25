#include <Display.hpp>

namespace chip8::display {
Display::Display(std::array<std::array<uint8_t, 64>, 32> &display)
    : display(display), window(nullptr), renderer(nullptr) {
    clear();
}

Display::~Display() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

bool Display::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return false; // SDL initialization failed
    }

    // Create the SDL window
    window =
        SDL_CreateWindow("CHIP-8 Emulator", SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED, 640, 320, SDL_WINDOW_SHOWN);
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

void Display::update() {
    // Set pixel size (adjust as needed)
    const int pixelSize = 10;

    // Clear the screen before drawing new pixels
    SDL_RenderClear(renderer);

    // Iterate over each pixel in the display array
    for (int y = 0; y < 32; ++y) {
        for (int x = 0; x < 64; ++x) {
            // Set the color (white for on, black for off)
            SDL_SetRenderDrawColor(renderer, display[y][x] * 255, 0, 0, 255);

            // Draw a filled rectangle for each pixel
            SDL_Rect rect = {x * pixelSize, y * pixelSize, pixelSize,
                             pixelSize};
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    // Present the renderer (update the window)
    SDL_RenderPresent(renderer);
}

void Display::clear() {
    // Set all pixels to 0 (off)
    for (auto &row : display) {
        row.fill(0);
    }
}
} // namespace chip8::display
