#include "CPUTileMapData.h"

CPUTileMapData::CPUTileMapData() {
	quit = false;
	V = std::vector<uint8_t>(16);
}

bool CPUTileMapData::getExitStatus() {
	return quit;
}

void CPUTileMapData::setExitStatus(bool quitStatus) {
	quit = quitStatus;
}

uint8_t CPUTileMapData::getVRegister(std::size_t vRegister) {
	return V[vRegister];
}

void CPUTileMapData::setVRegister(std::size_t vRegister, uint8_t registerData) {
	V[vRegister] = registerData;
}