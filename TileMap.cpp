#include "TileMap.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <vector>

TileMap::TileMap() {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("Couldn't initialise SDL: %s\n", SDL_GetError());
		return;
	}

	window = SDL_CreateWindow("Just a chill dude", WINDOW_WIDTH, WINDOW_HEIGHT, 0);

	if (!window) {
		SDL_Log("Couldn't create window: %s\n", SDL_GetError());
		return;
	}

	renderer = SDL_CreateRenderer(window, NULL);

	if (!renderer) {
		SDL_Log("Couldn't create renderer: %s\n", SDL_GetError());
		return;
	}

	whiteTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, TEXTURE_SIZE, TEXTURE_SIZE);
	blackTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, TEXTURE_SIZE, TEXTURE_SIZE);

	if (!whiteTexture) {
		SDL_Log("Couldn't create white texture: %s\n", SDL_GetError());
		return;
	}

	if (!blackTexture) {
		SDL_Log("Couldn't create black texture: %s\n", SDL_GetError());
		return;
	}
	
	SDL_SetRenderTarget(renderer, whiteTexture);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderTarget(renderer, blackTexture);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderTarget(renderer, NULL);

	for (std::size_t i = 0; i < TILEMAP_HEIGHT; i++) {
		for (std::size_t j = 0; j < TILEMAP_WIDTH; j++) {
			tileMap[i][j] = false;
		}
	}
}

void TileMap::Draw() {
	for (std::size_t i = 0; i < TILEMAP_HEIGHT; i++) {
		for (std::size_t j = 0; j < TILEMAP_WIDTH; j++) {
			textureRect = { (float) j * RECT_SIZE, (float) i * RECT_SIZE, RECT_SIZE, RECT_SIZE};
			if (tileMap[i][j] == true) {
				SDL_RenderTexture(renderer, whiteTexture, NULL, &textureRect);
			}
			else {
				SDL_RenderTexture(renderer, blackTexture, NULL, &textureRect);
			}
		}
	}
	SDL_RenderPresent(renderer);
}



void TileMap::Destroy() {
	SDL_DestroyTexture(whiteTexture);
	SDL_DestroyTexture(blackTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
}