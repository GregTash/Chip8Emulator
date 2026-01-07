#include <iostream>
#include "SDL3/SDL.h"

#include "../include/components.h"

#include "../include/miniaudio.h"

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount) {

}

int main() {
    if (InitAudio() != MA_SUCCESS) return audio_result;

    //Used to calculate delta time
    long a = 0.0f, b = 0.0f;

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

        //Limit fps to 60 and run functions at 60 frames per second
        if ((a - b) > 1000/60.0f) {
            b = a;

            //Other
            UpdateTimers();

            //Drawing
            SDL_SetRenderDrawColor(renderer,0,0,0,255);
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer,255,255,255,255);

            RenderScreen(renderer);

            SDL_RenderPresent(renderer);
        }
    }

    ma_engine_uninit(&engine);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    return 0;
}