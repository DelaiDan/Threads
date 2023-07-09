
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 16 // Quantidade de Threads
#define NUM_ELEMENTS 52 // Quantidade de elementos no Array

//Variaveis da logica
typedef struct {
    int num1;
    int num2;
} ThreadArgs;

int FJ(int n, int k){
    if (n==1){
        return 0;
    }

    return (FJ(n-1,k) + k) %n;
}

//Logica do Problema
void *threadFunc(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    int result = FJ(args->num1, args->num2);
    printf("Resultado = %d\n", result);
    pthread_exit(NULL);
}

int main() {
    int input[NUM_ELEMENTS] = {13, 86, 75, 97, 76, 58, 74, 26, 32, 83, 40, 16, 52, 99, 3, 75, 77, 37, 54, 50, 21, 42, 43, 82, 14, 39, 29, 57, 16, 82, 69, 97, 58, 39, 51, 30, 39, 88, 68, 39, 71, 62, 47, 96, 14, 60, 95, 62, 11, 9, 55, 44};
    pthread_t threads[NUM_THREADS];
    ThreadArgs threadArgs[NUM_THREADS];

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

    return 0;
}
