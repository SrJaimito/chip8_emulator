#ifndef _C8_KEYBOARD_H__
#define _C8_KEYBOARD_H__

#include <stdint.h>

#define C8_NUM_KEYS 16

typedef struct {
    int pressed_keys[C8_NUM_KEYS];
} c8_keyboard_t;

void c8_keyboard_init(c8_keyboard_t *keyboard);
void c8_keyboard_poll(c8_keyboard_t *keyboard);
int c8_keyboard_is_pressed(c8_keyboard_t *keyboard, uint8_t key);

#endif
