#include <assert.h>
#include <stdbool.h>
#include <SDL.h>

#include "cpu.h"
#include "display.h"

int main(int argc, char ** argv)
{
    int ret = 0;
    struct cpu_s cpu = {0};
    struct display_s display = {0};

    ret = display_init(&display, DISPLAY_WIDTH, DISPLAY_HEIGHT);
    if (ret < 0) {
        exit(EXIT_FAILURE);
    }

    SDL_Event event;
    bool running = true;
    
    while (running) {
        display_render(&display, cpu.display);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
    }

    display_deinit(&display);
    return 0;
}
