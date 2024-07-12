#include "c8_keyboard.h"

#include <string.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>

static int map_input(SDL_Event *event) {
    switch (event->key.keysym.sym) {
        case SDLK_1: return 0x1;
        case SDLK_2: return 0x2;
        case SDLK_3: return 0x3;
        case SDLK_4: return 0xC;
        case SDLK_q: return 0x4;
        case SDLK_w: return 0x5;
        case SDLK_e: return 0x6;
        case SDLK_r: return 0xD;
        case SDLK_a: return 0x7;
        case SDLK_s: return 0x8;
        case SDLK_d: return 0x9;
        case SDLK_f: return 0xE;
        case SDLK_z: return 0xA;
        case SDLK_x: return 0x0;
        case SDLK_c: return 0xB;
        case SDLK_v: return 0xF;
        default: return 0x0;
    }
}

void c8_keyboard_init(c8_keyboard_t *keyboard) {
    memset(keyboard->pressed_keys, 0, C8_NUM_KEYS * sizeof(int));
}

void c8_keyboard_poll(c8_keyboard_t *keyboard) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                keyboard->pressed_keys[map_input(&event)] = 1;
                break;

            case SDL_KEYUP:
                keyboard->pressed_keys[map_input(&event)] = 0;
        }
    }
}

int c8_keyboard_is_pressed(c8_keyboard_t *keyboard, uint8_t key) {
    return keyboard->pressed_keys[key];
}
