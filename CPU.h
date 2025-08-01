#pragma once
#include "Memory.h"
#include "TIleMap.h"
#include <vector>
#include <memory>

class CPU {
	private:
		// Parts of the CPU
		uint16_t PC;
		uint16_t I;

		// Object pointers needed to work with CPU
		std::unique_ptr<Memory> RAM;
		std::unique_ptr<TileMap> Chip8TM;
		std::shared_ptr<CPUTileMapData> Chip8SD; // Shared attributes
		//I;
		//stack;
		//delayTimer;
		//soundTimer;
	public:
		CPU(std::unique_ptr<Memory> ram, std::unique_ptr<TileMap> chip8tm, std::shared_ptr<CPUTileMapData> chip8sd); // Initialises CPU parts and pointers for objects 
		uint16_t Fetch(); // Fetch next instruction to be decoded
		std::vector<uint8_t> Decode(uint16_t instruction); // Break down instruction to be executed
		void Execute(const std::vector<uint8_t>& currentInstructions); // Perform current instruction
		void Run(); // Run emulation Chip-8 architecture
};

