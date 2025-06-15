#pragma once
#include <vector>

class Memory {
private:
    std::vector<uint8_t> workingMemory;
public:
    Memory();
    void addToMemory(std::vector<uint8_t>& gameData);
    void print();
};
