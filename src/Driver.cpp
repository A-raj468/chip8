#include <Driver.hpp>

#include <SDL_events.h>
#include <chrono>
#include <string>
#include <thread>

using namespace chip8::frontend;

Driver::Driver(const std::string &rom_path) : rom_path(rom_path) {}

bool Driver::input(SDL_Event &event) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return false;
        } else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
            // Handle key press events
            bool is_down = event.type == SDL_KEYDOWN;
            switch (event.key.keysym.sym) {
            case SDLK_1:
                input_buffer[0x1] = is_down;
                break;
            case SDLK_2:
                input_buffer[0x2] = is_down;
                break;
            case SDLK_3:
                input_buffer[0x3] = is_down;
                break;
            case SDLK_4:
                input_buffer[0xC] = is_down;
                break;
            case SDLK_q:
                input_buffer[0x4] = is_down;
                break;
            case SDLK_w:
                input_buffer[0x5] = is_down;
                break;
            case SDLK_e:
                input_buffer[0x6] = is_down;
                break;
            case SDLK_r:
                input_buffer[0xD] = is_down;
                break;
            case SDLK_a:
                input_buffer[0x7] = is_down;
                break;
            case SDLK_s:
                input_buffer[0x8] = is_down;
                break;
            case SDLK_d:
                input_buffer[0x9] = is_down;
                break;
            case SDLK_f:
                input_buffer[0xE] = is_down;
                break;
            case SDLK_z:
                input_buffer[0xA] = is_down;
                break;
            case SDLK_x:
                input_buffer[0x0] = is_down;
                break;
            case SDLK_c:
                input_buffer[0xB] = is_down;
                break;
            case SDLK_v:
                input_buffer[0xF] = is_down;
                break;
            }
        }
    }
    return true;
}

int Driver::init() {
    input_buffer.fill(false);
    if (vm.load_rom(rom_path) > 0) {
        return 1;
    }
    renderer.init();
    return 0;
}

int Driver::run() {
    const int target_fps = 60;
    const std::chrono::milliseconds frame_duration(1000 / target_fps);
    const int ips = 600;

    bool running = true;
    SDL_Event event;

    while (running) {
        auto start_time = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < ips / target_fps; i++) {
            if (vm.step()) {
                return 1;
            }
        }

        if (vm.tick()) {
            // Sound output
        }

        renderer.render(vm.get_display().data());

        if (!input(event)) {
            running = false;
            break;
        }
        vm.register_keys(input_buffer);

        auto end_time = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            end_time - start_time);

        if (elapsed < frame_duration) {
            std::this_thread::sleep_for(frame_duration - elapsed);
        }
    }
    return 0;
}
