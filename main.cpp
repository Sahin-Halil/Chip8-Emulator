// Chip8-Emulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <SDL3/SDL_main.h>
#include <iostream>
#include <vector>
#include "loadROM.h"
#include "Memory.h"
#include "CPU.h"
#include "TileMap.h"


int main(int argc, char* argv[])
{
    
    
    TileMap Chip8Game;

    //uint8_t val = 5;
    //bool arr[8] = {};
    //std::size_t i = 0;
    //for (unsigned int mask = 0x80; mask != 0; mask >>= 1) {
    //    arr[i] = val & mask;
    //    i += 1;
    //}
    //for (std::size_t k = 0; k < 8; k++) {
    //    std::cout << arr[k] << "\n";
    //}
    // 0xF0, 0x90, 0x90, 0x90, 0xF0 = 0
    std::size_t x = 28;
    std::size_t y = 14;
    std::size_t N = 5;

    std::vector<std::vector<bool>> g(N, std::vector<bool>(8, false));
    std::vector<uint8_t> data = { 0xF0, 0x90, 0x90, 0x90, 0xF0 };
    auto dataIndex = data.begin();
    for (std::size_t i = 0; i < N; i++) {
        
        std::uint8_t val = *(dataIndex);
        //std::cout << +val << " ";
        std::uint8_t mask = 0x80;
        for (std::size_t j = 0; j < 8; j++) {
            g[i][j] = mask & val;
            //std::cout << +mask << " ";
            mask >>= 1;
            //std::cout << g[i][j];
        }
        //std::cout << "\n";
        dataIndex++;
    }
    
    // bitmapping for 0
    /*g[0][0] = true;
    g[0][1] = true;
    g[0][2] = true;
    g[0][3] = true;
    g[1][0] = true;
    g[1][3] = true;
    g[2][0] = true;
    g[2][3] = true;
    g[3][0] = true;
    g[3][3] = true;
    g[4][0] = true;
    g[4][1] = true;
    g[4][2] = true;
    g[4][3] = true;*/

    
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < g[i].size(); j++)
        {
            //g[i][j] = j % 2;
            //std::cout << "I was here";
            std::cout << g[i][j] << " ";
        }
        std::cout << '\n';
    }

    Chip8Game.updateMap(x, y, N, g);
    Chip8Game.Draw();
    //SDL_Delay(10000);
    // reverting changes
    /*g[0][0] = false;
    g[0][1] = false;
    g[0][2] = false;
    g[0][3] = false;
    g[1][0] = false;
    g[1][3] = false;
    g[2][0] = false;
    g[2][3] = false;
    g[3][0] = false;
    g[3][3] = false;
    g[4][0] = false;
    g[4][1] = false;
    g[4][2] = false;
    g[4][3] = false;*/
    // bitmapping for 1
    /*g[0][2] = true;
    g[1][1] = true;
    g[1][2] = true;
    g[2][2] = true;
    g[3][2] = true;
    g[4][1] = true;
    g[4][2] = true;
    g[4][3] = true;
    Chip8Game.updateMap(5, 20, 5, g);
    Chip8Game.Draw();*/
    SDL_Event e;
    bool quit = false;
    while (quit == false)
    {
        //Get event data
        while (SDL_PollEvent(&e) == true)
        {
            //If event is quit type
            if (e.type == SDL_EVENT_QUIT)
            {
                //End the main loop
                quit = true;
            }
        }
        //Chip8Game.Draw();
    }
    
    Chip8Game.Destroy();
    return 0;


    /* This is what i normally work by when designing the interface of a non - template function:

     Pass by value if the function does not want to modify the parameter and the value is cheap to copy(int, double, float, char, bool, etc... Notice that std::string, std::vector, and the rest of the containers in the standard library are NOT)

     Pass by const pointer if the value is expensive to copy and the function does not want to modify the value pointed to and NULL is a value that the function handles.

     Pass by non - const pointer if the value is expensive to copy and the function wants to modify the value pointed to and NULL is a value that the function handles.

     Pass by const reference when the value is expensive to copy and the function does not want to modify the value referred to and NULL would not be a valid value if a pointer was used instead.

     Pass by non - const reference when the value is expensive to copy and the function wants to modify the value referred to and NULL would not be a valid value if a pointer was used instead.*/

     /*uint8_t example1 = 254;
     uint8_t example2 = 30;
     uint16_t res = (example1 << 8) | example2;
     std::cout << +example1 << "\n";
     std::cout << +res << "\n";*/

     /*std::vector<uint8_t> data1 = {1, 2, 3, 4};
     uint16_t pc = 0;
     std::cout << +data1[pc] << " " << +data1[pc + 1] << "\n";
     pc += 2;
     std::cout << +data1[pc] << " " << +data1[pc + 1];*/


     /* std::vector<uint8_t> gameData = loadROM();

      Memory RAM;
      RAM.setMemory(gameData);
      RAM.printMemory();

      std::cout << +RAM.getMemory(516) << "\n";
      std::cout << +RAM.getMemory(517) << "\n";

      CPU chip8Processor(RAM);
      chip8Processor.Fetch();
      chip8Processor.Fetch();
      std::cout << +chip8Processor.Fetch();

      return 0;*/

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
