#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 4 // Quantidade de Threads
#define NUM_ELEMENTS 50 // Quantidade de elementos no Array

typedef struct {
    int num1;
    int num2;
} ThreadArgs;

void *threadFunc(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    int dif = args->num1 + args->num2;
    printf("SOMA = %d\n", dif);
    pthread_exit(NULL);
}

int main() {
    int input[NUM_ELEMENTS] = {49, 89, 127, 160, 81, 67, 133, 24, 44, 174, 181, 107, 39, 96, 37, 116, 187, 155, 186, 91, 13, 140, 36, 156, 79, 183, 84, 66, 10, 151, 167, 5, 86, 143, 76, 20, 29, 63, 128, 18, 22, 122, 68, 150, 180, 98, 21, 31, 70, 191};
    pthread_t threads[NUM_THREADS];
    ThreadArgs threadArgs[NUM_THREADS];

    // Criar as threads
    clock_t start = clock();
    for (int i = 0; i < NUM_ELEMENTS; i += 2) {
        threadArgs[i % NUM_THREADS].num1 = input[i];
        threadArgs[i % NUM_THREADS].num2 = input[i + 1];
        pthread_create(&threads[i % NUM_THREADS], NULL, threadFunc, (void *)&threadArgs[i % NUM_THREADS]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    clock_t end = clock();

    double elapsedTime = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Tempo: %.6f \n", elapsedTime);

    return 0;
}
