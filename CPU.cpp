#include "CPU.h"
#include <iostream>

CPU::CPU(Memory& ram, TileMap& tileMap) {
	PC = 512;
	I = 0;
	RAM = ram;
	Chip8TM = tileMap;
	V = std::vector<uint8_t>(16);
	quit = false;
}

uint16_t CPU::Fetch() {
	uint8_t firstByte = RAM.getMemory(PC);
	uint8_t secondByte = RAM.getMemory(PC + 1);
	//std::cout << +firstByte << " " << +secondByte << "\n";
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
	while (quit == false) {
		Chip8TM.getEvent(quit);
		std::cout << quit;
		uint16_t instruction = Fetch();
		std::vector<uint8_t> instructions = Decode(instruction);
		uint8_t nibble1 = instructions[0], nibble2 = instructions[1], nibble3 = instructions[2], nibble4 = instructions[3];
		uint8_t X = nibble2;
		uint8_t Y = nibble3;
		uint8_t N = nibble4;
		uint8_t NN = (nibble3 << 4) | nibble4;
		uint16_t NNN = (nibble2 << 8) | (nibble3 << 4) | nibble4;
		//std::cout << PC - 2 << " " << instruction << " " << + nibble1 << " " << +nibble2 << " " << +nibble3 << " " << +nibble4 << " " << "\n";

		// instructions done so far
		// DXYN (display/draw)
		// 00E0 (clear screen)
		// 1NNN (jump)
		// 6XNN (set register VX)
		// (add value to register VX)
		// ANNN (set index register I)
		switch (nibble1) {
			case 0xD:
			{
				// Put these in its own method later on
				std::vector<uint8_t> spriteDataBinary = std::vector<uint8_t>(N);
				std::vector<std::vector<bool>> spriteDataBool(N, std::vector<bool>(8, false));
				for (size_t i = 0; i < N; i++) {
					uint8_t spriteData = RAM.getMemory(I + i);
					spriteDataBinary[i] = spriteData;
				}				
				for (std::size_t i = 0; i < N; i++) {
					std::uint8_t val = spriteDataBinary[i];
					std::uint8_t mask = 0x80;
					for (std::size_t j = 0; j < 8; j++) {
						spriteDataBool[i][j] = mask & val;
						mask >>= 1;
					}
				}
				Chip8TM.updateMap(V[X], V[Y], N, spriteDataBool);
				//std::cout << "Here" << "\n";
				Chip8TM.Draw();
				break;
			}
			case 0x0:
				switch (nibble2) {
					case 0x0:
						switch (nibble3) {
							case 0xE:
								switch (nibble4) {
									case 0x0:
										//std::cout << +A << " " << +X << " " << +Y << " " << +N << "\n";
										//std::cout << "Here" << "\n";
										Chip8TM.resetMap();
										break;
								}
								break;
						}
						break;
				}
				break;
			case 0x1:
				PC = NNN;
				break;
			case 0x6:
				//std::cout << "Here" << +X << "\n";
				V[X] = NN;
				break;
			case 0x7:
				//std::cout << "Here" << +X << "\n";
				V[X] += NN;
				break;
			case 0xA:
				//std::cout << "Here" << +I << "\n";
				I = NNN;
				break;
			default:
				std::cout << "ERROR" << "\n";
				break;
		}
	}
}

