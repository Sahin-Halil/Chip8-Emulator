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

std::vector<uint8_t> CPU::Decode(uint16_t instruction) {
	std::vector<uint8_t> instructions = std::vector<uint8_t>(4);
	std::uint8_t mask = 0x0F;
	for (std::size_t i = 0; i < 4; i++) {
		instructions[i] = (instruction >> ((3 - i) * 4)) & mask;
	}
	return instructions;
}

void CPU::Run() {
	while (PC < 644) {
		uint16_t instruction = Fetch();
		std::vector<uint8_t> instructions = Decode(instruction);
		uint8_t nibble1 = instructions[0], nibble2 = instructions[1], nibble3 = instructions[2], nibble4 = instructions[3];
		uint8_t A = nibble1;
		uint8_t X = nibble2;
		uint8_t Y = nibble3;
		uint8_t N = nibble4;
		uint8_t NN = (nibble3 << 4) | nibble4;
		uint16_t NNN = (nibble2 << 8) | (nibble3 << 4) | nibble4;
		std::cout << PC - 2 << " " << instruction << " " << + nibble1 << " " << +nibble2 << " " << +nibble3 << " " << +nibble4 << " " << "\n";
	}
}

