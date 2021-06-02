#pragma once
#include "cpu.h"

#include <SDL.h>

#define SCALE 10

struct display_s {
    int width;
    int height;
    SDL_Window * window;
    SDL_Renderer * renderer;
    SDL_Texture * texture;
};

int display_init(
    struct display_s * display,
    int width,
    int height
);

void display_deinit(
    struct display_s * display
);

int display_render(
    struct display_s * display,
    struct cpu_s * cpu
);

