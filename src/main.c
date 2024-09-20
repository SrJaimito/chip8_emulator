#include <stdio.h>
#include <stdlib.h>

#include "chip_8.h"

int main(int argc, char *argv[]) {
    chip_8_t chip_8;
    c8_error_e error;

    error = chip_8_init(&chip_8, argv[1]);
    switch (error) {
        case C8_SDL_INIT_ERROR:
            fprintf(stderr, "C8_SDL_INIT_ERROR\n");
            break;

        case C8_ALLOC_ERROR:
            fprintf(stderr, "C8_ALLOC_ERROR\n");
            break;

        case C8_FILE_ERROR:
            fprintf(stderr, "C8_FILE_ERROR\n");
            break;

        case C8_MEMSIZ_ERROR:
            fprintf(stderr, "C8_MEMSIZ_ERROR\n");
            break;

        case C8_DISPLAY_INIT_ERROR:
            fprintf(stderr, "C8_DISPLAY_INIT_ERROR\n");
            break;

        default:
            printf("Chip-8 init success\n");
    }

    chip_8_run(&chip_8);

    return EXIT_SUCCESS;
}
