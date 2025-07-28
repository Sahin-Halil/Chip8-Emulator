#pragma once
#include "Memory.h"
#include "TIleMap.h"
#include <vector>
#include <memory>

class CPU {
	private:
		uint16_t PC;
		uint16_t I;
		std::unique_ptr<Memory> RAM;
		std::unique_ptr<TileMap> Chip8TM;
		std::shared_ptr<CPUTileMapData> Chip8SD;
		//I;
		//stack;
		//delayTimer;
		//soundTimer;
		//variableRegisters;
	public:
		CPU(std::unique_ptr<Memory> ram, std::unique_ptr<TileMap> chip8tm, std::shared_ptr<CPUTileMapData> chip8sd);
		uint16_t Fetch();
		std::vector<uint8_t> Decode(uint16_t instruction);
		void Run();
};

