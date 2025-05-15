#include <Driver.hpp>

#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <rom_file>" << std::endl;
        return 1;
    }

    std::string rom_path = argv[1];

    chip8::frontend::Driver driver(rom_path);
    if (driver.init()) {
        std::cerr << "Driver Initialization Failed!\n";
        return 1;
    }
    driver.run();

    return 0;
}
