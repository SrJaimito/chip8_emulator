#ifndef __C8_MEMORY_H__
#define __C8_MEMORY_H__

#include <stdint.h>

#define C8_MEMORY_SIZE        0x1000
#define C8_PROGRAM_START_ADDR 0x200
#define C8_MAX_PROGRAM_SIZE   (C8_MEMORY_SIZE - C8_PROGRAM_START_ADDR)

typedef struct {
    uint8_t data[C8_MEMORY_SIZE];
} c8_memory_t;

int c8_memory_init(c8_memory_t *memory, const char *program);

void c8_memory_write(c8_memory_t *memory, uint16_t addr, uint8_t value);
void c8_memory_read(c8_memory_t *memory, uint16_t addr, uint8_t *value);

#endif
