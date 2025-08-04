#include "CPU.h"
#include <iostream>

CPU::CPU(std::unique_ptr<Memory> ram, std::unique_ptr<TileMap> chip8tm, std::shared_ptr<CPUTileMapData> chip8sd) {
	PC = 512;
	I = 0;
	RAM = std::move(ram);
	Chip8TM = std::move(chip8tm);
	Chip8SD = std::move(chip8sd);
}

uint16_t CPU::Fetch() {
	uint8_t firstByte = RAM->getMemory(PC);
	uint8_t secondByte = RAM->getMemory(PC + 1);
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
	while (Chip8SD->getExitStatus() == false) {
		Chip8TM->getEvent();
		Chip8TM->remainingTime();
		//Chip8TM->Draw();
		uint16_t instruction = Fetch();
		std::vector<uint8_t> instructions = Decode(instruction);
		uint8_t nibble1 = instructions[0], nibble2 = instructions[1], nibble3 = instructions[2], nibble4 = instructions[3];
		uint8_t X = nibble2;
		uint8_t Y = nibble3;
		uint8_t N = nibble4;
		uint8_t NN = (nibble3 << 4) | nibble4;
		uint16_t NNN = (nibble2 << 8) | (nibble3 << 4) | nibble4;
		std::cout << PC - 2 << " " << instruction << " " << + nibble1 << " " << +nibble2 << " " << +nibble3 << " " << +nibble4 << " " << "\n";
		// instructions done so far
		// DXYN (display/draw)
		// 00E0 (clear screen)
		// 1NNN (jump)
		// 6XNN (set register VX)
		// 7XNN (add value to register VX)
		// ANNN (set index register I)

		// 3XNN (skip Instruction)
		// 4XNN (skip Instruction)
		// 5XY0 (skip Instruction)
		// 8XY5 (store in VX, VX - VY, and modified VF)
		// 8XY7 (store in VX: VY - VX, and modified VF)
		// 8XY1 (store in VX: VX or VY)
		// 8XY2 (store in VX: VX and VY)
		// 8XY3 (store in VX: VX XOR VY)
		// 8XYE (modern version: shifted VX to left, and modified VF)
		// 8XY6 (modern version: shifted VX to right, and modified VF)
		// FX55 (takes contents of registers V0-VX, and stores it in memory starting from I)
		// FX65 (takes contents of memory starting from I, and stores it in register V0-VX)
		// FX33 (Break a number into digits and add it to memory starting from I)
		 
		// 9XY0 (Skip Instruction)
		switch (nibble1) {
			case 0xD: {
				// Put these in its own method later on
				std::vector<uint8_t> spriteDataBinary = std::vector<uint8_t>(N);
				std::vector<std::vector<bool>> spriteDataBool(N, std::vector<bool>(8, false));
				for (size_t i = 0; i < N; i++) {
					uint8_t spriteData = RAM->getMemory(I + i);
					spriteDataBinary[i] = spriteData;
				}	
				for (std::size_t i = 0; i < N; i++) {
					std::uint8_t val = spriteDataBinary[i];
					std::uint8_t mask = 0x80;
					for (std::size_t j = 0; j < 8; j++) {
						spriteDataBool[i][j] = mask & val;
						mask >>= 1;
						std::cout << spriteDataBool[i][j];
					}
					std::cout << "\n";
				}
				Chip8TM->updateMap(X, Y, N, spriteDataBool);
				//std::cout << "Here" << "\n";
				Chip8TM->Draw();
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
										Chip8TM->resetMap();
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
				Chip8SD->setVRegister(X, NN);
				break;
			case 0x7:
				{
				//std::cout << "Here" << +X << "\n";
				uint8_t currRV = Chip8SD->getVRegister(X);
				Chip8SD->setVRegister(X, currRV + NN);
				break;
				}
			case 0xA:
				//std::cout << "Here" << +I << "\n";
				I = NNN;
				break;
			case 0x3:
				//std::cout << "Here" << +I << "\n";
				if (Chip8SD->getVRegister(X) == NN) {
					std::cout << "Here" << "\n";
					PC += 2;
				}
				break;
			case 0x4:
				//std::cout << "Here" << +I << "\n";
				if (Chip8SD->getVRegister(X) != NN) {
					PC += 2;
				}
				break;
			case 0x5:
				//std::cout << "Here" << +I << "\n";
				switch (nibble4) {
					case 0x0:
						if (Chip8SD->getVRegister(X) == Chip8SD->getVRegister(Y)) {
							PC += 2;
						}
						break;
				}
			 	break;
			//case 0x9:
			//	//std::cout << "Here" <<"\n";
			//	switch (nibble4) {
			//		case 0x0:
			//			if (Chip8SD->getVRegister(X) != Chip8SD->getVRegister(Y)) {
			//				PC += 2;
			//			}
			//			break;
			//	}
			//	break;
			case 0x8:
				switch (nibble4) {
					case 0x5: {
						//std::cout << "Here" << "\n";
						Chip8SD->setVRegister(0xF, 1);
						uint8_t VX = Chip8SD->getVRegister(X);
						uint8_t VY = Chip8SD->getVRegister(Y);
						uint8_t difference = VX - VY;
						if (VX < VY) {
							std::cout << "here" << "\n";
							//difference = VY - VX;
							Chip8SD->setVRegister(0xF, 0);
						}
						Chip8SD->setVRegister(X, difference);
						break;
					}
					case 0x7: {
						//std::cout << "Here" << "\n";
						Chip8SD->setVRegister(0xF, 1);
						uint8_t VX = Chip8SD->getVRegister(X);
						uint8_t VY = Chip8SD->getVRegister(Y);
						uint8_t difference = VY - VX;
						if (VY < VX) {
							std::cout << "here" << "\n";
							//difference = VX - VY;
							Chip8SD->setVRegister(0xF, 0);
						}
						Chip8SD->setVRegister(X, difference);
						break;
					}
					case 0x1: {
						uint8_t VX = Chip8SD->getVRegister(X);
						uint8_t VY = Chip8SD->getVRegister(Y);
						uint8_t bitwiseOR = VX | VY;
						Chip8SD->setVRegister(X, bitwiseOR);
						break;
					}
					case 0x2: {
						uint8_t VX = Chip8SD->getVRegister(X);
						uint8_t VY = Chip8SD->getVRegister(Y);
						uint8_t bitwiseAND = VX & VY;
						Chip8SD->setVRegister(X, bitwiseAND);
						break;
					}
					case 0x3: {
						uint8_t VX = Chip8SD->getVRegister(X);
						uint8_t VY = Chip8SD->getVRegister(Y);
						uint8_t bitwiseXOR = VX ^ VY;
						Chip8SD->setVRegister(X, bitwiseXOR);
						break;
					}
					case 0xE: {
						uint8_t VX = Chip8SD->getVRegister(X);
						uint8_t MSB = 0x80 & VX;
						VX <<= 1;
						MSB >>= 7;
						Chip8SD->setVRegister(X, VX);
						Chip8SD->setVRegister(0xF, MSB);
						break;
					}
					case 0x6: {
						uint8_t VX = Chip8SD->getVRegister(X);
						uint8_t LSB = 0x01 & VX;
						VX >>= 1;
						Chip8SD->setVRegister(X, VX);
						Chip8SD->setVRegister(0xF, LSB);
						break;
					}
					break;
				}
				break;
			case 0xF:
				switch (nibble3) {
					case 0x5:
						switch (nibble4) {
							case 0x5:
								std::cout << "instruction: " << "FX55" << "\n";
								for (std::size_t i = 0; i <= X; i++) {
									uint8_t V = Chip8SD->getVRegister(i);
									std::cout << +V << "\n";
									RAM->updateMemory(I + i, V);
								}
								break;
						}
						break;
					case 0x6:
						switch (nibble4) {
							case 0x5:
								std::cout << "instruction: " << "FX65" << "\n";
								for (std::size_t i = 0; i <= X; i++) {
									uint8_t data = RAM->getMemory(I + i);
									std::cout << +data << "\n";
									Chip8SD->setVRegister(i, data);
								}
								break;
						}
						break;
					case 0x3:
						switch (nibble4) {
							case 0x3: {
								std::cout << "instruction: " << "FX33" << "\n";
								// I, I + 1, I + 2
								// I + 1, I + 2, I + 3
								uint8_t VX = Chip8SD->getVRegister(X);
								for (std::size_t i = 3; i > 0; i--) {
									uint8_t digit = VX % 10;
									RAM->updateMemory(I + i - 1, digit);
									VX /= 10;
								}
								break;
							}
						}
						break;
					case 0x1: 
						switch (nibble4) {
							case 0xE:
								I += Chip8SD->getVRegister(X);
								break;
						}
						break;
				}
				break;
			default:
				std::cout << "ERROR" << "\n";
				break;
		}
	}

	Chip8TM->Destroy();
}

