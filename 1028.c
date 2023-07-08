
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 8 // Quantidade de Threads
#define NUM_ELEMENTS 40 // Quantidade de elementos no Array

//Variaveis da logica
typedef struct {
    int num1;
    int num2;
} ThreadArgs;

int pilhasFigurinhas(int f2, int f1){
    if(f1==0) return f2;
    return pilhasFigurinhas(f1, f2%f1);
}

//Logica do Problema
void *threadFunc(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    int result = pilhasFigurinhas(args->num2, args->num1);
    printf("Resultado = %d\n", result);
    pthread_exit(NULL);
}

int main() {
    int input[NUM_ELEMENTS] = {13, 86, 75, 97, 76, 58, 74, 26, 32, 83, 40, 16, 52, 99, 3, 75, 77, 37, 54, 50, 21, 42, 43, 82, 14, 39, 29, 57, 16, 82, 69, 97, 58, 39, 51, 30, 39, 88, 68};
    pthread_t threads[NUM_THREADS];
    ThreadArgs threadArgs[NUM_THREADS];

    clock_t start = clock();

    // Cria as threads e aloca as variaveis da logica
    for (int i = 0; i < NUM_ELEMENTS; i += 2) {
        threadArgs[i % NUM_THREADS].num1 = input[i];
        threadArgs[i % NUM_THREADS].num2 = input[i + 1];
        pthread_create(&threads[i % NUM_THREADS], NULL, threadFunc, (void *)&threadArgs[i % NUM_THREADS]);
    }

    //Espera acabar
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_t end = clock();

    double elapsedTime = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Tempo: %.6f \n", elapsedTime);

    return 0;
}
