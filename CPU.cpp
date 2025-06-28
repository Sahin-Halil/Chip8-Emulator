#include "CPU.h"
#include "Memory.h"

CPU::CPU(Memory& ram) {
	PC = 512;
	RAM = ram;
}

uint16_t CPU::Fetch() {
	uint8_t firstByte = RAM.getMemory(PC);
	uint8_t secondByte = RAM.getMemory(PC + 1);
	PC += 2;

	uint16_t instruction = (firstByte << 8) | secondByte;
	return instruction;
}

