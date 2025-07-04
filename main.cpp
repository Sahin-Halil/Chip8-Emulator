// Chip8-Emulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include "Memory.h"
#include "loadROM.h"

int main()
{
    std::vector<uint8_t> gameData = loadROM();
    uint8_t extraData1 = 100;
    uint8_t extraData2 = 254;
    uint8_t extraData3 = 255;
   
    Memory RAM;
    RAM.setMemory(gameData);
    RAM.updateMemory(132 + 512, extraData1);
    RAM.updateMemory(133 + 512, extraData2);
    RAM.updateMemory(134 + 512, extraData3);
    RAM.printMemory();
    
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
