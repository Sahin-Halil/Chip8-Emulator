// Chip8-Emulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <SDL3/SDL_main.h>
#include <iostream>
#include <vector>
#include "loadROM.h"
#include "Memory.h"
#include "CPU.h"
#include "TileMap.h"
#include "CPUTileMapData.h"


int main(int argc, char *argv[])
{
    
    /* This is what i normally work by when designing the interface of a non - template function:

     Pass by value if the function does not want to modify the parameter and the value is cheap to copy(int, double, float, char, bool, etc... Notice that std::string, std::vector, and the rest of the containers in the standard library are NOT)

     Pass by const pointer if the value is expensive to copy and the function does not want to modify the value pointed to and NULL is a value that the function handles.

     Pass by non - const pointer if the value is expensive to copy and the function wants to modify the value pointed to and NULL is a value that the function handles.

     Pass by const reference when the value is expensive to copy and the function does not want to modify the value referred to and NULL would not be a valid value if a pointer was used instead.

     Pass by non - const reference when the value is expensive to copy and the function wants to modify the value referred to and NULL would not be a valid value if a pointer was used instead.*/

      // Load ROM contents into array
      std::vector<uint8_t> gameData = loadROM();

      // Create memory object with one pointer
      std::unique_ptr<Memory> RAM = std::make_unique<Memory>();
      RAM->setMemory(gameData); // Load contents of ROM into memory object
      //RAM->printMemory();

      // Shared attributes between CPU and TileMap classes
      std::shared_ptr<CPUTileMapData> Chip8SD1 = std::make_unique<CPUTileMapData>();
      std::shared_ptr<CPUTileMapData> Chip8SD2(Chip8SD1); // Share contents of struct object via shared pointer

      // Create object of TileMap (with one pointer) and pass struct object into it
      std::unique_ptr<TileMap> Chip8TM = std::make_unique<TileMap>(std::move(Chip8SD2));
      //RAM->updateMemory(0x1FF, 1);
      // Create object of CPU and pass in neccessary objects to run it
      CPU Chip8CPU(std::move(RAM), std::move(Chip8TM), std::move(Chip8SD1));
      Chip8CPU.Run(); // Start cpu so emulator can begin running

      return 0;
}



