#pragma once
#include <iostream>
#include <stdint.h>
#include <vector>
#include <map>

#include "SDL3/SDL.h"

//Structs
struct Vector2 {
    float x;
    float y;

    Vector2(float _x, float _y) {
        x = _x;
        y = _y;
    }
};

//Memory
uint8_t memory[4096] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

std::vector<uint16_t> stack;

//Timers
uint8_t delayTimer = 60, soundTimer = 60;
void UpdateTimers() {
    if (delayTimer <= 0) delayTimer = 60;
    if (soundTimer <= 0) soundTimer = 60;

    delayTimer -= 1;
    soundTimer -= 1;
}

//Screen
const Vector2 screenSize(64,32);
uint8_t pixels[64*32];
Vector2 screenScale(16,16);

void RenderScreen(SDL_Renderer* renderer) {
    float xPos = 0;
    float yPos = 0;

    for (long unsigned int i = 0; i < sizeof(pixels); i++) {
        if (pixels[i] == 0) {
            xPos++;
            if (xPos >= 64) {
                yPos++;
                xPos = 0;
            }
            continue;
        }

        SDL_FRect rect = {
            xPos*screenScale.x, yPos*screenScale.y,
            screenScale.x, screenScale.y
        };
        SDL_RenderFillRect(renderer, &rect);

        xPos++;
        if (xPos >= 64) {
            yPos++;
            xPos = 0;
        }
    }
}

//Input
std::map<char, bool> keys = {
    {'1', false}, {'2', false}, {'3', false}, {'C', false},
    {'4', false}, {'5', false}, {'6', false}, {'D', false},
    {'7', false}, {'8', false}, {'9', false}, {'E', false},
    {'A', false}, {'0', false}, {'B', false}, {'F', false},
};

void Input() {
    SDL_PumpEvents();

    const bool *input = SDL_GetKeyboardState(nullptr);

    if (input[SDL_SCANCODE_1]) keys['1'] = true;
    else keys['1'] = false;

    if (input[SDL_SCANCODE_2]) keys['2'] = true;
    else keys['2'] = false;

    if (input[SDL_SCANCODE_3]) keys['3'] = true;
    else keys['3'] = false;

    if (input[SDL_SCANCODE_4]) keys['C'] = true;
    else keys['C'] = false;



    if (input[SDL_SCANCODE_Q]) keys['4'] = true;
    else keys['4'] = false;

    if (input[SDL_SCANCODE_W]) keys['5'] = true;
    else keys['5'] = false;

    if (input[SDL_SCANCODE_E]) keys['6'] = true;
    else keys['6'] = false;

    if (input[SDL_SCANCODE_R]) keys['D'] = true;
    else keys['D'] = false;
    


    if (input[SDL_SCANCODE_A]) keys['7'] = true;
    else keys['7'] = false;

    if (input[SDL_SCANCODE_S]) keys['8'] = true;
    else keys['8'] = false;

    if (input[SDL_SCANCODE_D]) keys['9'] = true;
    else keys['9'] = false;

    if (input[SDL_SCANCODE_F]) keys['E'] = true;
    else keys['E'] = false;
    


    if (input[SDL_SCANCODE_Z]) keys['A'] = true;
    else keys['A'] = false;

    if (input[SDL_SCANCODE_X]) keys['0'] = true;
    else keys['0'] = false;

    if (input[SDL_SCANCODE_C]) keys['B'] = true;
    else keys['B'] = false;

    if (input[SDL_SCANCODE_V]) keys['F'] = true;
    else keys['F'] = false;
}