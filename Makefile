BUILD_DIR = build

SRC_DIR = src
C8_DIR = $(SRC_DIR)/chip_8
C8_CPU_DIR = $(C8_DIR)/c8_cpu
C8_MEM_DIR = $(C8_DIR)/c8_memory
C8_DIS_DIR = $(C8_DIR)/c8_display
C8_TIM_DIR = $(C8_DIR)/c8_timer
C8_KEY_DIR = $(C8_DIR)/c8_keyboard

OBJ_FILES = $(BUILD_DIR)/chip_8.o $(BUILD_DIR)/c8_cpu.o $(BUILD_DIR)/c8_memory.o
OBJ_FILES += $(BUILD_DIR)/c8_display.o $(BUILD_DIR)/c8_timer.o $(BUILD_DIR)/c8_keyboard.o

CC = gcc

CFLAGS = -O3 -g3
CFLAGS += -Wall -pedantic
CFLAGS += -I$(C8_DIR) -I$(C8_CPU_DIR) -I$(C8_MEM_DIR) -I$(C8_DIS_DIR) -I$(C8_TIM_DIR) -I$(C8_KEY_DIR)
CFLAGS += -lSDL2
# CFLAGS += -DDEBUG_CPU

all: chip8

chip8: $(SRC_DIR)/main.c $(OBJ_FILES)
	$(CC) $^ -o $@ $(CFLAGS)

$(BUILD_DIR)/chip_8.o: $(C8_DIR)/chip_8.c $(C8_DIR)/chip_8.h
	$(CC) $< -o $@ $(CFLAGS) -c

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
	rm -rf $(BUILD_DIR)/* chip8
