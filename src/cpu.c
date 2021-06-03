#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include <assert.h>

#include "cpu.h"
#include "instructions.h"

static int cpu_vram_get(
    struct cpu_s * cpu, unsigned x, unsigned y
)
{
    return cpu->display[x + (y * DISPLAY_WIDTH)];
}

static int cpu_vram_set(
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
    return cpu_vram_set(cpu, x, y, 0xFFFFFFFF);
}

int cpu_pixel_disable(struct cpu_s * cpu, unsigned x, unsigned y)
{
    return cpu_vram_set(cpu, x, y, 0xFF000000);
}

int cpu_clear_vram(struct cpu_s * cpu)
{
    int ret = 0; 

    for (int x = 0; x < DISPLAY_WIDTH; x++) {
        for (int y = 0; y < DISPLAY_HEIGHT; y++) {
            ret = cpu_pixel_disable(cpu, x, y);
            if (ret < 0) {
                return -1;
            }
        }
    }

    return 0;
}

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
    uint16_t instruction = INSTR(b1, b2);

    switch (INSTR_OP(instruction)) {

        // Clear screen
        case 0x0000:
            switch (INSTR_NN(instruction)) {
                case 0x00E0:
                    cpu_clear_vram(cpu);
                    break;

                default:
                    break;
            }

            break;

        // Set pc 
        case 0x1000:
            cpu->pc = INSTR_NNN(instruction);
            break;

        // printf("6XINSTR_NN: Set register V%d to %d\n", X(instruction), INSTR_NN(instruction));
        case 0x6000: {
            uint8_t reg = INSTR_X(instruction);
            uint8_t value = INSTR_NN(instruction);
            cpu->v[reg] = value;

            break;
        }

        // printf("7XINSTR_NN: Add %d to register V%d\n", INSTR_NN(instruction), X(instruction));
        case 0x7000: {
            uint8_t reg = INSTR_X(instruction);
            uint8_t value = INSTR_NN(instruction);
            cpu->v[reg] += value;
            break;
        }

        // printf("AINSTR_NNN: Set register I to %d\n", INSTR_NNN(instruction));
        case 0xA000:
            cpu->i = INSTR_NNN(instruction);
            break;

        case 0xD000: {
            cpu->v[VF] = 0;
            uint8_t x = cpu->v[INSTR_X(instruction)] % DISPLAY_WIDTH;
            uint8_t y = cpu->v[INSTR_Y(instruction)] % DISPLAY_HEIGHT;


            for (int i = 0; i < INSTR_N(instruction); i++) {

                // Not really sure about this, when do we change it? 
                uint8_t sprite_data = cpu->memory[cpu->i];

                // Go through all bits.
                for (int j = 0; j < 8; j++) {

                    // Get the bit at the current position.
                    uint8_t sprite_bit = ((sprite_data >> j) % 2);
                    uint8_t display_bit = cpu_vram_get(cpu, x, y);
                    
                    if (sprite_bit & display_bit) {
                        printf("hej!\n");
                        cpu_pixel_enable(cpu, x, y);
                        cpu->v[VF] = 1;
                    } else if (sprite_bit & !display_bit) {
                        cpu_pixel_enable(cpu, x, y);
                    }

                    if (x == DISPLAY_WIDTH - 1) {
                        break;
                    }

                    x += 1;
                }

                y += 1;
            }

            break;
        }


        default:
            break;
    }

    return 0;
}

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
