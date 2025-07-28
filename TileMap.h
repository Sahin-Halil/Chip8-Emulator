#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <Memory>
#include "CPUTileMapData.h"

// Constants for TileMap
#define WINDOW_WIDTH 64 * 10
#define WINDOW_HEIGHT 32 * 10
#define TILEMAP_WIDTH 64 
#define TILEMAP_HEIGHT 32 
#define TEXTURE_SIZE 10
#define RECT_SIZE 10

class TileMap
{
	private:
		// Game window/tilemap essentials 
		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Texture* whiteTexture;
		SDL_Texture* blackTexture;
		SDL_FRect textureRect;
		bool tileMap[TILEMAP_HEIGHT][TILEMAP_WIDTH];

		// Game loop essentials
		int frameRate;
		uint64_t timeBefore;

		// Shared Attributes
		std::shared_ptr<CPUTileMapData> Chip8SD;

	public:
		TileMap(std::shared_ptr<CPUTileMapData> Chip8sd); // Initialises tilemap and game window
		void updateMap(std::size_t x, std::size_t y, std::size_t N, const std::vector<std::vector<bool>>& updateArea); // Takes starting positions, size and data to update tilemap with
		void Draw(); // Ouputs latest contents of tilemap to game window
		void resetMap(); // Resets all pixels on tilemap back to false (off)
		void Destroy(); // Destroys game window during code termination
		void remainingTime(); // Wait until time is up before starting next loop cycle (frame)
		void getEvent(); // Get event from user
};

