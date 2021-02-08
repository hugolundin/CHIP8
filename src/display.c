#include <SDL.h>
#include "display.h"

int display_init(struct display_s * display, int width, int height)
{
    SDL_Init(SDL_INIT_VIDEO);
    display->width = width;
    display->height = height;

    display->window = SDL_CreateWindow(
        /* title = */ "CHIP-8",
        /* x = */ SDL_WINDOWPOS_UNDEFINED,
        /* y = */ SDL_WINDOWPOS_UNDEFINED,
        /* w = */ display->width * SCALE,
        /* h = */ display->height * SCALE,
        /* flags = */ SDL_WINDOW_SHOWN
    );

    if (NULL == display->window) {
        return -1;
    }

    display->renderer = SDL_CreateRenderer(
        /* window = */ display->window,
        /* index = */ -1,
        /* flags = */ SDL_RENDERER_ACCELERATED
    );

    if (NULL == display->renderer) {
        return -1;
    }

    display->texture = SDL_CreateTexture(
        /* renderer = */ display->renderer,
        /* format = */ SDL_PIXELFORMAT_ARGB8888,
        /* access = */ SDL_TEXTUREACCESS_STATIC,
        /* w = */ display->width,
        /* h = */ display->height
    );

    if (NULL == display->texture) {
        return -1;
    }

    return 0;
} 

void display_deinit(struct display_s * display)
{
    SDL_DestroyTexture(display->texture);
    SDL_DestroyRenderer(display->renderer);
    SDL_DestroyWindow(display->window);
    SDL_Quit();
}

int display_render(struct display_s * display, uint32_t * buf)
{
    int ret = 0;

    ret = SDL_UpdateTexture(
        /* texture = */ display->texture,
        /* rect = */ NULL,
        /* pixels = */ buf,
        /* pitch = */ display->width * sizeof(uint32_t)
    );

    ret = SDL_RenderCopy(
        /* renderer = */ display->renderer,
        /* texture = */ display->texture,
        /* src_rect = */ NULL,
        /* dest_rect = */ NULL
    );

    SDL_RenderPresent(display->renderer);
    return 0;
}
