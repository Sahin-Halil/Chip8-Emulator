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
	public:
		CPU(Memory& ram);
		//Run();
		uint16_t Fetch();
};

