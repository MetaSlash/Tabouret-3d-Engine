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
    Rectangle r1(0, 0, 0, 10, 10, 0xFF00FF00);
    Rectangle r2(0, 0, 0, 10, 10, 0xFF00FF00);
    Rectangle r3(0, 0, 0, 10, 10, 0xFF00FF00);
    Rectangle r4(0, 0, 0, 10, 10, 0xFF00FF00);
    Rectangle r5(0, 0, 0, 10, 10, 0xFF00FF00);
    Rectangle r6(0, 0, 0, 10, 10, 0xFF00FF00);
    Rectangle r7(0, 0, 0, 10, 10, 0xFF00FF00);
    Rectangle r8(0, 0, 0, 10, 10, 0xFF00FF00);

    float dz = 0.5;
    // --- Main Loop ---
    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
        }
        dz += 0.005f;

        // Clear Screen
        frame.clear();

        // TODO: Continue the render of the moving cube

        // Motion Logic
        r1.set3dCoods(0.5f, 0.5f, dz);
        r2.set3dCoods(-0.5f, 0.5f, dz);
        r3.set3dCoods(0.5f, -0.5f, dz);
        r4.set3dCoods(-0.5f, -0.5f, dz);

        // r5.set3dCoods(0.5f, 0.5f, dz * (-1));
        // r6.set3dCoods(-0.5f, 0.5f, dz * (-1));
        // r7.set3dCoods(0.5f, -0.5f, dz * (-1));
        // r8.set3dCoods(-0.5f, -0.5f, dz * (-1));

        // Draw on screen the points
        frame.drawRectangle(r1);
        frame.drawRectangle(r2);
        frame.drawRectangle(r3);
        frame.drawRectangle(r4);
        // frame.drawRectangle(r5);
        // frame.drawRectangle(r6);
        // frame.drawRectangle(r7);
        // frame.drawRectangle(r8);

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
