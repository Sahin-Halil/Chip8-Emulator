#pragma once
#include <vector>

struct CPUTileMapData
{
	private:
		bool quit;
		std::vector<uint8_t> V;

	public:
		CPUTileMapData();
		bool getExitStatus();
		void setExitStatus(bool quitStatus);
		uint8_t getVRegister(std::size_t vRegister);
		void setVRegister(std::size_t vRegister, uint8_t registerData);
};

