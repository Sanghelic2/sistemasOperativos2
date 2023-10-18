#include <pthread.h>
#include <stdio.h>

int saldo = 0;
#define NUM_HILOS 100
#define REPETICIONES 100
pthread_spinlock_t spinlock;

void * sumaSaldo(void *arg) {
    for (int i = 0; i < REPETICIONES; i++) {
        pthread_spin_lock(&spinlock);
        saldo += 100;
        pthread_spin_unlock(&spinlock);
        printf("Valor actual de saldo en el hilo: %d\n", saldo);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t hilos[NUM_HILOS];
    pthread_spin_init(&spinlock, PTHREAD_PROCESS_PRIVATE);

    for (int i = 0; i < NUM_HILOS; i++) {
        pthread_create(&hilos[i], NULL, sumaSaldo, NULL);
    }

    for (int i = 0; i < NUM_HILOS; i++) {
        pthread_join(hilos[i], NULL);
    }

    pthread_spin_destroy(&spinlock);

    printf("Saldo final: %d\n", saldo);

    pthread_exit(NULL);
}