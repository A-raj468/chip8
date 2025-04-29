cmake_minimum_required(VERSION 3.10)

project(chip8 VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(
  ${PROJECT_NAME}
  ${PROJECT_SOURCE_DIR}/src/main.cpp ${PROJECT_SOURCE_DIR}/src/Instruction.cpp
  ${PROJECT_SOURCE_DIR}/src/Decoder.cpp ${PROJECT_SOURCE_DIR}/src/CPU.cpp
  ${PROJECT_SOURCE_DIR}/src/Renderer.cpp)

find_package(SDL2 REQUIRED)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} SDL2::SDL2)
