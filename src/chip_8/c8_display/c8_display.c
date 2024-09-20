#include "c8_display.h"

#include <SDL2/SDL_timer.h>
#include <string.h>

int c8_display_init(c8_display_t *display) {
    for (int i = 0; i < C8_DISPLAY_HEIGHT; i++) {
        memset(display->pixels[i], 0, C8_DISPLAY_WIDTH);
    }

    SDL_Window *window = SDL_CreateWindow(
        "Chip-8 emulator",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        C8_DISPLAY_WIDTH * DISPLAY_SCALE, C8_DISPLAY_HEIGHT * DISPLAY_SCALE,
        SDL_WINDOW_SHOWN
    );

    if (window == NULL) {
        return 1;
    }

    display->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (display->renderer == NULL) {
        SDL_DestroyWindow(window);
        return 2;
    }

    display->last_render_time = 0;

    return 0;
}

void c8_display_clear(c8_display_t *display) {
    for (int i = 0; i < C8_DISPLAY_HEIGHT; i++) {
        memset(display->pixels[i], 0, C8_DISPLAY_WIDTH);
    }
}

int c8_display_draw_sprite(c8_display_t *display,
        uint8_t *sprite, uint8_t sprite_len, uint8_t x, uint8_t y) {

    int collision = 0;

    for (int i = 0; i < sprite_len; i++) {
        int screen_y = (y + i) % C8_DISPLAY_HEIGHT;

        for (int j = 0; j < C8_SPRITE_WIDTH; j++) {
            int screen_x = (x + j) % C8_DISPLAY_WIDTH;
            uint8_t pixel = (sprite[i] >> (C8_SPRITE_WIDTH - j - 1)) & 0x01;

            if (pixel == 1) {
                if (display->pixels[screen_y][screen_x] == 1) {
                    display->pixels[screen_y][screen_x] = 0;
                    collision = 1;
                } else {
                    display->pixels[screen_y][screen_x] = 1;
                }
            }
        }
    }

    return collision;
}

void c8_display_render(c8_display_t *display) {
    uint32_t current_time = SDL_GetTicks();
    if (current_time - display->last_render_time >= DISPLAY_REFRESH_MS) {
        display->last_render_time = current_time;

        SDL_SetRenderDrawColor(display->renderer, 0, 0, 0, 255);
        SDL_RenderClear(display->renderer);

        SDL_SetRenderDrawColor(display->renderer, 255, 255, 255, 255);

        for (int i = 0; i < C8_DISPLAY_HEIGHT; i++) {
            for (int j = 0; j < C8_DISPLAY_WIDTH; j++) {
                if (display->pixels[i][j] == 1) {
                    int x = j * DISPLAY_SCALE;
                    int y = i * DISPLAY_SCALE;

                    for (int y_off = 0; y_off < DISPLAY_SCALE; y_off++) {
                        for (int x_off = 0; x_off < DISPLAY_SCALE; x_off++) {
                            SDL_RenderDrawPoint(display->renderer, x + x_off, y + y_off);
                        }
                    }
                }
            }
        }

        SDL_RenderPresent(display->renderer);
    }
}
