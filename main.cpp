// Chip8-Emulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>
#include "Memory.h"
using namespace std;



int main()
{
    
    ifstream chip8;
    chip8.open("Game-Files/IBM-Logo.ch8");
    if (chip8.is_open()) {
        std::cout << "Success: chip8 file was opened";
    }
    else {
        std::cout << "Error: chip8 file could not be opened";
    }
    
    /*std::vector<uint8_t> gameData = {};
    
    Memory RAM;
    RAM.setMemory(gameData);
    RAM.printMemory();
    
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
