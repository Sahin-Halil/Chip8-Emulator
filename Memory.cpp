#include "Memory.h"
#include <vector>
#include <iostream>

Memory::Memory() {
	workingMemory = std::vector<uint8_t>(4096);
}

void Memory::setMemory(std::vector<uint8_t>& gameData) {
	for (int i = 0; i < gameData.size(); i++) {
		workingMemory[i] = gameData[i];
	}
}

uint8_t Memory::getMemory(int i) {
	return workingMemory[i];
}

void Memory::printMemory() {
	std::cout << "Printing Contents of Working Memory" << "\n";

	for (int i = 0; i < 4; i++) {
		std::cout << +getMemory(i) << "\n";
	}
	
	std::cout << "End of Contents of Working Memory" << "\n";
}
