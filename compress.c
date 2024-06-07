#include "main.h"

// Сжатие с использованием кодирования Хаффмана
int compress_with_Haffman(const char* filename) {
    char input[MAX_SIZE] = {0};
    int fileSize = 0, outputSize = 0, numPairs = 0;

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

    if (fileSize > MAX_SIZE) {
        fprintf(stderr, "The file size exceeds the size allowed for compression");
        fclose(file_in);

        return 1;
    }

    fread(input, sizeof(char), fileSize, file_in);

    unsigned char* data;
    int* freq;

    countFrequencies(input, &data, &freq, &numPairs);

    file_out = fopen("en_input.txt", "wb");

    fwrite(&numPairs, sizeof(int), 1, file_out);

    HuffmanCodes(data, freq, numPairs, file_out);

    char output[MAX_SIZE] = {0};
    char codes[MAX_TREE_HT][MAX_TREE_HT] = {{0}};

    MinHeapNode* root = buildHuffmanTree(data, freq, numPairs);

    int arr[MAX_TREE_HT], top = 0;

    storeCodes(root, arr, top, codes);

    getHuffmanEncodedData(input, output, codes, fileSize, &outputSize);

    fwrite(&outputSize, sizeof(int), 1, file_out);
    fwrite(&fileSize, sizeof(int), 1, file_out);
    fwrite(output, sizeof(char), outputSize, file_out);

    fclose(file_in);
    fclose(file_out);

    fprintf(stdout, "Compression was successful");

    return 0;
}