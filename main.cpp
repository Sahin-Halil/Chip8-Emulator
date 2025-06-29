// Chip8-Emulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "loadROM.h"
#include "Memory.h"
#include "CPU.h"

int main()
{

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


    std::vector<uint8_t> gameData = loadROM();

    Memory RAM;
    RAM.setMemory(gameData);

    CPU chip8Processor(RAM);
    
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
