#include "c8_timer.h"

#include <SDL2/SDL.h>

void c8_timer_init(c8_timer_t *timer) {
    timer->count = 0;
    timer->last_decrease_time = 0;
}

uint8_t c8_timer_get_count(c8_timer_t *timer) {
    return timer->count;
}

void c8_timer_set_count(c8_timer_t *timer, uint8_t count) {
    timer->count = count;
}

void c8_timer_update(c8_timer_t *timer) {
    uint32_t current_time = SDL_GetTicks();
    if (current_time - timer->last_decrease_time >= 1000) {
        if (timer->count > 0) {
            timer->count--;
        }
    }
}
