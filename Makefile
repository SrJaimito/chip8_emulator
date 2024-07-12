BUILD_DIR = build

SRC_DIR = src
C8_CPU_DIR = $(SRC_DIR)/c8_cpu
C8_MEM_DIR = $(SRC_DIR)/c8_memory
C8_DIS_DIR = $(SRC_DIR)/c8_display
C8_TIM_DIR = $(SRC_DIR)/c8_timer
C8_KEY_DIR = $(SRC_DIR)/c8_keyboard

CC = gcc

CFLAGS = -O3 -g3
CFLAGS += -Wall -pedantic
CFLAGS += -I$(C8_CPU_DIR) -I$(C8_MEM_DIR) -I$(C8_DIS_DIR) -I$(C8_TIM_DIR) -I$(C8_KEY_DIR)
CFLAGS += -lSDL2

all: chip8

chip8: $(SRC_DIR)/main.c $(BUILD_DIR)/c8_cpu.o $(BUILD_DIR)/c8_memory.o $(BUILD_DIR)/c8_display.o $(BUILD_DIR)/c8_timer.o $(BUILD_DIR)/c8_keyboard.o
	$(CC) $^ -o $@ $(CFLAGS)

$(BUILD_DIR)/c8_cpu.o: $(C8_CPU_DIR)/c8_cpu.c $(C8_CPU_DIR)/c8_cpu.h
	$(CC) $< -o $@ $(CFLAGS) -c

$(BUILD_DIR)/c8_memory.o: $(C8_MEM_DIR)/c8_memory.c $(C8_MEM_DIR)/c8_memory.h
	$(CC) $< -o $@ $(CFLAGS) -c

$(BUILD_DIR)/c8_display.o: $(C8_DIS_DIR)/c8_display.c $(C8_DIS_DIR)/c8_display.h
	$(CC) $< -o $@ $(CFLAGS) -c

$(BUILD_DIR)/c8_timer.o: $(C8_TIM_DIR)/c8_timer.c $(C8_TIM_DIR)/c8_timer.h
	$(CC) $< -o $@ $(CFLAGS) -c

$(BUILD_DIR)/c8_keyboard.o: $(C8_KEY_DIR)/c8_keyboard.c $(C8_KEY_DIR)/c8_keyboard.h
	$(CC) $< -o $@ $(CFLAGS) -c

clean:
	rm -rf $(BUILD_DIR)/*
