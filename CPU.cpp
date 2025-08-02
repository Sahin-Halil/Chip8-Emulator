#include "CPU.h"
#include <iostream>

// Initialise each CPU attribute
CPU::CPU(std::unique_ptr<Memory> ram, std::unique_ptr<TileMap> chip8tm, std::shared_ptr<CPUTileMapData> chip8sd) {
	// Initialise registers
	PC = 512;
	I = 0;
	
	// Move objects into respective pointers
	RAM = std::move(ram);
	Chip8TM = std::move(chip8tm);
	Chip8SD = std::move(chip8sd);
}

// Get next two bytes from memory, then increment PC, merge the two bytes and return it (this is the instruction)
uint16_t CPU::Fetch() {
	// Retrive next two bytes
	uint8_t firstByte = RAM->getMemory(getPC());
	uint8_t secondByte = RAM->getMemory(getPC() + 1);
	
	setPC(getPC() + 2); // Increment PC 

	// Merge the bytes into one, then return it
	uint16_t instruction = (firstByte << 8) | secondByte;
	return instruction;
}

// Breakdown 16 bit instruction into 4 nibbles (each nibble stored in its own 
std::vector<uint8_t> CPU::Decode(uint16_t instruction) {
	std::vector<uint8_t> instructions = std::vector<uint8_t>(4); // Array to store each nibble of instruction
	std::uint8_t mask = 0x0F; // Used to get last 4 bits of binary number

	// Loop 4 times, each iteration for a differnet nibble in instruction
	for (std::size_t i = 0; i < 4; i++) {
		instructions[i] = (instruction >> ((3 - i) * 4)) & mask; // shift instruction and mask to get and store current nibble
	}

	return instructions; 
}

