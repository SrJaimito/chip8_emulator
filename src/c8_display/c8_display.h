#ifndef __C8_DISPLAY_H__
#define __C8_DISPLAY_H__

#include <stdint.h>

#define C8_DISPLAY_WIDTH  64
#define C8_DISPLAY_HEIGHT 32

#define C8_SPRITE_WIDTH       8
#define C8_SPRITE_MAX_HEIGHT  15
#define C8_CHAR_SPRITE_HEIGHT 5

typedef struct {
    uint8_t pixels[C8_DISPLAY_HEIGHT][C8_DISPLAY_WIDTH];
} c8_display_t;

void c8_display_clear(c8_display_t *display);
int c8_display_draw_sprite(c8_display_t *display,
        uint8_t *sprite, uint8_t sprite_len, uint8_t x, uint8_t y);

#endif
