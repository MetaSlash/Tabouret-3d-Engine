#include <SDL.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#include <chrono>
#include <iostream>
#include <thread>

#include "./Canvas/Canvas.hpp"
#include "constants.hpp"

void handler(int s) {
    std::cout << "signal caught : " << s << std::endl;
    exit(s);
}

int main(int argc, char* argv[]) {
    // 1. Initialize SDL and create a Window

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow(
        "Software Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    // The Renderer and Texture act as the "bridge" to show our raw pixels
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                                             SDL_TEXTUREACCESS_STREAMING,
                                             WINDOW_WIDTH, WINDOW_HEIGHT);

    // 2. Create our "Framebuffer" (a raw array of pixels)
    // We use uint32_t so each element is exactly 4 bytes (A, R, G, B)
    Canvas frame(WINDOW_WIDTH, WINDOW_HEIGHT, 0xFF000000);

    // 3. Define the Rectangle
    std::vector<Cuboid> c;

    c.push_back(Cuboid(-1, -1, 4, 0xFF0000FF));
    c.push_back(Cuboid(1, -1, 4, 0xFFFF0000));
    c.push_back(Cuboid(0, 0, 4, 0xFFFFFFFF));
    c.push_back(Cuboid(0, 1, 4, 0xFFFFFFFF));
    c.push_back(Cuboid(0, 2, 4, 0xFFFFFFFF));

    float step = 1;
    // --- Main Loop ---
    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
        }

        // Clear Screen
        frame.clear();

        // Drawing Part
        for (size_t i = 0; i < c.size(); i++) {
            frame.drawCuboid(c.at(i));
        }

        // Check for key presses
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    running = false;  // Exit on Escape
                    break;
                case SDLK_z:
                    for (size_t i = 0; i < c.size(); i++) {
                        c.at(i).;
                    }

                    break;
                case SDLK_s:
                    player_jump();  // Specific action for Space
                    break;
                default:
                    break;
            }
        }

        signal(SIGINT, handler);

        // Push our memory buffer to the GPU to be displayed
        SDL_UpdateTexture(texture, NULL, frame.buffer.data(),
                          WINDOW_WIDTH * sizeof(uint32_t));

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FPS);
    }

    // Cleanup
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
