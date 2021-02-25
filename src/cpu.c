#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "cpu.h"
#include "instructions.h"

//------------------------------------------------------
// Video memory management
//------------------------------------------------------

static int cpu_pixel_set(
    struct cpu_s * cpu, unsigned x, unsigned y, int32_t color
)
{
    if (x < 0 || x >= DISPLAY_WIDTH || y < 0 || y >= DISPLAY_HEIGHT) {
        return -1;
    }

    cpu->display[x + (y * DISPLAY_WIDTH)] = color;
    cpu->render_flag = true;

    return 0;
}

int cpu_pixel_enable(struct cpu_s * cpu, unsigned x, unsigned y)
{
    return cpu_pixel_set(cpu, x, y, 0xFFFFFFFF);
}

int cpu_pixel_disable(struct cpu_s * cpu, unsigned x, unsigned y)
{
    return cpu_pixel_set(cpu, x, y, 0xFF000000);
}

//------------------------------------------------------
// CPU management
//------------------------------------------------------

int cpu_init(struct cpu_s * cpu, int cycles)
{
    cpu->cycles = cycles;

    return 0;
}

int cpu_clock(struct cpu_s * cpu)
{   
    if (cpu->cycles > 0) {
        cpu->cycles -= 1;
    } else if (cpu->cycles == 0) {
        return HALT;
    }

    cpu->cycles -= 1;
    uint8_t b1 = cpu->memory[cpu->pc];
    uint8_t b2 = cpu->memory[cpu->pc + 1];
    cpu->pc = (cpu->pc + 2) % MEMORY_SIZE;

    // Combine them into a 16-bit instruction. 
    uint16_t instruction = INSTRUCTION(b1, b2);

    switch (OP(instruction)) {
        case 0x0000:
            switch (NN(instruction)) {
                case 0x00E0:
                    printf("00E0: Clear screen\n");
                    break;

                default:
                    printf("--- Unknown instruction: %04X\n", instruction);
                    break;
            }

            break;

        case 0x1000:
            printf("1NNN: PC = %d\n", NNN(instruction));
            break;

        case 0x6000:
            printf("6XNN: Set register V%d to %d\n", X(instruction), NN(instruction));
            break;

        case 0x7000:
            printf("7XNN: Add %d to register V%d\n", NN(instruction), X(instruction));
            break;

        case 0xA000:
            printf("ANNN: Set register I to %d\n", NNN(instruction));
            break;

        case 0xD000:
            printf("DXYN: Display/draw\n");
            break;

        default:
            printf("--- Unknown instruction: %04X\n", instruction);
            break;
    }

    return 0;
}

//------------------------------------------------------
// Program memory management
//------------------------------------------------------

int cpu_load_rom(
    struct cpu_s * cpu,
    uint8_t * program,
    size_t program_len
)
{
    if (program_len >= MEMORY_SIZE) {
        return -1;
    }

    for (size_t i = 0; i < program_len; i++) {
        cpu->memory[i] = program[i];
    }

    return 0;
}
