#pragma once
#include <vector>

class Memory {
    private:
		// Arrays for holding ROM contents
        std::vector<uint8_t> workingMemory;
        std::vector<uint8_t> fonts;

    public:
        Memory(); // Initialises array for holding emulation contents
        void setMemory(const std::vector<uint8_t>& gameData); // Adds ROM contents 
        uint8_t getMemory(size_t i); // gets content of a memory address
        void updateMemory(size_t index, uint8_t data); // Sets content of a memory adress 
        void printMemory(); // Prints Fonts and ROM contents 
};
