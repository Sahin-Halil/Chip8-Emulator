#include "CPUTileMapData.h"
#include <iostream>

CPUTileMapData::CPUTileMapData() {
	Quit = false; // Game loop is initially on (hence this is false)
	V = std::vector<uint8_t>(16); // 16 empty registers
	// Initialise all values in keys array to false
	for (std::size_t i = 0; i < 16; i++) {
		keysDown[i] = false;
	}
	resetKeyUps(); // Initialise all key ups to true
}

// Check if user clicked to exit
bool CPUTileMapData::getExitStatus() {
	return Quit;
}

// Set quit to its new status (user may have chose to close game)
void CPUTileMapData::setExitStatus(bool quitStatus) {
	Quit = quitStatus;
}

// Get one of the chosen variable registers (0-F)
uint8_t CPUTileMapData::getVRegister(std::size_t vRegister) {
	if (0 <= vRegister && vRegister < 16) {
		return V[vRegister];
	}
	else {
		std::cout << "Error: Invalid variable register access in get method" << "\n";
		return 0;
	}
}

// Set one of the registers to its new value
void CPUTileMapData::setVRegister(std::size_t vRegister, uint8_t registerData) {
	if (0 <= vRegister && vRegister < 16) {
		V[vRegister] = registerData;
	}
	else {
		std::cout << "Error: Invalid variable register access in set method" << "\n";
	}
}

// Get current key status (if pressed or not)
bool CPUTileMapData::getKeyPress(std::size_t keyPressIndex) {
	if (0 <= keyPressIndex  && keyPressIndex < 16) {
		return keysDown[keyPressIndex];
	}
	else {
		std::cout << "Error: Invalid key access in get method" << "\n";
		return 0;
	}
}

// Set key to true or false if pressed 
void CPUTileMapData::setKeyPress(std::size_t keyPressIndex, bool keyPress) {
	if (0 <= keyPressIndex && keyPressIndex < 16) {
		// set to true if user released key
		if (keyPress == false) {
			keysUp[keyPressIndex] = true;
		}
		keysDown[keyPressIndex] = keyPress;
	}
	else {
		std::cout << "Error: Invalid key access in set method" << "\n";
	}
}

// Reset all keys that have been released after sometime 
void CPUTileMapData::resetKeyUps() {
	for (std::size_t i = 0; i < 16; i++) {
		keysUp[i] = false;
	}
}

// check if key has been released
uint8_t CPUTileMapData::checkKeyUp(std::size_t keyUpIndex) {
	if (0 <= keyUpIndex && keyUpIndex < 16) {
		if (keysUp[keyUpIndex] == true) {
			return (uint8_t) keyUpIndex;
		}
	}
	else {
		std::cout << "Error: Invalid key access in key up method" << "\n";
	}
	return 255; // no key was released (or invalid key up index)
}
