#include "main.h"

// Создание нового узла дерева Хаффмана
MinHeapNode* newNode(unsigned char data, unsigned freq) {
    MinHeapNode* temp = (MinHeapNode*)malloc(sizeof(MinHeapNode));

    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;

    return temp;
}

// Создание минимальной кучи (очереди приоритетов) с заданной вместимостью
MinHeap* createMinHeap(unsigned capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));

    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (MinHeapNode**)malloc(minHeap->capacity * sizeof(MinHeapNode*));

    return minHeap;
}

// Обмен двух узлов минимальной кучи
void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b) {
    MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// Поддержание свойства минимальной кучи
void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if ((left < minHeap->size) && (minHeap->array[left]->freq < minHeap->array[smallest]->freq))
        smallest = left;

    if ((right < minHeap->size) && (minHeap->array[right]->freq < minHeap->array[smallest]->freq))
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

// Извлечение минимального узла из кучи
MinHeapNode* extractMin(MinHeap* minHeap) {
    MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size-- - 1];

    minHeapify(minHeap, 0);

    return temp;
}

// Вставка нового узла в кучу
void insertMinHeap(MinHeap* minHeap, MinHeapNode* minHeapNode) {
    int i = ++minHeap->size - 1;

    while (i && (minHeapNode->freq < minHeap->array[(i-1)/2]->freq)) {
        minHeap->array[i] = minHeap->array[(i-1)/2];
        
        i = (i - 1) / 2;
    }

    minHeap->array[i] = minHeapNode;
}

// Построение минимальной кучи
void buildMinHeap(MinHeap* minHeap) {
    int n = minHeap->size - 1;

    for (int i = (n - 1) / 2; i >= 0; i--) {
        minHeapify(minHeap, i);
    }
}

// Создание и построение минимальной кучи
MinHeap* createAndBuildMinHeap(unsigned char* data, int* freq, int size) {
    MinHeap* minHeap = createMinHeap(size);

    for (int i = 0; i < size; i++) {
        minHeap->array[i] = newNode(data[i], freq[i]);
    }

    minHeap->size = size;

    buildMinHeap(minHeap);

    return minHeap;
}

// Построение дерева Хаффмана
MinHeapNode* buildHuffmanTree(unsigned char* data, int* freq, int size) {
    MinHeapNode *left, *right, *top;

    MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    while (!(minHeap->size == 1)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = newNode('%', left->freq + right->freq);

        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }

    return extractMin(minHeap);
}

// Хранение кодов Хаффмана в виде битовых строк
void storeCodes(MinHeapNode* root, int* arr, int top, char codes[][MAX_TREE_HT]) {
    if (root->left) {
        arr[top] = 0;

        storeCodes(root->left, arr, top + 1, codes);
    }
    if (root->right) {
        arr[top] = 1;

        storeCodes(root->right, arr, top + 1, codes);
    }
    if (!(root->left) && !(root->right)) {
        for (int i = 0; i < top; i++) {
            codes[root->data][i] = arr[i];
        }

        codes[root->data][top] = -1;
    }
}

// Функция для подсчета частот символов в строке
void countFrequencies(const char* str, unsigned char** data, int** freq, int* numPairs) {
    int count[MAX_CHAR] = {0};
    int uniqueChars = 0, length = strlen(str), index = 0;

    for (int i = 0; i < length; i++) {
        if (count[(unsigned char)str[i]] == 0) uniqueChars++;

        count[(unsigned char)str[i]]++;
    }

    *data = (unsigned char*)malloc(uniqueChars * sizeof(unsigned char));
    *freq = (int*)malloc(uniqueChars * sizeof(int));

    for (int i = 0; i < MAX_CHAR; i++) {
        if (count[i] > 0) {
            (*data)[index] = (unsigned char)i;
            (*freq)[index] = count[i];

            index++;
        }
    }

    *numPairs = uniqueChars;
}

// Главная функция для кодирования Хаффмана
void HuffmanCodes(unsigned char* data, int* freq, int numPairs, FILE* file) {
    MinHeapNode* root = buildHuffmanTree(data, freq, numPairs);

    int arr[MAX_TREE_HT], top = 0;
    char codes[MAX_TREE_HT][MAX_TREE_HT] = {{0}};

    storeCodes(root, arr, top, codes);

    for (int i = 0; i < numPairs; i++) {
        fwrite(&data[i], sizeof(char), 1, file);
        fwrite(&freq[i], sizeof(int), 1, file);
    }
}

// Вспомогательная функция, которая возвращает закодированные данные
void getHuffmanEncodedData(const char* input, char* output, char codes[][MAX_TREE_HT], int inputSize, int* outputSize) {
    int j = 0, k = 0, index = 0;
    char mask = 0b00000001;

    for (int i = 0; i < inputSize; i++) {
        while (codes[(unsigned char)input[i]][j] != -1) {
            if (codes[(unsigned char)input[i]][j]) output[index] |= mask << (k % 8);

            if ((k++ % 8) == 7) index++;

            j++;
        }

        j = 0;

    }

    *outputSize = index + 1;
}

// Функция для декодирования данных
void decodeHuffmanData(const char* input, char* data, int* freq, int numPairs, int inputSize, int outputSize, FILE* file) {
    MinHeapNode* root = buildHuffmanTree(data, freq, numPairs);

    char mask = 0b00000001, last_symbol = 0;
    int k = 0, count = 0, count_output = 0;

    MinHeapNode* current = root;

    while (count < inputSize) {
        if (!current->left && !current->right) {
            if ((last_symbol == 0x0D) && (current->data == 0x0A));
            else fprintf(file, "%c", current->data);

            last_symbol = current->data;
            current = root;
            count_output++;
        }

        if (*input & (mask << (k % 8))) {
            current = current->right;
        } else {
            current = current->left;
        }

        if ((k++ % 8) == 7) {
            input++;
            count++;
        }

        if (count_output == outputSize) return;
    }
}