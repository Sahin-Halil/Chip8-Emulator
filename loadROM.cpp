#include <iostream>
#include <fstream>
#include <vector>
#include "loadROM.h"

std::vector<uint8_t> loadROM() {
    std::vector<uint8_t> gameData = {};
    
    std::ifstream chip8Game;
    chip8Game.open("Game-Files/IBM-Logo.ch8", std::ios::out | std::ios::binary);

    if (chip8Game.is_open()) {
        std::cout << "Success: chip8 file was opened" << "\n";
        uint8_t data = chip8Game.get();
        while (chip8Game.good()) {
            //std::cout << +data << "\n";
            gameData.push_back(data);
            data = chip8Game.get();
        }
    }
    else {
        std::cout << "Error: chip8 file could not be opened";
    }

    chip8Game.close();

    return gameData;
}