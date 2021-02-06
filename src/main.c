#include <assert.h>
#include <stdbool.h>
#include <SDL.h>

#include "cpu.h"

void chip8_run_limited(struct cpu_s * cpu, unsigned count)
{
    while (count > 0) {
        cpu_clock(cpu);
        count -= 1;
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
    chip8_run_limited(&cpu, 8);

    return 0;
}
