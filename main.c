#include "main.h"

// Главная функция архиватора
int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <compress|unpack>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    const char *command = argv[2];

    if (strcmp(command, "compress") == 0) {
        compress_with_Haffman(filename);
    } else if (strcmp(command, "unpack") == 0) {
        unpack_with_Haffman(filename);
    } else {
        fprintf(stderr, "Error: unknown command %s\n", command);
        return 1;
    }

    return 0;
}