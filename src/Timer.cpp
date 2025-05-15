#include <Timer.hpp>

#include <cstdint>

using namespace chip8::core;

Timer::Timer() {}

uint8_t Timer::get_delay() { return delay_timer; }

uint8_t Timer::get_sound() { return sound_timer; }

void Timer::set_delay(uint8_t val) { delay_timer = val; }

void Timer::set_sound(uint8_t val) { sound_timer = val; }

bool Timer::tick() {
    if (delay_timer > 0) {
        delay_timer--;
    }

    if (sound_timer > 0) {
        sound_timer--;
        if (sound_timer == 0) {
            return true;
        }
    }
    return false;
}