void CPU::Execute(const std::vector<uint8_t>& currentInstructions) {
	uint8_t nibble1 = currentInstructions[0], nibble2 = currentInstructions[1], nibble3 = currentInstructions[2], nibble4 = currentInstructions[3];

	// Standard variables that are used in many different instructions
	uint8_t X = nibble2; // The second nibble. Used to look up one of the 16 registers (VX) from V0 through VF.
	uint8_t Y = nibble3; // The third nibble.Also used to look up one of the 16 registers(VY) from V0 through VF.
	uint8_t N = nibble4; // The fourth nibble. A 4-bit number.
	uint8_t NN = (nibble3 << 4) | nibble4; // The second byte (third and fourth nibbles). An 8-bit immediate number.
	uint16_t NNN = (nibble2 << 8) | (nibble3 << 4) | nibble4; // The second, third and fourth nibbles. A 12-bit immediate memory address.

	//std::cout << getPC() - 2 << " " << instruction << " " << + nibble1 << " " << +nibble2 << " " << +nibble3 << " " << +nibble4 << " " << "\n";

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
	// FX55 (modern version: takes contents of registers V0-VX, and stores it in memory starting from I)
	// FX65 (modern version: takes contents of memory starting from I, and stores it in register V0-VX)
	// FX33 (Break a number into digits and add it to memory starting from I)

	// 9XY0 (Skip Instruction)
	// FX1E (modern version: VX is addedd to I, VF set to 1 if overflow)

	// Switch cases, each leading to a different instruction the emulator can execute
	switch (nibble1) {
		// DXYN (display/draw)
		case 0xD: {
			// Get sprite data and output on game window 
			std::vector<std::vector<bool>> spriteDataBool = getDrawingData(N);
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
								// 00E0 (clear screen)
								case 0x0:
									Chip8TM->resetMap();
									break;
								}
							break;
						}
					break;
				}
			break;
		// 1NNN (jump)
		case 0x1:
			setPC(NNN);
			break;
		// 6XNN (set register VX)
		case 0x6:
			Chip8SD->setVRegister(X, NN);
			break;
		// 7XNN (add value to register VX)
		case 0x7: {
			uint8_t currRV = Chip8SD->getVRegister(X);
			Chip8SD->setVRegister(X, currRV + NN);
			break;
		}
		// ANNN (set index register I)
		case 0xA:
			setI(NNN);
			break;
		// 3XNN (skip Instruction)
		case 0x3:
			if (Chip8SD->getVRegister(X) == NN) {
				setPC(getPC() + 2);
			}
			break;
		// 4XNN (skip Instruction)
		case 0x4:
			if (Chip8SD->getVRegister(X) != NN) {
				setPC(getPC() + 2);
			}
			break;
		case 0x5:
			switch (nibble4) {
				// 5XY0 (skip Instruction)
				case 0x0:
					if (Chip8SD->getVRegister(X) == Chip8SD->getVRegister(Y)) {
						setPC(getPC() + 2);
					}
					break;
			}
			break;
		//case 0x9:
		//	//std::cout << "Here" <<"\n";
		//	switch (nibble4) {
		//		case 0x0:
		//			if (Chip8SD->getVRegister(X) != Chip8SD->getVRegister(Y)) {
		//				setPC(getPC() + 2);
		//			}
		//			break;
		//	}
		//	break;
		case 0x8:
			switch (nibble4) {
				// 8XY5 (store in VX, VX - VY, and modified VF)
				case 0x5: {
					//std::cout << "Here" << "\n";
					Chip8SD->setVRegister(0xF, 1);
					uint8_t VX = Chip8SD->getVRegister(X);
					uint8_t VY = Chip8SD->getVRegister(Y);
					uint8_t difference = VX - VY;
					if (VX < VY) {
						// std::cout << "here" << "\n";
						// difference = VY - VX;
						Chip8SD->setVRegister(0xF, 0);
					}
					Chip8SD->setVRegister(X, difference);
					break;
				}
				// 8XY7 (store in VX : VY - VX, and modified VF)
				case 0x7: {
					Chip8SD->setVRegister(0xF, 1);
					uint8_t VX = Chip8SD->getVRegister(X);
					uint8_t VY = Chip8SD->getVRegister(Y);
					uint8_t difference = VY - VX;
					if (VY < VX) {
						// std::cout << "here" << "\n";
						// difference = VX - VY;
						Chip8SD->setVRegister(0xF, 0);
					}
					Chip8SD->setVRegister(X, difference);
					break;
				}
				// 8XY1 (store in VX: VX or VY)
				case 0x1: {
					uint8_t VX = Chip8SD->getVRegister(X);
					uint8_t VY = Chip8SD->getVRegister(Y);
					uint8_t bitwiseOR = VX | VY;
					Chip8SD->setVRegister(X, bitwiseOR);
					break;
				}
				// 8XY2 (store in VX : VX and VY)
				case 0x2: {
					uint8_t VX = Chip8SD->getVRegister(X);
					uint8_t VY = Chip8SD->getVRegister(Y);
					uint8_t bitwiseAND = VX & VY;
					Chip8SD->setVRegister(X, bitwiseAND);
					break;
				}
				// 8XY3 (store in VX: VX XOR VY)
				case 0x3: {
					uint8_t VX = Chip8SD->getVRegister(X);
					uint8_t VY = Chip8SD->getVRegister(Y);
					uint8_t bitwiseXOR = VX ^ VY;
					Chip8SD->setVRegister(X, bitwiseXOR);
					break;
				}
				// 8XYE (modern version: shifted VX to left, and modified VF)
				case 0xE: {
					uint8_t VX = Chip8SD->getVRegister(X);
					uint8_t MSB = 0x80 & VX;
					VX <<= 1;
					MSB >>= 7;
					Chip8SD->setVRegister(X, VX);
					Chip8SD->setVRegister(0xF, MSB);
					break;
				}
				// 8XY6 (modern version: shifted VX to right, and modified VF)
				case 0x6: {
					uint8_t VX = Chip8SD->getVRegister(X);
					uint8_t LSB = 0x01 & VX;
					VX >>= 1;
					Chip8SD->setVRegister(X, VX);
					Chip8SD->setVRegister(0xF, LSB);
					break;
				}
			}
			break;
		case 0xF:
			switch (nibble3) {
				case 0x5:
					switch (nibble4) {
						// FX55 (modern version: takes contents of registers V0-VX, and stores it in memory starting from I)
						case 0x5:
							for (std::size_t i = 0; i <= X; i++) {
								uint8_t V = Chip8SD->getVRegister(i);
								RAM->updateMemory(getI() + i, V);
							}
							break;
					}
					break;
				case 0x6:
					switch (nibble4) {
						// FX65 (modern version: takes contents of memory starting from I, and stores it in register V0-VX)
						case 0x5:
							for (std::size_t i = 0; i <= X; i++) {
								uint8_t data = RAM->getMemory(getI() + i);
								Chip8SD->setVRegister(i, data);
							}
							break;
						}
					break;
				case 0x3:
					switch (nibble4) {
						// FX33 (Break a number into digits and add it to memory starting from I)
						case 0x3: {
							uint8_t VX = Chip8SD->getVRegister(X);
							for (std::size_t i = 3; i > 0; i--) {
								uint8_t digit = VX % 10;
								RAM->updateMemory(getI() + i - 1, digit);
								VX /= 10;
							}
							break;
						}
					}
					break;
				case 0x1:
					switch (nibble4) {
						// FX1E (modern version: VX is addedd to I, VF set to 1 if overflow)
						case 0xE: {
							uint8_t VX = Chip8SD->getVRegister(X);
							if (I + VX > 0xFFF) {
								Chip8SD->setVRegister(0xF, 1);
							}
							setI(getI() + VX);
							break;
						}
					}
					break;
				}
				break;
		// Unknown instruction (useful for debugging)
		default:
			std::cout << "ERROR" << "\n";
			break;
	}
}

