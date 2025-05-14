#include <Chip8.hpp>

#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <rom_file>" << std::endl;
        return 1;
    }

    std::string rom_path = argv[1];

    chip8::chip8::Chip8 chip8;
    if (chip8.load_rom(rom_path) > 0) {
        std::cerr << "Failed to load rom: " << rom_path << std::endl;
        return 1;
    }

    if (!chip8.init()) {
        std::cerr << "Failed to initialize SDL!" << std::endl;
        return 1;
    }

    chip8.run();

    return 0;
}
