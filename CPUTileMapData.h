#pragma once
#include <vector>

struct CPUTileMapData {
	private:
		// Shared Attributes
		bool quit;
		std::vector<uint8_t> V;

	public:
		CPUTileMapData(); // Initialises shared attributes

		// Getter and setter for quit attribute
		bool getExitStatus();
		void setExitStatus(bool quitStatus);

		// Getter and setter for 16 variable registers
		uint8_t getVRegister(std::size_t vRegister);
		void setVRegister(std::size_t vRegister, uint8_t registerData);
};

