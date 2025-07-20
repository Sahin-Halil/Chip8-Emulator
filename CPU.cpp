#include "CPU.h"
#include <iostream>

CPU::CPU(Memory& ram) {
	PC = 512;
	RAM = ram;
	quit = false;
}

uint16_t CPU::Fetch() {
	uint8_t firstByte = RAM.getMemory(PC);
	uint8_t secondByte = RAM.getMemory(PC + 1);
	PC += 2;

	uint16_t instruction = (firstByte << 8) | secondByte;
	return instruction;
}

void CPU::Run() {
	while (quit == false) {
		std::cout << "here";
	}
}

