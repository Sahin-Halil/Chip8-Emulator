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
    
    
    /*TileMap Chip8Game;

    std::size_t x = 40;
    std::size_t y = 0;
    std::size_t N = 5;
    std::vector<std::vector<bool>> g(N, std::vector<bool>(8, false));
    std::vector<uint8_t> data = {};
    std::vector<uint8_t> vx = { 0x20, 0x60, 0x20, 0x20, 0x70 };
    bool quit = false;
    while (quit == false)
    {
        Chip8Game.resetMap();
        for (std::size_t i = 0; i < N; i++) {
            for (std::size_t j = 0; j < 8; j++) {
                g[i][j] = false;
            }
        }
        Chip8Game.getEvent(quit, vx);
        for (std::size_t i = 0; i < N; i++) {
            std::uint8_t val = vx[i];
            std::uint8_t mask = 0x80;
            for (std::size_t j = 0; j < 8; j++) {
                g[i][j] = mask & val;
                mask >>= 1;
            }
        }
        Chip8Game.updateMap(x, y, N, g);
        Chip8Game.Draw();
        Chip8Game.remainingTime();
       
    }
    
    Chip8Game.Destroy();
    return 0;*/


    /* This is what i normally work by when designing the interface of a non - template function:

     Pass by value if the function does not want to modify the parameter and the value is cheap to copy(int, double, float, char, bool, etc... Notice that std::string, std::vector, and the rest of the containers in the standard library are NOT)

     Pass by const pointer if the value is expensive to copy and the function does not want to modify the value pointed to and NULL is a value that the function handles.

     Pass by non - const pointer if the value is expensive to copy and the function wants to modify the value pointed to and NULL is a value that the function handles.

     Pass by const reference when the value is expensive to copy and the function does not want to modify the value referred to and NULL would not be a valid value if a pointer was used instead.

     Pass by non - const reference when the value is expensive to copy and the function wants to modify the value referred to and NULL would not be a valid value if a pointer was used instead.*/

      std::vector<uint8_t> gameData = loadROM();

      std::unique_ptr<Memory> RAM = std::make_unique<Memory>();
      RAM->setMemory(gameData);
      //RAM->printMemory();

      std::shared_ptr<CPUTileMapData> Chip8SD1 = std::make_unique<CPUTileMapData>();
      std::shared_ptr<CPUTileMapData> Chip8SD2(Chip8SD1);

      std::unique_ptr<TileMap> Chip8TM = std::make_unique<TileMap>(std::move(Chip8SD2));

      CPU Chip8CPU(std::move(RAM), std::move(Chip8TM), std::move(Chip8SD1));
      Chip8CPU.Run();

      return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
