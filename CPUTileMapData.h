#pragma once
#include <vector>

// Add a method for constructor which resets values in keys array (this may need to be called after every iteration of CPU loop to reset keys pressed)
// Add a key up in tilemap events method for when user lets go of input
// Decrease timers for key based instructions
// Release key with key up annd get rid of reset key method (since keys are reset when released)

struct CPUTileMapData {
	private:
		// Shared Attributes
		bool Quit;
		std::vector<uint8_t> V;
		bool keysDown[16];
		bool keysUp[16];

	public:
		CPUTileMapData(); // Initialises shared attributes

		// Getter and setter for quit attribute
		bool getExitStatus();
		void setExitStatus(bool quitStatus);

		// Getter and setter for 16 variable registers
		uint8_t getVRegister(std::size_t vRegister);
		void setVRegister(std::size_t vRegister, uint8_t registerData);

		// Getter and setter for key presses
		bool getKeyPress(std::size_t keyPressIndex);
		void setKeyPress(std::size_t keyPressIndex, bool KeyPress);

		void resetKeyUps(); // Reset all key ups
		uint8_t checkKeyUp(std::size_t keyPressIndex); // Check if key has been released
};

