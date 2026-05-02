#include <SDL.h>
#include <unistd.h>

#include <chrono>
#include <iostream>
#include <thread>

#include "./Canvas/Canvas.h"
#include "constants.h"

// TODO: Make a line Class to be able to draw the arrets of the cube

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
    // Rectangle r1(0, 10, 1, 10, 10, 0xFF00FF00);
    Point p1(-1, 1, 2, 0xFF00FF00);
    Point p2(1, 1, 2, 0xFF00FF00);
    Point p3(1, -1, 2, 0xFF00FF00);
    Point p4(-1, -1, 2, 0xFF00FF00);

    Triangle t1(p1, p2, p3, 0xFF748FFC);
    Triangle t2(p1, p3, p4, 0xFFfC0588);

    Square s1(t1, t2, 0xFF00FF00);

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

        // Motion logic

        // Drawing Part

        frame.drawSquare(s1);

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
