#include "c8_cpu.h"

#include <stdlib.h>
#include <string.h>

#include <SDL2/SDL.h>

#ifdef DEBUG_CPU
#define dbg(...) printf(__VA_ARGS__)
#else
#define dbg(...)
#endif

static void cls(c8_cpu_t *cpu) {
    dbg("Running: CLS\n");

    c8_display_clear(cpu->display);
}

static void ret(c8_cpu_t *cpu) {
    dbg("Running: RET\n");

    cpu->sp--;
    cpu->pc = cpu->stack[cpu->sp];
}

static void jp_addr(c8_cpu_t *cpu, uint16_t addr) {
    dbg("Running: JP addr\n");

    cpu->pc = addr;
}

static void call_addr(c8_cpu_t *cpu, uint16_t addr) {
    dbg("Running: CALL addr\n");

    cpu->stack[cpu->sp] = cpu->pc;
    cpu->sp++;

    cpu->pc = addr;
}

static void se_vx_byte(c8_cpu_t *cpu, uint8_t vx, uint8_t byte) {
    dbg("Running: SE vx, byte\n");

    if (cpu->v[vx] == byte) {
        cpu->pc += 2;
    }
}

static void sne_vx_byte(c8_cpu_t *cpu, uint8_t vx, uint8_t byte) {
    dbg("Running: SNE vx, byte\n");

    if (cpu->v[vx] != byte) {
        cpu->pc += 2;
    }
}

static void se_vx_vy(c8_cpu_t *cpu, uint8_t vx, uint8_t vy) {
    dbg("Running: SE vx, vy\n");

    if (cpu->v[vx] == cpu->v[vy]) {
        cpu->pc += 2;
    }
}

static void ld_vx_byte(c8_cpu_t *cpu, uint8_t vx, uint8_t byte) {
    dbg("Running: LD vx, byte\n");

    cpu->v[vx] = byte;
}

static void add_vx_byte(c8_cpu_t *cpu, uint8_t vx, uint8_t byte) {
    dbg("Running: ADD vx, byte\n");

    cpu->v[vx] += byte;
}

static void ld_vx_vy(c8_cpu_t *cpu, uint8_t vx, uint8_t vy) {
    dbg("Running: LD vx, vy\n");

    cpu->v[vx] = cpu->v[vy];
}

static void or_vx_vy(c8_cpu_t *cpu, uint8_t vx, uint8_t vy) {
    dbg("Running: OR vx, vy\n");

    cpu->v[vx] |= cpu->v[vy];
}

static void and_vx_vy(c8_cpu_t *cpu, uint8_t vx, uint8_t vy) {
    dbg("Running: AND vx, vy\n");

    cpu->v[vx] &= cpu->v[vy];
}

static void xor_vx_vy(c8_cpu_t *cpu, uint8_t vx, uint8_t vy) {
    dbg("Running: XOR vx, vy\n");

    cpu->v[vx] ^= cpu->v[vy];
}

static void add_vx_vy(c8_cpu_t *cpu, uint8_t vx, uint8_t vy) {
    dbg("Running: ADD vx, vy\n");

    uint16_t result = cpu->v[vx] + cpu->v[vy];

    cpu->v[0x0F] = result > 0xFF ? 0x01 : 0x00;

    cpu->v[vx] = result & 0xFF;
}

static void sub_vx_vy(c8_cpu_t *cpu, uint8_t vx, uint8_t vy) {
    dbg("Running: SUB vx, vy\n");

    cpu->v[0x0F] = cpu->v[vx] > cpu->v[vy] ? 0x01 : 0x00;
    cpu->v[vx] -= cpu->v[vy];
}

static void shr_vx(c8_cpu_t *cpu, uint8_t vx) {
    dbg("Running: SHR vx\n");

    cpu->v[0x0F] = cpu->v[vx] & 0x01;
    cpu->v[vx] >>= 1;
}

