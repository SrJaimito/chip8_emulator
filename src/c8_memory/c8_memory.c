#include "c8_memory.h"

int c8_memory_write(c8_memory_t memory, uint16_t addr, uint8_t value){
    if (addr < C8_PROGRAM_START_ADDR || addr > C8_MEMORY_SIZE) {
        return 0;
    }

    memory[addr] = value;

    return 1;
}

int c8_memory_read(c8_memory_t memory, uint16_t addr, uint8_t *value){
    if (addr < C8_PROGRAM_START_ADDR || addr > C8_MEMORY_SIZE) {
        return 0;
    }

    *value = memory[addr];

    return 1;
}
