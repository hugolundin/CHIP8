#include <assert.h>
#include <stdbool.h>
#include <SDL.h>

#include "cpu.h"

void chip8_run_cycles(struct cpu_s * cpu, unsigned cycles)
{
    while (cycles > 0) {
        cpu_clock(cpu);
        cycles -= 1;
    }
}

void chip8_run(struct cpu_s * cpu)
{
    for (;;) {
        cpu_clock(cpu);
    }
}

int main(int argc, char ** argv)
{
    struct cpu_s cpu = {0};
    chip8_run_cycles(&cpu, 5);

    return 0;
}
