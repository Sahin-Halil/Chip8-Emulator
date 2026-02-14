cmake_minimum_required(VERSION 3.20)
project(Chip8-Emulator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED)

add_executable(chip8
    src/main.cpp
    src/CPU.cpp
    src/Memory.cpp
    src/loadROM.cpp
    src/TileMap.cpp
    src/CPUTileMapData.cpp
)

target_include_directories(chip8 PRIVATE include)

target_link_libraries(chip8 PRIVATE SDL3::SDL3)

