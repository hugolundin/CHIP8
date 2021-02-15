#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "cpu.h"
#include "instructions.h"

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

void cpu_init(struct cpu_s * cpu)
{

}

void cpu_clock(struct cpu_s * cpu)
{
    int ret = 0;
    cpu->PC += 2;
}

int cpu_load_program(
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
