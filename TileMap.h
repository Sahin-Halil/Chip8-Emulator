#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#define WINDOW_WIDTH 64 * 10
#define WINDOW_HEIGHT 32 * 10
#define TILEMAP_WIDTH 64 
#define TILEMAP_HEIGHT 32 
#define TEXTURE_SIZE 10
#define RECT_SIZE 10

class TileMap
{
	private:
		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Texture* whiteTexture;
		SDL_Texture* blackTexture;
		SDL_FRect textureRect;
		bool tileMap[TILEMAP_HEIGHT][TILEMAP_WIDTH];

	public:
		TileMap();
		void updateMap();
		void Draw();
		void Destroy();
};

