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
		std::vector<uint8_t> V;
		//I;
		//stack;
		//delayTimer;
		//soundTimer;
		//variableRegisters;
		bool quit;
	public:
		CPU(std::unique_ptr<Memory> ram, std::unique_ptr<TileMap> chip8tm);
		uint16_t Fetch();
		std::vector<uint8_t> Decode(uint16_t instruction);
		void Run();
};

