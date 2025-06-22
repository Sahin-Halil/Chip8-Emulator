#pragma once
#include <vector>

class Memory {
    private:
        std::vector<uint8_t> workingMemory;
    public:
        Memory();
        void setMemory(std::vector<uint8_t>& gameData);
        uint8_t getMemory(int i);
        void printMemory();
};
