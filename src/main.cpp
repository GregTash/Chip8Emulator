#include <iostream>
#include <cmath>
#include "SDL3/SDL.h"

#include "../include/components.h"
#include "../include/miniaudio.h"

int main() {
    if (LoadApplication("Logo.ch8", memory) != 0) return -1;
    if (InitAudio() != MA_SUCCESS) return audio_result;

    //Used to calculate delta time
    long a = 0.0f, b = 0.0f;
    long c = 0.0f, d = 0.0f;
    uint16_t instructionsPerSec = 30;

    SDL_Init(SDL_INIT_VIDEO);
    
    SDL_Window* window = SDL_CreateWindow("Chip8Emu",
        screenSize.x * screenScale.x,
        screenSize.y * screenScale.y,
        SDL_WINDOW_MOUSE_FOCUS);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);

    SDL_Event event;
    bool active = true;
    while (active) {
        a = SDL_GetTicks();
        c = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                active = false;
                break;

                case SDL_EVENT_KEY_DOWN:
                Input();
                break;

                case SDL_EVENT_KEY_UP:
                Input();
                break;
            }
        }

        if ((c - d) > 1000/instructionsPerSec) {
            d = c;
            bool jumping = false;
            uint8_t nibble = memory[PC] << 4;

            switch(memory[PC] >> 4) {
                case 0x0:
                instructions::ClearScreen(renderer);
                break;

                case 0x1:
                nibble >>= 4;
                PC = (nibble * pow(16,2)) + memory[PC+1];
                jumping = true;
                break;

                case 0x6:
                break;

                case 0x7:
                break;

                case 0xA:
                break;

                case 0xD:
                break;
            }

            std::cout << static_cast<int>(memory[PC]) << ' ' << PC << '\n';
            if (!jumping) PC += 2;

            if (PC > 4096) active = false;
        }

        //Limit fps to 60 and run functions at 60 frames per second
        if ((a - b) > 1000/60.0f) {
            b = a;
            //Other
            UpdateTimers();

            //Drawing
            //SDL_SetRenderDrawColor(renderer,255,255,255,255);

            //RenderScreen(renderer);

            SDL_RenderPresent(renderer);
        }
    }

    ma_engine_uninit(&engine);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    return 0;
}