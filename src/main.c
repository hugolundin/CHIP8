#include <assert.h>
#include <stdbool.h>
#include <SDL.h>

#include "cpu.h"
#include "display.h"

static size_t open_file(char const * const filename, uint8_t * buf)
{
    FILE * file = fopen(filename, "rb");
    if (NULL == file) {
        return -1;
    }

    size_t bytes_written = fread(&buf[0], 1, MEMORY_SIZE, file);
    if (bytes_written < 0) {
        return -1;
    }

    int ret = fclose(file);
    if (ret < 0) {
        return -1;
    }

    return bytes_written;
}

static void dump_rom(uint8_t * buf, size_t buf_len)
{
    for (size_t i = 0; i < buf_len; i++) {
        printf("%x\n", buf[i]);
    }
}

int main(int argc, char ** argv)
{
    int ret = 0;
    struct cpu_s cpu = {0};
    size_t bytes_written = 0;
    uint8_t buf[MEMORY_SIZE];
    struct display_s display = {0};

    ret = display_init(&display, DISPLAY_WIDTH, DISPLAY_HEIGHT);
    if (ret < 0) {
        exit(EXIT_FAILURE);
    }

    bytes_written = open_file("/Users/hugolundin/Developer/personal/chip8/roms/ibm_logo.ch8", buf);
    if (bytes_written <= 0) {
        exit(EXIT_FAILURE);
    }

    ret = cpu_init(&cpu, -1);
    if (ret < 0) {
        exit(EXIT_FAILURE);
    }

    ret = cpu_load_rom(&cpu, buf, bytes_written);
    if (ret < 0) {
        exit(EXIT_FAILURE);
    }

    SDL_Event event;
    bool running = true;
    
    while (running) {
        ret = cpu_clock(&cpu);
        if (ret < 0) {
            running = false;
        }

        if (cpu.render_flag) {
            display_render(&display, &cpu);
        }
        
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }

            if (event.type == SDL_KEYDOWN) {
                cpu.render_flag = true;
            }
        }
    }

    if (cpu.unknown_instructions) {
        printf("Unknown instructions found.\n");
    }

    display_deinit(&display);
    return 0;
}
