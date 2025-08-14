#include <iostream>
#include <fstream>
#include <vector>
#include "loadROM.h"

// Load contents of ROM into array
std::vector<uint8_t> loadROM() {
    std::vector<uint8_t> gameData = {}; // Initialised array to store ROM contents
    
	// Open ROM as read only binary file
    std::ifstream chip8Game;
    chip8Game.open("Game-Files/4-Flags.ch8", std::ios::out | std::ios::binary);

	// Add contents to array if ROM exists
    if (chip8Game.is_open()) {
        // std::cout << "Success: chip8 file was opened" << "\n";
        uint8_t data = chip8Game.get(); // Get current binary value
        
		// Loop through the ROM and add each binary value to array
		while (chip8Game.good()) {
            //std::cout << +data << "\n";
            gameData.push_back(data);
            data = chip8Game.get(); // Get next binary value (if any)
        }
    }
    else {
        std::cout << "Error: chip8 file could not be opened"; // Error message incase ROM was not opened
    }

	// Close ROM when done accessing its contents (even if it didn't exist, this is to save space)
    chip8Game.close();

    return gameData;
}