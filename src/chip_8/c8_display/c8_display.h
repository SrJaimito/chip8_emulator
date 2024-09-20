#ifndef __C8_DISPLAY_H__
#define __C8_DISPLAY_H__

#include <stdint.h>

#include <SDL2/SDL.h>

#define C8_DISPLAY_WIDTH  64
#define C8_DISPLAY_HEIGHT 32

#define C8_SPRITE_WIDTH       8
#define C8_SPRITE_MAX_HEIGHT  15
#define C8_CHAR_SPRITE_HEIGHT 5

#define DISPLAY_SCALE 20

#define DISPLAY_REFRESH_MS 17

typedef struct {
    uint8_t pixels[C8_DISPLAY_HEIGHT][C8_DISPLAY_WIDTH];

    SDL_Renderer *renderer;
    uint32_t last_render_time;
} c8_display_t;

int c8_display_init(c8_display_t *display);

void c8_display_clear(c8_display_t *display);
int c8_display_draw_sprite(c8_display_t *display,
        uint8_t *sprite, uint8_t sprite_len, uint8_t x, uint8_t y);
void c8_display_render(c8_display_t *display);

#endif
