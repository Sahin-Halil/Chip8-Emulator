#pragma once
#include <SDL3/SDL.h>
#include "Memory.h"
#include "TIleMap.h"
#include <vector>
#include <memory>

class CPU {
private:
	// Parts of the CPU
	uint16_t PC;
	uint16_t I;
	std::vector<uint16_t> Stack;

	// Game loop essentials
	int frameRate;
	uint64_t timeBefore;

	// Object pointers needed to work with CPU
	std::unique_ptr<Memory> RAM;
	std::unique_ptr<TileMap> Chip8TM;
	std::shared_ptr<CPUTileMapData> Chip8SD; // Shared attributes
	//stack;
	//delayTimer;
	//soundTimer;
public:
	CPU(std::unique_ptr<Memory> ram, std::unique_ptr<TileMap> chip8tm, std::shared_ptr<CPUTileMapData> chip8sd); // Initialises CPU parts and pointers for objects 
	uint16_t Fetch(); // Fetch next instruction to be decoded
	std::vector<uint8_t> Decode(uint16_t instruction); // Break down instruction to be executed
	void Execute(const std::vector<uint8_t>& currentInstructions); // Perform current instruction
	void Run(); // Run emulation Chip-8 architecture
	std::vector<std::vector<bool>> getDrawingData(uint8_t N); // Get small 2D map of sprite data
	void remainingTime(); // Wait until time is up before starting next loop cycle (frame)

	// Getter and Setter for PC
	uint16_t getPC();
	void setPC(uint16_t newPC);

	// Getter and Setter for I
	uint16_t getI();
	void setI(uint16_t newI);

	// Pop and Push for Stack
	uint16_t popFromStack();
	void pushToStack(uint16_t address);
};

