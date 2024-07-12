#include "c8_timer.h"

void c8_timer_init(c8_timer_t *timer) {
    timer->count = 0;
}

uint8_t c8_timer_get_count(c8_timer_t *timer) {
    return timer->count;
}

void c8_timer_set_count(c8_timer_t *timer, uint8_t count) {
    timer->count = count;
}

void c8_timer_update(c8_timer_t *timer) {
}