// Run emulator
void CPU::Run() {
	// Loop until user clicks exit button
	while (Chip8SD->getExitStatus() == false) {
		Chip8TM->getEvent(); // Check if user triggered an event
		Chip8TM->remainingTime(); // Run emulator at set speed
		//Chip8TM->Draw();

		// Fetch - Decode - Execute
		uint16_t instruction = Fetch();
		std::vector<uint8_t> instructions = Decode(instruction);
		Execute(instructions);
	}

	Chip8TM->Destroy(); // Destroy game contents once emulation ends
}

// Get sprite data and put it into a 2D bool array
std::vector<std::vector<bool>> CPU::getDrawingData(uint8_t N) {
	// Declare arrays to retrieve sprite data
	std::vector<uint8_t> spriteDataBinary = std::vector<uint8_t>(N); 
	std::vector<std::vector<bool>> spriteDataBool(N, std::vector<bool>(8, false));

	// Loop through N entries of memory and add to array
	for (size_t i = 0; i < N; i++) {
		uint8_t spriteData = RAM->getMemory(getI() + i);
		spriteDataBinary[i] = spriteData;
	}

	// Break binary values into bits and add each to specific part of 2D boolean array
	for (std::size_t i = 0; i < N; i++) {
		std::uint8_t val = spriteDataBinary[i];
		std::uint8_t mask = 0x80; 
		for (std::size_t j = 0; j < 8; j++) {
			spriteDataBool[i][j] = mask & val; // Mask a specific bit of a binary value
			mask >>= 1;
			//std::cout << spriteDataBool[i][j];
		}
		// std::cout << "\n";
	}

	return spriteDataBool;
}

// Return current PC Value
uint16_t CPU::getPC() {
	return PC;
}

// Check new PC value is in range before setting it
void CPU::setPC(uint16_t newPC) {
	if (0 <= newPC  && newPC < 4096) {
		PC = newPC;
	}
	else {
		std::cout << "Error: New PC value out of bounds" << "\n";
	}
}

// Return current I value
uint16_t CPU::getI() {
	return I;
}

// Check new I value is in range before setting it
void CPU::setI(uint16_t newI) {
	if (0 <= newI && newI < 4096) {
		I = newI;
	}
	else {
		std::cout << "Error: New I value out of bounds" << "\n";
	}
}

