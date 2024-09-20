#ifndef __CHIP_8_H__
#define __CHIP_8_H__

#include "c8_cpu.h"
#include "c8_display.h"
#include "c8_keyboard.h"
#include "c8_memory.h"
#include "c8_timer.h"

typedef struct {
    c8_cpu_t *cpu;
    c8_display_t *display;
    c8_keyboard_t *keyboard;
    c8_memory_t *memory;
    c8_timer_t *delay_timer;
    c8_timer_t *sound_timer;
} chip_8_t;

typedef enum {
    C8_OK,
    C8_SDL_INIT_ERROR,
    C8_ALLOC_ERROR,
    C8_FILE_ERROR,
    C8_MEMSIZ_ERROR,
    C8_DISPLAY_INIT_ERROR
} c8_error_e;

c8_error_e chip_8_init(chip_8_t *chip_8, const char *program);
void chip_8_deinit(chip_8_t *chip_8);

void chip_8_run(chip_8_t *chip_8);

#endif
