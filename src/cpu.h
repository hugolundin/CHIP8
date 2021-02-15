#pragma once

#include <stdint.h>

#define DISPLAY_WIDTH 64
#define DISPLAY_HEIGHT 32
#define MEMORY_SIZE 0xFFF

struct cpu_s{
    int counter;
    bool render_flag;

    uint8_t memory[MEMORY_SIZE];
    uint32_t display[DISPLAY_HEIGHT * DISPLAY_WIDTH];

    // Stack pointer.
    uint8_t SP;

    // Program counter.
    uint16_t PC;

    // Used to store memory adresses.
    // Mostly the lowest (rightmost) 12 bits are used.
    uint16_t I;

    // Sound timer counter register. 
    uint8_t ST;

    // Delay timer counter register. 
    uint8_t DT;
    
    // General purpose registers. 
    uint8_t V0;
    uint8_t V1;
    uint8_t V2;
    uint8_t V3;
    uint8_t V4;
    uint8_t V5;
    uint8_t V6;
    uint8_t V7;
    uint8_t V8;
    uint8_t V9;
    uint8_t VA;
    uint8_t VB;
    uint8_t VC;
    uint8_t VD;
    uint8_t VE;

    // Shouldn't be used by user programs.
    // Is used as a flag register by some instructions.
    uint8_t VF;
};

void cpu_init(struct cpu_s * cpu);
void cpu_clock(struct cpu_s * cpu);

int cpu_load_program(
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
