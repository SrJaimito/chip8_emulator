#include "c8_display.h"

#include <string.h>

void c8_display_clear(c8_display_t *display) {
    memset(display->pixels, 0, C8_DISPLAY_WIDTH * C8_DISPLAY_HEIGHT);
}

int c8_display_draw_sprite(c8_display_t *display,
        uint8_t *sprite, uint8_t sprite_len, uint8_t x, uint8_t y) {

    int collision = 0;

    for (int i = 0; i < sprite_len; i++) {
        int screen_y = (y + i) % C8_DISPLAY_HEIGHT;

        for (int j = 0; j < C8_SPRITE_WIDTH; j++) {
            int screen_x = (x + j) % C8_DISPLAY_WIDTH;
            uint8_t pixel = (sprite[i] >> (C8_SPRITE_WIDTH - j - 1)) & 0x01;

            uint8_t xored_pixel = display->pixels[screen_y][screen_x] ^ pixel;
            if (xored_pixel == 0x01) {
                collision = 1;
            }

            display->pixels[screen_y][screen_x] = pixel;
        }
    }

    return collision;
}
