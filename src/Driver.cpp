#include <Driver.hpp>

#include <SDL_events.h>
#include <chrono>
#include <string>
#include <thread>

using namespace chip8::frontend;

Driver::Driver(const std::string &rom_path) : rom_path(rom_path) {}

int Driver::init() {
    input_buffer.fill(false);
    if (vm.load_rom(rom_path) > 0) {
        return 1;
    }
    return 0;
}

int Driver::run() {
    const int target_fps = 60;
    const std::chrono::milliseconds frame_duration(1000 / target_fps);
    const int ips = 600;

    bool running = true;

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

        auto end_time = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            end_time - start_time);

        if (elapsed < frame_duration) {
            std::this_thread::sleep_for(frame_duration - elapsed);
        }
    }
    return 0;
}
