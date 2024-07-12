#ifndef __C8_TIMER_H__
#define __C8_TIMER_H__

#include <stdint.h>

typedef struct {
    uint8_t count;
} c8_timer_t;

void c8_timer_init(c8_timer_t *timer);
uint8_t c8_timer_get_count(c8_timer_t *timer);
void c8_timer_set_count(c8_timer_t *timer, uint8_t count);
void c8_timer_update(c8_timer_t *timer);

#endif
