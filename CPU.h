#pragma once
#include "Memory.h"

class CPU {
	private:
		uint16_t PC;
		Memory RAM;
		//I;
		//stack;
		//delayTimer;
		//soundTimer;
		//variableRegisters;
		bool quit;
	public:
		CPU(Memory& ram);
		//Run();
		uint16_t Fetch();
		std::vector<uint8_t> Decode(uint16_t instruction);
		void Run();
};

