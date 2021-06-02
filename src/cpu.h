#pragma once

#include <stdint.h>

#define V0 0
#define V1 1
#define V2 2
#define V3 3
#define V4 4 
#define V5 5
#define V6 6
#define V7 7
#define V8 8
#define V9 9
#define VA 10
#define VB 11
#define VC 12
#define VD 13
#define VE 14
#define VF 15

#define DISPLAY_WIDTH 64
#define DISPLAY_HEIGHT 32
#define MEMORY_SIZE 0xFFF

#define HALT 1
#define ERROR -1
#define SUCCESS 0

#define INSTR(b1, b2) ((b1 << 8) | b2)
#define INSTR_OP(instruction) (instruction & 0xF000)
#define INSTR_X(instruction) (instruction & 0x0F00)
#define INSTR_Y(instruction) (instruction & 0x00F0)
#define INSTR_N(instruction) (instruction & 0x000F)
#define INSTR_NN(instruction) (instruction & 0x00FF)
#define INSTR_NNN(instruction) (instruction & 0x0FFF)

struct cpu_s {
    int cycles;
    int counter;
    bool render_flag;

    uint8_t stack[16];
    uint8_t memory[MEMORY_SIZE];
    uint32_t display[DISPLAY_HEIGHT * DISPLAY_WIDTH];

    // Stack pointer.
    uint8_t sp;

    // Program counter.
    uint16_t pc;

    // Used to store memory adresses.
    // Mostly the lowest (rightmost) 12 bits are used.
    uint16_t i;

    // Sound timer counter register. 
    uint8_t st;

    // Delay timer counter register. 
    uint8_t dt;

    uint8_t v[16];

    bool unknown_instructions;
};

int cpu_init(struct cpu_s * cpu, int cycles);
int cpu_clock(struct cpu_s * cpu);

int cpu_load_rom(
    struct cpu_s * cpu,
    uint8_t * program,
    size_t program_len
);

int cpu_pixel_enable(
    struct cpu_s * cpu,
    unsigned x,
    unsigned y
);

int cpu_pixel_disable(
    struct cpu_s * cpu,
    unsigned x,
    unsigned y
);
