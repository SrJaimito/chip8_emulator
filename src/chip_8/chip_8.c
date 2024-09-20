#include "chip_8.h"
#include "c8_cpu.h"
#include "c8_display.h"
#include "c8_keyboard.h"
#include "c8_memory.h"
#include "c8_timer.h"

#include <SDL2/SDL.h>

#include <SDL2/SDL_events.h>
#include <stdlib.h>

c8_error_e chip_8_init(chip_8_t *chip_8, const char *program) {
    chip_8->cpu = NULL;
    chip_8->memory = NULL;
    chip_8->display = NULL;
    chip_8->keyboard = NULL;
    chip_8->delay_timer = NULL;
    chip_8->sound_timer = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return C8_SDL_INIT_ERROR;
    }

    atexit(SDL_Quit);

    chip_8->memory = (c8_memory_t *) malloc(sizeof(c8_memory_t));
    if (chip_8->memory == NULL) {
        return C8_ALLOC_ERROR;
    }

    switch (c8_memory_init(chip_8->memory, program)) {
        case 1: return C8_FILE_ERROR;
        case 2: return C8_MEMSIZ_ERROR;
    }

    chip_8->display = (c8_display_t *) malloc(sizeof(c8_display_t));
    if (chip_8->display == NULL) {
        chip_8_deinit(chip_8);
        return C8_ALLOC_ERROR;
    }

    if (c8_display_init(chip_8->display) != 0) {
        chip_8_deinit(chip_8);
        return C8_DISPLAY_INIT_ERROR;
    }

    chip_8->keyboard = (c8_keyboard_t *) malloc(sizeof(c8_keyboard_t));
    if (chip_8->keyboard == NULL) {
        chip_8_deinit(chip_8);
        return C8_ALLOC_ERROR;
    }

    c8_keyboard_init(chip_8->keyboard);

    chip_8->delay_timer = (c8_timer_t *) malloc(sizeof(c8_timer_t));
    if (chip_8->keyboard == NULL) {
        chip_8_deinit(chip_8);
        return C8_ALLOC_ERROR;
    }

    c8_timer_init(chip_8->delay_timer);

    chip_8->sound_timer = (c8_timer_t *) malloc(sizeof(c8_timer_t));
    if (chip_8->keyboard == NULL) {
        chip_8_deinit(chip_8);
        return C8_ALLOC_ERROR;
    }

    c8_timer_init(chip_8->sound_timer);

    chip_8->cpu = (c8_cpu_t *) malloc(sizeof(c8_cpu_t));
    if (chip_8->cpu == NULL) {
        chip_8_deinit(chip_8);
        return C8_ALLOC_ERROR;
    }

    c8_cpu_init(chip_8->cpu);
    c8_cpu_connect_memory(chip_8->cpu, chip_8->memory);
    c8_cpu_connect_display(chip_8->cpu, chip_8->display);
    c8_cpu_connect_keyboard(chip_8->cpu, chip_8->keyboard);
    c8_cpu_connect_delay_timer(chip_8->cpu, chip_8->delay_timer);
    c8_cpu_connect_sound_timer(chip_8->cpu, chip_8->sound_timer);

    return C8_OK;
}

void chip_8_deinit(chip_8_t *chip_8) {
    if (chip_8->cpu != NULL) {
        free(chip_8->cpu);
    }

    if (chip_8->memory != NULL) {
        free(chip_8->memory);
    }

    if (chip_8->display != NULL) {
        free(chip_8->display);
    }

    if (chip_8->keyboard != NULL) {
        free(chip_8->keyboard);
    }

    if (chip_8->delay_timer != NULL) {
        free(chip_8->delay_timer);
    }

    if (chip_8->sound_timer != NULL) {
        free(chip_8->sound_timer);
    }
}

void chip_8_run(chip_8_t *chip_8) {
    int quit = 0;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            } else {
                c8_keyboard_check_input(chip_8->keyboard, &event);
            }
        }

        c8_cpu_run_next_instruction(chip_8->cpu);

        c8_timer_update(chip_8->delay_timer);
        c8_timer_update(chip_8->sound_timer);

        c8_display_render(chip_8->display);
    }
}
