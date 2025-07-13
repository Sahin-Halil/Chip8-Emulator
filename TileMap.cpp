#include "TileMap.h"
#include <iostream>

// Setups tilemap and game window
TileMap::TileMap() {
	// Checks if the SDL library is initialised and working
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("Couldn't initialise SDL: %s\n", SDL_GetError());
		return;
	}

	// Creating and checking window was created
	window = SDL_CreateWindow("Just a chill dude", WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	if (!window) {
		SDL_Log("Couldn't create window: %s\n", SDL_GetError());
		return;
	}

	// Creating and checking renderer was created
	renderer = SDL_CreateRenderer(window, NULL);
	if (!renderer) {
		SDL_Log("Couldn't create renderer: %s\n", SDL_GetError());
		return;
	}

	// Contents of game window will be black or white
	whiteTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, TEXTURE_SIZE, TEXTURE_SIZE);
	blackTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, TEXTURE_SIZE, TEXTURE_SIZE);

	// Checks to see if the texture was created
	if (!whiteTexture) {
		SDL_Log("Couldn't create white texture: %s\n", SDL_GetError());
		return;
	}

	if (!blackTexture) {
		SDL_Log("Couldn't create black texture: %s\n", SDL_GetError());
		return;
	}
	
	// Setting the colour of each texture to their respective colours e.g. white for white texture
	SDL_SetRenderTarget(renderer, whiteTexture);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderTarget(renderer, blackTexture);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	// Reseting renderer back to main game window
	SDL_SetRenderTarget(renderer, NULL);

	// Initialising all values in tilemap to false, false = black and true = white
	for (std::size_t i = 0; i < TILEMAP_HEIGHT; i++) {
		for (std::size_t j = 0; j < TILEMAP_WIDTH; j++) {
			tileMap[i][j] = false;
		}
	}
}

// Updates tilemap with a given starting (x, y), size and contents to update tilemap with
void TileMap::updateMap(std::size_t x, std::size_t y, std::size_t N, const std::vector<std::vector<bool>>& updateArea) {
	// Set x in range 0 - 63 and make sure it doesn't go off edge of screen
	std::size_t x_start = x % TILEMAP_WIDTH;
	std::size_t x_end = (x_start + 8 < TILEMAP_WIDTH) ? x_start + 8 : TILEMAP_WIDTH;
	
	// Set y in range 0 - 32 and make sure it doesn't go off edge of screen
	std::size_t y_start = y % TILEMAP_HEIGHT;
	std::size_t y_end = (y_start + N < TILEMAP_HEIGHT) ? y_start + N : TILEMAP_HEIGHT;

	// Both tilemap and updated portion are 2D arrays
	// Two pointers for each array are used to track current index
	auto updateAreaRow = updateArea.begin();
	for (std::size_t i = y_start; i < y_end; i++) {
		auto updateAreaCol = updateAreaRow->begin();
		for (std::size_t j = x_start; j < x_end; j++) {
			// Value of tilemap is set to either true or false
			tileMap[i][j] ^= *(updateAreaCol);
			updateAreaCol++;
		}
		updateAreaRow ++;
	}
}

// Nested loop to output contents of tilemap to game window
void TileMap::Draw() {
	for (std::size_t i = 0; i < TILEMAP_HEIGHT; i++) {
		for (std::size_t j = 0; j < TILEMAP_WIDTH; j++) {
			// rectangle is used to help set position of texture within game window
			textureRect = { (float) j * RECT_SIZE, (float) i * RECT_SIZE, RECT_SIZE, RECT_SIZE};
			std::cout << tileMap[i][j] << " ";
			
			// If cell in tilemap is set to true, then white is shown, else black
			if (tileMap[i][j] == true) {
				SDL_RenderTexture(renderer, whiteTexture, NULL, &textureRect);
			}
			else {
				SDL_RenderTexture(renderer, blackTexture, NULL, &textureRect);
			}
		}
		std::cout << '\n';
	}
	// Outputs updated tilemap to game window
	SDL_RenderPresent(renderer);
}

// Destroys all game window relevant attributes in order to prevent memory leaks
void TileMap::Destroy() {
	// These attributes need to be manually deleted when terminating program
	SDL_DestroyTexture(whiteTexture);
	SDL_DestroyTexture(blackTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	// End program once all necessary attributes have been destroyed
	SDL_Quit();
}