#include "Memory.h"
#include <vector>
#include <iostream>

// Initialise memory array
Memory::Memory() {
	workingMemory = std::vector<uint8_t>(4096); // Empty 4KB array for storing ROM contents
	
	// All fonts for Chip8 (0-F)
	fonts = { 
		0xF0, 0x90, 0x90, 0x90, 0xF0, // 0	  
		0x20, 0x60, 0x20, 0x20, 0x70, // 1
		0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
		0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
		0x90, 0x90, 0xF0, 0x10, 0x10, // 4
		0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
		0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
		0xF0, 0x10, 0x20, 0x40, 0x40, // 7
		0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
		0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
		0xF0, 0x90, 0xF0, 0x90, 0x90, // A
		0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
		0xF0, 0x80, 0x80, 0x80, 0xF0, // C
		0xE0, 0x90, 0x90, 0x90, 0xE0, // D
		0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
		0xF0, 0x80, 0xF0, 0x80, 0x80  // F 
	};
	
	for (size_t i = 0; i < 80; i++) {
		workingMemory[i + 80] = fonts[i]; // Store fonts in memory
	}
}

// Put ROM contents into memory array
void Memory::setMemory(const std::vector<uint8_t>& gameData) {
	for (size_t i = 0; i < gameData.size(); i++) {
		workingMemory[i + 512] = gameData[i]; // Working memory starts at address 512
	}
}

// Get element at given memory address
uint8_t Memory::getMemory(size_t i) {
	return workingMemory[i];
}

// Update memory at given address
void Memory::updateMemory(size_t index, uint8_t data) {
	workingMemory[index] = data;
}

// Print Fonts and ROM contents in memory
void Memory::printMemory() {
	std::cout << "Printing Contents of Working Memory" << "\n";

	// Loop through all fonts and print them
	std::cout << "Printing Standard Fonts" << "\n";
	for (size_t i = 80; i < 160; i++) {
		std::cout << +getMemory(i) << "\n"; 
	}
	
	// Loop through all ROM contents
	std::cout << "Printing Contents of RAM" << "\n";
	for (size_t i = 512; i < 1000; i++) {
		std::cout << +getMemory(i) << "\n";
	}
	
	std::cout << "End of Contents of Working Memory" << "\n";
}