static void subn_vx_vy(c8_cpu_t *cpu, uint8_t vx, uint8_t vy) {
    dbg("Running: SUBN vx, vy\n");

    cpu->v[0x0F] = cpu->v[vy] > cpu->v[vx] ? 0x01 : 0x00;
    cpu->v[vx] = cpu->v[vy] - cpu->v[vx];
}

static void shl_vx(c8_cpu_t *cpu, uint8_t vx) {
    dbg("Running: SHL vx\n");

    cpu->v[0x0F] = cpu->v[vx] >> 7;
    cpu->v[vx] <<= 1;
}

static void sne_vx_vy(c8_cpu_t *cpu, uint8_t vx, uint8_t vy) {
    dbg("Running: SNE vx, vy\n");

    if (cpu->v[vx] != cpu->v[vy]) {
        cpu->pc += 2;
    }
}

static void ld_i_addr(c8_cpu_t *cpu, uint16_t addr) {
    dbg("Running: LD i, addr\n");

    cpu->i = addr;
}

static void jp_v0_addr(c8_cpu_t *cpu, uint16_t addr) {
    dbg("Running: JP v0, addr\n");

    cpu->pc = cpu->v[0] + addr;
}

static void rnd_vx_byte(c8_cpu_t *cpu, uint8_t vx, uint8_t byte) {
    dbg("Running: RND vx, byte\n");

    uint8_t rand_byte = rand() % 0x100;

    cpu->v[vx] = rand_byte & byte;
}

static void drw_vx_vy_nibble(c8_cpu_t *cpu, uint8_t vx, uint8_t vy, uint8_t nibble) {
    dbg("Running: DRW vx, vy\n");

    uint8_t sprite[C8_SPRITE_MAX_HEIGHT];

    for (int i = 0; i < nibble; i++) {
        c8_memory_read(cpu->memory, cpu->i + i, sprite + i);
    }

    cpu->v[0xF] = c8_display_draw_sprite(cpu->display, sprite, nibble, cpu->v[vx], cpu->v[vy]);
}

static void skp_vx(c8_cpu_t *cpu, uint8_t vx) {
    dbg("Running: SKP vx\n");

    if (c8_keyboard_is_pressed(cpu->keyboard, cpu->v[vx])) {
        cpu->pc += 2;
    }
}

static void sknp_vx(c8_cpu_t *cpu, uint8_t vx) {
    dbg("Running: SKNP vx\n");

    if (!c8_keyboard_is_pressed(cpu->keyboard, cpu->v[vx])) {
        cpu->pc += 2;
    }
}

static void ld_vx_dt(c8_cpu_t *cpu, uint8_t vx) {
    dbg("Running: LD vx, dt\n");

    cpu->v[vx] = c8_timer_get_count(cpu->delay_timer);
}

static int ld_vx_k(c8_cpu_t *cpu, uint8_t vx) {
    dbg("Running: LD vx, k\n");

    for (int key = 0; key <= 0xF; key++) {
        if (c8_keyboard_is_pressed(cpu->keyboard, key)) {
            cpu->v[vx] = key;
            return 1;
        }
    }

    return 0;
}

static void ld_dt_vx(c8_cpu_t *cpu, uint8_t vx) {
    dbg("Running: LD dt, vx\n");

    c8_timer_set_count(cpu->delay_timer, cpu->v[vx]);
}

static void ld_st_vx(c8_cpu_t *cpu, uint8_t vx) {
    dbg("Running: LD st, vx\n");

    c8_timer_set_count(cpu->sound_timer, cpu->v[vx]);
}

static void add_i_vx(c8_cpu_t *cpu, uint8_t vx) {
    dbg("Running: ADD i, vx\n");

    cpu->i += cpu->v[vx];
}

static void ld_f_vx(c8_cpu_t *cpu, uint8_t vx) {
    dbg("Running: LD f, vx\n");

    cpu->i = cpu->v[vx] * C8_CHAR_SPRITE_HEIGHT;
}

