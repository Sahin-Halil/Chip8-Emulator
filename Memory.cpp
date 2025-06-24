#include "Memory.h"
#include <vector>
#include <iostream>

Memory::Memory() {
	workingMemory = std::vector<uint8_t>(4096);
}

void Memory::setMemory(std::vector<uint8_t>& gameData) {
	for (size_t i = 0; i < gameData.size(); i++) {
		workingMemory[i + 512] = gameData[i];
	}
}

uint8_t Memory::getMemory(size_t i) {
	return workingMemory[i];
}

void Memory::updateMemory(size_t index, uint8_t& data) {
	workingMemory[index] = data;
}

void Memory::printMemory() {
	std::cout << "Printing Contents of Working Memory" << "\n";

	for (size_t i = 512; i < 647; i++) {
		std::cout << +getMemory(i) << "\n";
	}
	
	std::cout << "End of Contents of Working Memory" << "\n";
}
