#include "c8_cpu.h"

static void cls() {
}

static void ret() {
}

static void sys_addr() {
}

static void jp_addr(uint16_t addr) {
}

static void call_addr(uint16_t addr) {
}

static void se_vx_byte(uint8_t vx, uint8_t byte) {
}

static void sne_vx_byte() {
}

static void se_vx_vy() {
}

static void ld_vx_byte() {
}

static void add_vx_byte() {
}

static void ld_vx_vy() {
}

static void or_vx_vy() {
}

static void and_vx_vy() {
}

static void xor_vx_vy() {
}

static void add_vx_vy() {
}

static void sub_vx_vy() {
}

static void shr_vx_vy() {
}

static void subn_vx_vy() {
}

static void shl_vx_vy() {
}

static void sne_vx_vy() {
}

static void ld_i_addr() {
}

static void jp_v0_addr() {
}

static void rnd_vx_byte() {
}

static void drw_vx_vy_nibble() {
}

static void skp_vx() {
}

static void sknp_vx() {
}

static void ld_vx_dt() {
}

static void ld_vx_k() {
}

static void ld_dt_vx() {
}

static void ld_st_vx() {
}

static void add_i_vx() {
}

static void ld_f_vx() {
}

static void ld_b_vx() {
}

static void ld_i_vx() {
}

static void ld_vx_i() {
}

void execute_opcode(uint16_t opcode) {
    uint8_t ms_nibble = opcode >> 12;

    switch (ms_nibble) {
        case 0x0:
            if (opcode == 0x00E0) {
                cls();
            } else if (opcode == 0x00EE) {
                ret();
            }

            break;

        case 0x1:
            jp_addr(opcode & 0x0FFF);
            break;

        case 0x2:
            call_addr(opcode & 0xFFF);
            break;

        case 0x3:
            se_vx_byte((opcode >> 8) & 0xF, opcode & 0xFF);
            break;

        case 0x4:
            break;

        case 0x5:
            break;

        case 0x6:
            break;

        case 0x7:
            break;

        case 0x8:
            break;

        case 0x9:
            break;

        case 0xA:
            break;

        case 0xB:
            break;

        case 0xC:
            break;

        case 0xD:
            break;

        case 0xE:
            break;

        case 0xF:
    }
}
