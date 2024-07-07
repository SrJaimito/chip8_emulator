#ifndef __C8_MEMORY_H__
#define __C8_MEMORY_H__

#include <stdint.h>

#define C8_MEMORY_SIZE        0x1000
#define C8_PROGRAM_START_ADDR 0x200

typedef uint8_t c8_memory_t[C8_MEMORY_SIZE];

int c8_memory_write(c8_memory_t memory, uint16_t addr, uint8_t value);
int c8_memory_read(c8_memory_t memory, uint16_t addr, uint8_t *value);

#endif