static void ld_b_vx(c8_cpu_t *cpu, uint8_t vx) {
    dbg("Running: L b, vx\n");

    uint8_t value = cpu->v[vx];

    uint8_t units = value % 10;
    uint8_t tens = (value / 10) % 10;
    uint8_t hundreds = value / 100;

    c8_memory_write(cpu->memory, cpu->i, hundreds);
    c8_memory_write(cpu->memory, cpu->i + 1, tens);
    c8_memory_write(cpu->memory, cpu->i + 2, units);
}

static void ld_i_vx(c8_cpu_t *cpu, uint8_t vx) {
    dbg("Running: LD i, vx\n");

    for (uint8_t i = 0; i <= vx; i++) {
        c8_memory_write(cpu->memory, cpu->i + i, cpu->v[i]);
    }
}

static void ld_vx_i(c8_cpu_t *cpu, uint8_t vx) {
    dbg("Running: LD vx, i\n");

    for (uint8_t i = 0; i <= vx; i++) {
        c8_memory_read(cpu->memory, cpu->i + i, cpu->v + i);
    }
}

static int execute_opcode(c8_cpu_t *cpu, uint16_t opcode) {
    dbg("Decoding opcode: %04x\n", opcode);

    int increment_pc = 1;

    switch (opcode >> 12) {
        case 0x0:
            if (opcode == 0x00E0) {
                cls(cpu);
            } else if (opcode == 0x00EE) {
                ret(cpu);
            }

            break;

        case 0x1:
            jp_addr(cpu, opcode & 0x0FFF);

            increment_pc = 0;

            break;

        case 0x2:
            call_addr(cpu, opcode & 0xFFF);

            increment_pc = 0;

            break;

        case 0x3:
            se_vx_byte(cpu, (opcode >> 8) & 0xF, opcode & 0xFF);
            break;

        case 0x4:
            sne_vx_byte(cpu, (opcode >> 8) & 0xF, opcode & 0xFF);
            break;

        case 0x5:
            se_vx_vy(cpu, (opcode >> 8) & 0xF, (opcode >> 4) & 0xF);
            break;

        case 0x6:
            ld_vx_byte(cpu, (opcode >> 8) & 0xF, opcode & 0xFF);
            break;

        case 0x7:
            add_vx_byte(cpu, (opcode >> 8) & 0xF, opcode & 0xFF);
            break;

        case 0x8:
            switch (opcode & 0xF) {
                case 0x0:
                    ld_vx_vy(cpu, (opcode >> 8) & 0xF, (opcode >> 4) & 0xF);
                    break;

                case 0x1:
                    or_vx_vy(cpu, (opcode >> 8) & 0xF, (opcode >> 4) & 0xF);
                    break;

                case 0x2:
                    and_vx_vy(cpu, (opcode >> 8) & 0xF, (opcode >> 4) & 0xF);
                    break;

                case 0x3:
                    xor_vx_vy(cpu, (opcode >> 8) & 0xF, (opcode >> 4) & 0xF);
                    break;

                case 0x4:
                    add_vx_vy(cpu, (opcode >> 8) & 0xF, (opcode >> 4) & 0xF);
                    break;

                case 0x5:
                    sub_vx_vy(cpu, (opcode >> 8) & 0xF, (opcode >> 4) & 0xF);
                    break;

                case 0x6:
                    shr_vx(cpu, (opcode >> 8) & 0xF);
                    break;

                case 0x7:
                    subn_vx_vy(cpu, (opcode >> 8) & 0xF, (opcode >> 4) & 0xF);
                    break;

                case 0xE:
                    shl_vx(cpu, (opcode >> 8) & 0xF);
            }

            break;

        case 0x9:
            sne_vx_vy(cpu, (opcode >> 8) & 0xF, (opcode >> 4) & 0xF);
            break;

        case 0xA:
            ld_i_addr(cpu, opcode & 0x0FFF);
            break;

        case 0xB:
            jp_v0_addr(cpu, opcode & 0x0FFF);

            increment_pc = 0;

            break;

        case 0xC:
            rnd_vx_byte(cpu, (opcode >> 8) & 0xF, opcode & 0xFF);
            break;

        case 0xD:
            drw_vx_vy_nibble(cpu, (opcode >> 8) & 0xF, (opcode >> 4) & 0xF, opcode & 0xF);
            break;

        case 0xE:
            switch (opcode & 0xFF) {
                case 0x9E:
                    skp_vx(cpu, (opcode >> 8) & 0xF);
                    break;

                case 0xA1:
                    sknp_vx(cpu, (opcode >> 8) & 0xF);
            }

            break;

        case 0xF:
            switch (opcode & 0xFF) {
                case 0x07:
                    ld_vx_dt(cpu, (opcode >> 8) & 0xF);
                    break;

                case 0x0A:
                    increment_pc = ld_vx_k(cpu, (opcode >> 8) & 0xF);
                    break;

                case 0x15:
                    ld_dt_vx(cpu, (opcode >> 8) & 0xF);
                    break;

                case 0x18:
                    ld_st_vx(cpu, (opcode >> 8) & 0xF);
                    break;

                case 0x1E:
                    add_i_vx(cpu, (opcode >> 8) & 0xF);
                    break;

                case 0x29:
                    ld_f_vx(cpu, (opcode >> 8) & 0xF);
                    break;

                case 0x33:
                    ld_b_vx(cpu, (opcode >> 8) & 0xF);
                    break;

                case 0x55:
                    ld_i_vx(cpu, (opcode >> 8) & 0xF);
                    break;

                case 0x65:
                    ld_vx_i(cpu, (opcode >> 8) & 0xF);
            }
    }

    return increment_pc;
}

