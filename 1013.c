
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 16 // Quantidade de Threads
#define NUM_ELEMENTS 51 // Quantidade de elementos no Array

//Variaveis da logica
typedef struct {
    int num1;
    int num2;
    int num3;
} ThreadArgs;

//Logica do Problema
void *threadFunc(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;

    int maior = (args->num1 + args->num2 +abs(args->num1 - args->num2))/2;
    int maior2 = (maior + args->num3 + abs(maior - args->num3))/2;

    printf("Comparando %d %d e %d - MAIOR = %d\n", args->num1, args->num2, args->num3, maior2);
    pthread_exit(NULL);
}

int main() {
    int input[NUM_ELEMENTS] = {13, 86, 75, 97, 76, 58, 74, 26, 32, 83, 40, 16, 52, 99, 3, 75, 77, 37, 54, 50, 21, 42, 43, 82, 14, 39, 29, 57, 16, 82, 69, 97, 58, 39, 51, 30, 39, 88, 68, 39, 71, 62, 47, 96, 14, 60, 95, 62, 11, 9, 60};
    pthread_t threads[NUM_THREADS];
    ThreadArgs threadArgs[NUM_THREADS];

    // Cria as threads e aloca as variaveis da logica
    for (int i = 0; i < NUM_ELEMENTS; i += 3) {
        threadArgs[i % NUM_THREADS].num1 = input[i];
        threadArgs[i % NUM_THREADS].num2 = input[i + 1];
        threadArgs[i % NUM_THREADS].num3 = input[i + 2];
        pthread_create(&threads[i % NUM_THREADS], NULL, threadFunc, (void *)&threadArgs[i % NUM_THREADS]);
    }

    //Espera acabar
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
