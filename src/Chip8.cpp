#include <Chip8.hpp>

#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>

namespace chip8::chip8 {
Chip8::Chip8()
    : decoder(memory, pc),
      cpu(memory, pc, I, V, display, delay_timer, sound_timer),
      renderer(display) {}

int Chip8::load_rom(const std::string &rom_path) {
    std::ifstream rom(rom_path, std::ios::binary);
    if (!rom.is_open()) {
        std::cerr << "Failed to open file: " << rom_path << std::endl;
        return 1;
    }
    rom.seekg(0, std::ios::end);
    const size_t ROM_SIZE = rom.tellg();
    rom.seekg(0, std::ios::beg);

    rom.read(reinterpret_cast<char *>(&memory[ROM_START]), ROM_SIZE);
    rom.close();
    return 0;
}

int Chip8::init() { return renderer.init(); }

int Chip8::run() {
    const int target_fps = 60;
    const std::chrono::milliseconds frame_duration(1000 / target_fps);
    const int ips = 600;

    running = true;
    SDL_Event event;

    while (running) {
        auto start_time = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < ips / target_fps; i++) {
            if (pc >= MEMSIZE) {
                running = false;
                break;
            }
            instruction::Instruction instruction = decoder.fetch();
            /* std::cout << instruction.to_string() << std::endl; */
            cpu.execute(instruction, keyPressed);
        }

        update_timers();
        renderer.update();

        register_keys(event);

        auto end_time = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            end_time - start_time);

        if (elapsed < frame_duration) {
            std::this_thread::sleep_for(frame_duration - elapsed);
        }
    }
    return 0;
}

void Chip8::update_timers() {
    if (delay_timer > 0) {
        delay_timer--;
    }

    if (sound_timer > 0) {
        sound_timer--;
        if (sound_timer == 0) {
            // Stop sound here
        }
    }
}

void Chip8::register_keys(SDL_Event &event) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false; // Exit the loop if the user closes the window
        } else if (event.type == SDL_KEYDOWN) {
            // Handle key down events
            switch (event.key.keysym.sym) {
            case SDLK_1:
                keyPressed[0x1] = true;
                break;
            case SDLK_2:
                keyPressed[0x2] = true;
                break;
            case SDLK_3:
                keyPressed[0x3] = true;
                break;
            case SDLK_4:
                keyPressed[0xC] = true;
                break;
            case SDLK_q:
                keyPressed[0x4] = true;
                break;
            case SDLK_w:
                keyPressed[0x5] = true;
                break;
            case SDLK_e:
                keyPressed[0x6] = true;
                break;
            case SDLK_r:
                keyPressed[0xD] = true;
                break;
            case SDLK_a:
                keyPressed[0x7] = true;
                break;
            case SDLK_s:
                keyPressed[0x8] = true;
                break;
            case SDLK_d:
                keyPressed[0x9] = true;
                break;
            case SDLK_f:
                keyPressed[0xE] = true;
                break;
            case SDLK_z:
                keyPressed[0xA] = true;
                break;
            case SDLK_x:
                keyPressed[0x0] = true;
                break;
            case SDLK_c:
                keyPressed[0xB] = true;
                break;
            case SDLK_v:
                keyPressed[0xF] = true;
                break;
            }
        } else if (event.type == SDL_KEYUP) {
            // Handle key up events
            switch (event.key.keysym.sym) {
            case SDLK_1:
                keyPressed[0x1] = false;
                break;
            case SDLK_2:
                keyPressed[0x2] = false;
                break;
            case SDLK_3:
                keyPressed[0x3] = false;
                break;
            case SDLK_4:
                keyPressed[0xC] = false;
                break;
            case SDLK_q:
                keyPressed[0x4] = false;
                break;
            case SDLK_w:
                keyPressed[0x5] = false;
                break;
            case SDLK_e:
                keyPressed[0x6] = false;
                break;
            case SDLK_r:
                keyPressed[0xD] = false;
                break;
            case SDLK_a:
                keyPressed[0x7] = false;
                break;
            case SDLK_s:
                keyPressed[0x8] = false;
                break;
            case SDLK_d:
                keyPressed[0x9] = false;
                break;
            case SDLK_f:
                keyPressed[0xE] = false;
                break;
            case SDLK_z:
                keyPressed[0xA] = false;
                break;
            case SDLK_x:
                keyPressed[0x0] = false;
                break;
            case SDLK_c:
                keyPressed[0xB] = false;
                break;
            case SDLK_v:
                keyPressed[0xF] = false;
                break;
            }
        }
    }
}

} // namespace chip8::chip8