void c8_cpu_init(c8_cpu_t *cpu) {
    cpu->i = 0;
    cpu->pc = 0x200;
    cpu->sp = 0;

    memset(cpu->v, 0, 16);
    memset(cpu->stack, 0, 16 * 2);

    cpu->memory = NULL;
    cpu->display = NULL;
    cpu->delay_timer = NULL;
    cpu->sound_timer = NULL;
    cpu->keyboard = NULL;

    cpu->last_instruction_time = 0;
}

void c8_cpu_connect_memory(c8_cpu_t *cpu, c8_memory_t *memory) {
    cpu->memory = memory;
}

void c8_cpu_connect_display(c8_cpu_t *cpu, c8_display_t *display) {
    cpu->display = display;
}

void c8_cpu_connect_delay_timer(c8_cpu_t *cpu, c8_timer_t *timer) {
    cpu->delay_timer = timer;
}

void c8_cpu_connect_sound_timer(c8_cpu_t *cpu, c8_timer_t *timer) {
    cpu->sound_timer = timer;
}

void c8_cpu_connect_keyboard(c8_cpu_t *cpu, c8_keyboard_t *keyboard) {
    cpu->keyboard = keyboard;
}

void c8_cpu_run_next_instruction(c8_cpu_t *cpu) {
    uint32_t current_time = SDL_GetTicks();
    if (current_time - cpu->last_instruction_time >= C8_INSTRUCTION_TIME_MS) {
        cpu->last_instruction_time = current_time;

        uint8_t inst_msb, inst_lsb;
        c8_memory_read(cpu->memory, cpu->pc, &inst_msb);
        c8_memory_read(cpu->memory, cpu->pc + 1, &inst_lsb);

        uint16_t opcode = (((uint16_t) inst_msb) << 8) | inst_lsb;

        int increment_pc = execute_opcode(cpu, opcode);
        if (increment_pc) {
            cpu->pc += 2;
        }
    }
}
