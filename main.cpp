// Chip8-Emulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "loadROM.h"
#include "Memory.h"
#include "CPU.h"
#include "TileMap.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>


#define WINDOW_WIDTH 64 * 10
#define WINDOW_HEIGHT 32 * 10

int main(int argc, char* argv[])
{
    SDL_Window* window;                    // Declare a pointer
    bool done = false;                     // Game condition

    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL3

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "Just a chill dude",          // window title
        WINDOW_WIDTH,                               // width, in pixels
        WINDOW_HEIGHT,                               // height, in pixels
        0                  // flags - see below
    );

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    SDL_Texture* whiteTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 10, 10);
    SDL_Texture* blackTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 10, 10);

    SDL_SetRenderTarget(renderer, whiteTexture);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderTarget(renderer, blackTexture);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderTarget(renderer, NULL);

    bool gameMap[WINDOW_HEIGHT / 10][WINDOW_WIDTH / 10];
    for (std::size_t i = 0; i < WINDOW_HEIGHT / 10; i++) {
        for (std::size_t j = 0; j < WINDOW_WIDTH / 10; j++) {
            gameMap[i][j] = false;
        }
    }

    gameMap[0][0] = true;
    gameMap[31][63] = true;
    gameMap[20][30] = true;
    gameMap[30][20] = true;
    gameMap[3][5] = true;
    gameMap[30][50] = true;
    gameMap[16][31] = true;
    gameMap[20][20] = true;
    gameMap[28][52] = true;

    for (std::size_t i = 0; i < WINDOW_HEIGHT / 10; i++) {
        for (std::size_t j = 0; j < WINDOW_WIDTH / 10; j++) {
            SDL_FRect textureRect = { (float) j*10, (float) i*10, 10, 10 };
            if (gameMap[i][j] == true) {
                //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderTexture(renderer, whiteTexture, NULL, &textureRect);
            }
            else {
                //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderTexture(renderer, blackTexture, NULL, &textureRect);
            }
            //SDL_SetRenderScale(renderer, 1, 1);
            //SDL_RenderPoint(renderer, j, i);

        }
    }
    SDL_RenderPresent(renderer);
    while (!done) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_EVENT_QUIT:
                done = true;
                break;
            }
        }
    }

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Destroy renderer
    SDL_DestroyRenderer(renderer);

    // Destroy Textures
    SDL_DestroyTexture(whiteTexture);
    SDL_DestroyTexture(blackTexture);

    // Clean up
    SDL_Quit();
    return 0;

    /* This is what i normally work by when designing the interface of a non - template function:

     Pass by value if the function does not want to modify the parameter and the value is cheap to copy(int, double, float, char, bool, etc... Notice that std::string, std::vector, and the rest of the containers in the standard library are NOT)

     Pass by const pointer if the value is expensive to copy and the function does not want to modify the value pointed to and NULL is a value that the function handles.

     Pass by non - const pointer if the value is expensive to copy and the function wants to modify the value pointed to and NULL is a value that the function handles.

     Pass by const reference when the value is expensive to copy and the function does not want to modify the value referred to and NULL would not be a valid value if a pointer was used instead.

     Pass by non - const reference when the value is expensive to copy and the function wants to modify the value referred to and NULL would not be a valid value if a pointer was used instead.*/

     /*uint8_t example1 = 254;
     uint8_t example2 = 30;
     uint16_t res = (example1 << 8) | example2;
     std::cout << +example1 << "\n";
     std::cout << +res << "\n";*/

     /*std::vector<uint8_t> data1 = {1, 2, 3, 4};
     uint16_t pc = 0;
     std::cout << +data1[pc] << " " << +data1[pc + 1] << "\n";
     pc += 2;
     std::cout << +data1[pc] << " " << +data1[pc + 1];*/


     /* std::vector<uint8_t> gameData = loadROM();

      Memory RAM;
      RAM.setMemory(gameData);
      RAM.printMemory();

      std::cout << +RAM.getMemory(516) << "\n";
      std::cout << +RAM.getMemory(517) << "\n";

      CPU chip8Processor(RAM);
      chip8Processor.Fetch();
      chip8Processor.Fetch();
      std::cout << +chip8Processor.Fetch();

      return 0;*/

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
