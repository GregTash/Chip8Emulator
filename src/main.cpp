#include <iostream>
#include "SDL3/SDL.h"

#include "../include/components.h"

int main() {
    //Used to calculate delta time
    long a = 0.0f, b = 0.0f;

    SDL_Init(SDL_INIT_VIDEO);
    
    SDL_Window* window = SDL_CreateWindow("Chip8Emu",
        screenSize.x * screenScale.x,
        screenSize.y * screenScale.y,
        SDL_WINDOW_MOUSE_FOCUS);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    SDL_Event event;
    bool active = true;
    while (active) {
        a = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                active = false;
                break;
            }

            //Limit fps to 60 and run drawing functions 60 frames per second
            if ((a - b) > 1000/60.0f) {
                b = a;

                SDL_SetRenderDrawColor(renderer,0,0,0,255);
                SDL_RenderClear(renderer);
                SDL_SetRenderDrawColor(renderer,255,255,255,255);

                RenderScreen(renderer);

                SDL_RenderPresent(renderer);
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    return 0;
}