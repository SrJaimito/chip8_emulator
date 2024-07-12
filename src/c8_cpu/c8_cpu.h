#ifndef __C8_CPU_H__
#define __C8_CPU_H__

#include <stdint.h>

#include "c8_memory.h"
#include "c8_display.h"
#include "c8_timer.h"
#include "c8_keyboard.h"

typedef struct {
    uint8_t v[16];
    uint16_t i;

    uint16_t stack[16];

    uint16_t pc;
    uint8_t sp;

    // Connections to other hardware components
    c8_memory_t *memory;
    c8_display_t *display;
    c8_timer_t *delay_timer;
    c8_timer_t *sound_timer;
    c8_keyboard_t *keyboard;
} c8_cpu_t;

void c8_cpu_init(c8_cpu_t *cpu);

void c8_cpu_connect_memory(c8_cpu_t *cpu, c8_memory_t *memory);
void c8_cpu_connect_display(c8_cpu_t *cpu, c8_display_t *display);
void c8_cpu_connect_delay_timer(c8_cpu_t *cpu, c8_timer_t *timer);
void c8_cpu_connect_sound_timer(c8_cpu_t *cpu, c8_timer_t *timer);
void c8_cpu_connect_keyboard(c8_cpu_t *cpu, c8_keyboard_t *keyboard);

void c8_cpu_run_next_instruction(c8_cpu_t *cpu);

#endif
