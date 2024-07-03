#ifndef __CPU_H__
#define __CPU_H__

#include <stdint.h>

#include "c8_memory.h"
#include "c8_display.h"

typedef struct {
    uint8_t v[16];
    uint16_t i;

    uint16_t stack[16];

    uint16_t pc;
    uint8_t sp;

    c8_memory_t *mem;
    c8_display_t *disp;
} c8_cpu_t;

void execute_opcode(uint16_t opcode);

#endif
