#include "Memory.h"
#include <vector>
#include <iostream>

Memory::Memory() {
	workingMemory = std::vector<uint8_t>(4096);
}

void Memory::addToMemory(std::vector<uint8_t>& gameData) {
	for (int i = 0; i < gameData.size(); i++) {
		workingMemory[i] = gameData[i];
	}
}

void Memory::print() {
	std::cout << "Printing Contents of Working Memory" << "\n";

	for (int i = 0; i < 4; i++) {
		std::cout << +workingMemory[i] << "\n";
	}
	
	std::cout << "End of Contents of Working Memory" << "\n";
}
