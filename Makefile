BUILD_DIR = build

SRC_DIR = src
C8_CPU_DIR = $(SRC_DIR)/c8_cpu
C8_MEM_DIR = $(SRC_DIR)/c8_memory

CC = gcc

CFLAGS = -O3 -g3
CFLAGS += -Wall -pedantic
CFLAGS += -I$(C8_CPU_DIR) -I$(C8_MEM_DIR)

all: chip8

chip8: $(SRC_DIR)/main.c $(BUILD_DIR)/c8_cpu.o $(BUILD_DIR)/c8_memory.o
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/c8_cpu.o: $(C8_CPU_DIR)/c8_cpu.c $(C8_CPU_DIR)/c8_cpu.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/c8_memory.o: $(C8_MEM_DIR)/c8_memory.c $(C8_MEM_DIR)/c8_memory.h
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(BUILD_DIR)/*
