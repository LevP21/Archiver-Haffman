#include "main.h"

// Распаковка с использованием декодирования Хаффмана
int unpack_with_Haffman(const char* filename) {
    char input[MAX_SIZE] = {0};
    int fileSize = 0, encodeSize = 0, numPairs = 0, outputSize = 0;

    FILE* file_in;
    FILE* file_out;

    file_in = fopen(filename, "rb");

    if (file_in == NULL) {
        fprintf(stderr, "Error: file %s not found\n", filename);
        fclose(file_in);

        return 1;
    }

    fseek(file_in, 0, SEEK_END);
    fileSize = ftell(file_in);
    rewind(file_in);

    fread(&numPairs, sizeof(int), 1, file_in);

    if (fileSize > MAX_SIZE || numPairs > MAX_SIZE) {
        fprintf(stderr, "Error: invalid input file");
        fclose(file_in);

        return 1;
    }
    
    unsigned char* data = (unsigned char*)malloc(numPairs);
    int* freq = (int*)malloc(numPairs * sizeof(int));

    for (int i = 0; i < numPairs; i++) {
        fread(&data[i], sizeof(char), 1, file_in);
        fread(&freq[i], sizeof(int), 1, file_in);
    }

    fread(&encodeSize, sizeof(int), 1, file_in);
    fread(&outputSize, sizeof(int), 1, file_in);
    fread(input, sizeof(char), encodeSize, file_in);

    file_out = fopen("output.txt", "w");

    decodeHuffmanData(input, data, freq, numPairs, encodeSize, outputSize, file_out);

    free(data);
    free(freq);

    fclose(file_in);
    fclose(file_out);

    fprintf(stdout, "Unpacking was successful");

    return 0;
}