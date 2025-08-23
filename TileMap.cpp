#include "TileMap.h"
#include <iostream>

// Setups tilemap and game window
TileMap::TileMap(std::shared_ptr<CPUTileMapData> chip8sd) {
	// Checks if the SDL library is initialised and working
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
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
	resetMap();

	// Set audio spec
	SDL_AudioSpec audioSpec;
	audioSpec.format = SDL_AUDIO_F32;
	audioSpec.channels = 1;
	audioSpec.freq = 44100;

	// Open audio device
	stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &audioSpec, NULL, NULL);

	// Check to see if stream was created
	if (!stream) {
		SDL_Log("Couldn't create audio stream: %s\n", SDL_GetError());
		return;
	}

	// Unpause audio (usually off to begin with)
	SDL_ResumeAudioStreamDevice(stream);

	// Initialising Shared Data
	Chip8SD = std::move(chip8sd);
}

// Updates tilemap with a given starting (x, y), size and contents to update tilemap with
void TileMap::updateMap(std::size_t x, std::size_t y, std::size_t N, const std::vector<std::vector<bool>>& updateArea) {
	// Set x in range 0 - 63 and make sure it doesn't go off edge of screen
	std::size_t x_start = Chip8SD->getVRegister(x) % TILEMAP_WIDTH;
	std::size_t x_end = (x_start + 8 < TILEMAP_WIDTH) ? x_start + 8 : TILEMAP_WIDTH;
	
	// Set y in range 0 - 32 and make sure it doesn't go off edge of screen
	std::size_t y_start = Chip8SD->getVRegister(y) % TILEMAP_HEIGHT;
	//std::size_t y_end = (y_start + N < TILEMAP_HEIGHT) ? y_start + N : TILEMAP_HEIGHT;
	std::size_t y_end = y_start + N;
	//Chip8SD->setVRegister(0xF, 1);

	// Both tilemap and updated portion are 2D arrays
	// Two pointers for each array are used to track current index
	auto updateAreaRow = updateArea.begin();
	for (std::size_t i = y_start; i < y_end; i++) {
		auto updateAreaCol = updateAreaRow->begin();
		for (std::size_t j = x_start; j < x_end; j++) {
			// Value of tilemap is set to either true or false
			if (tileMap[i][j]){
				//Chip8SD->setVRegister(0xF, 0);
			}
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
			
			// If cell in tilemap is set to true, then white is shown, else black
			if (tileMap[i][j] == true) {
				SDL_RenderTexture(renderer, whiteTexture, NULL, &textureRect);
			}
			else {
				SDL_RenderTexture(renderer, blackTexture, NULL, &textureRect);
			}
			//std::cout << tileMap[i][j];
		}
		//std::cout << "\n";
	}
	// Outputs updated tilemap to game window
	SDL_RenderPresent(renderer);
}

// Nested loop to set every pixel in tilemap to false (off)
void TileMap::resetMap() {
	for (std::size_t i = 0; i < TILEMAP_HEIGHT; i++) {
		for (std::size_t j = 0; j < TILEMAP_HEIGHT; j++) {
			// tilemap pixel is reset on this line
			tileMap[i][j] = false;
		}
	}
}

// Destroys all game window relevant attributes in order to prevent memory leaks
void TileMap::Destroy() {
	// These attributes need to be manually deleted when terminating program
	SDL_DestroyAudioStream(stream);
	SDL_DestroyTexture(whiteTexture);
	SDL_DestroyTexture(blackTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	// End program once all necessary attributes have been destroyed
	SDL_Quit();
}

// Return the current event happening
void TileMap::getEvent() {
	SDL_Event e;
	std::vector <uint8_t> vx = { 0x20, 0x60, 0x20, 0x20, 0x70 };
	//Get event data
	while (SDL_PollEvent(&e) == true)
	{
		switch (e.type) {
			// checks if exit button is pressed	
			case SDL_EVENT_QUIT: 
				Chip8SD->setExitStatus(true); // This will set quit to true (game loop ends)
				break;
			// All possible key presses (0-F)
			case SDL_EVENT_KEY_DOWN:
				switch (e.key.scancode) {
					case SDL_SCANCODE_1:
						vx = { 0x20, 0x60, 0x20, 0x20, 0x70 };
						break;
					case SDL_SCANCODE_2:
						vx = { 0xF0, 0x10, 0xF0, 0x80, 0xF0 };
						break;
					case SDL_SCANCODE_3:
						vx = { 0xF0, 0x10, 0xF0, 0x10, 0xF0 };
						break;
					case SDL_SCANCODE_4:
						vx = { 0xF0, 0x80, 0x80, 0x80, 0xF0 };
						break;
					case SDL_SCANCODE_Q:
						vx = { 0x90, 0x90, 0xF0, 0x10, 0x10 };
						break;
					case SDL_SCANCODE_W:
						vx = { 0xF0, 0x80, 0xF0, 0x10, 0xF0 };
						break;
					case SDL_SCANCODE_E:
						vx = { 0xF0, 0x80, 0xF0, 0x90, 0xF0 };
						break;
					case SDL_SCANCODE_R:
						vx = { 0xE0, 0x90, 0x90, 0x90, 0xE0 };
						break;
					case SDL_SCANCODE_A:
						vx = { 0xF0, 0x10, 0x20, 0x40, 0x40 };
						break;
					case SDL_SCANCODE_S:
						vx = { 0xF0, 0x90, 0xF0, 0x90, 0xF0 };
						break;
					case SDL_SCANCODE_D:
						vx = { 0xF0, 0x90, 0xF0, 0x10, 0xF0 };
						break;
					case SDL_SCANCODE_F:
						vx = { 0xF0, 0x80, 0xF0, 0x80, 0xF0 };
						break;
					case SDL_SCANCODE_Z:
						vx = { 0xF0, 0x90, 0xF0, 0x90, 0x90 };
						break;
					case SDL_SCANCODE_X:
						vx = { 0xF0, 0x90, 0x90, 0x90, 0xF0 };
						break;
					case SDL_SCANCODE_C:
						vx = { 0xE0, 0x90, 0xE0, 0x90, 0xE0 };
						break;
					case SDL_SCANCODE_V:
						vx = { 0xF0, 0x80, 0xF0, 0x80, 0x80 };
						break;
					}
		}
	}
}
