# Minimum CMake version required
cmake_minimum_required(VERSION 3.20)

# Project name
project(Chip8-Emulator)

# Use C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SDL3 library (required for graphics and input)
find_package(SDL3 REQUIRED)

# Define executable and source files
add_executable(chip8
    src/main.cpp
    src/CPU.cpp
    src/Memory.cpp
    src/loadROM.cpp
    src/TileMap.cpp
    src/CPUTileMapData.cpp
)

# Include header files from /include directory
target_include_directories(chip8 PRIVATE include)

# Link SDL3 library to the executable
target_link_libraries(chip8 PRIVATE SDL3::SDL3)