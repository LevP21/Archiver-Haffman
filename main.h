#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 524288

int compress_with_Haffman(const char* filename);
int unpack_with_Haffman(const char* filename);

#define MAX_TREE_HT 256
#define MAX_CHAR 256

// Узел дерева Хаффмана
typedef struct MinHeapNode {
    unsigned char data;
    unsigned freq;
    struct MinHeapNode *left, *right;
} MinHeapNode;

// Очередь приоритетов (минимальная куча)
typedef struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct MinHeapNode** array;
} MinHeap;

MinHeapNode* newNode(unsigned char data, unsigned freq);

MinHeap* createMinHeap(unsigned capacity);

void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b);

void minHeapify(MinHeap* minHeap, int idx);

MinHeapNode* extractMin(MinHeap* minHeap);

void insertMinHeap(MinHeap* minHeap, MinHeapNode* minHeapNode);

void buildMinHeap(MinHeap* minHeap);

MinHeap* createAndBuildMinHeap(unsigned char* data, int* freq, int size);

MinHeapNode* buildHuffmanTree(unsigned char* data, int* freq, int size);

void storeCodes(MinHeapNode* root, int* arr, int top, char codes[][MAX_TREE_HT]);

void countFrequencies(const char* str, unsigned char** data, int** freq, int* numPairs);

void HuffmanCodes(unsigned char* data, int* freq, int numPairs, FILE* file);

void getHuffmanEncodedData(const char* input, char* output, char codes[][MAX_TREE_HT], int inputSize, int* outputSize);

void decodeHuffmanData(const char* input, char* data, int* freq, int numPairs, int inputSize, int outputSize, FILE* file);