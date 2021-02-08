#include <assert.h>
#include <stdbool.h>
#include <SDL.h>

#include "cpu.h"

int main(int argc, char ** argv)
{
    struct cpu_s cpu = {0};
    
    int scale = 10;
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window * screen = SDL_CreateWindow(
        /* title = */ "CHIP-8",
        /* x = */ SDL_WINDOWPOS_CENTERED,
        /* y = */ SDL_WINDOWPOS_CENTERED,
        /* w = */ 64 * scale,
        /* h = */ 32 * scale,
        /* flags = */ SDL_WINDOW_OPENGL
    );

    SDL_Renderer * renderer = SDL_CreateRenderer(
        /*screen = */ screen,
        /* index = */ -1,
        /* flags = */ 0
    );

    SDL_Event event;

    for (;;) {
        while (SDL_PollEvent(&event));
    }

    return 0;
}
