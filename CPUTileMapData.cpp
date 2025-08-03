#include "CPUTileMapData.h"

CPUTileMapData::CPUTileMapData() {
	quit = false; // Game loop is initially on (hence this is false)
	V = std::vector<uint8_t>(16); // 16 empty registers
}

// Check if user clicked to exit
bool CPUTileMapData::getExitStatus() {
	return quit;
}

// Set quit to its new status (user may have chose to close game)
void CPUTileMapData::setExitStatus(bool quitStatus) {
	quit = quitStatus;
}

// Get one of the chosen variable registers (0-F)
uint8_t CPUTileMapData::getVRegister(std::size_t vRegister) {
	return V[vRegister];
}

// Set one of the registers to its new value
void CPUTileMapData::setVRegister(std::size_t vRegister, uint8_t registerData) {
	V[vRegister] = registerData;
}