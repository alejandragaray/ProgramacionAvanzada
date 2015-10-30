#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>
#include <bits/pthreadtypes.h>

#define ENANOS 7
#define SILLAS 4

pthread_mutex_t mutex_b;

pthread_mutex_t mutex_e[ENANOS];

pthread_cond_t esperando_turno;

sem_t semaf_s;

void crear_threads(int size, pthread_t *threads, void *(*func)(void *));

void *blancanieves(void *arg);

void *enanito(void *arg);

int ciclo = 1;

int main() {
    srand(time(NULL));
    
    pthread_mutex_init(&mutex_b, NULL);
    
    pthread_cond_init(&esperando_turno, 0);
    
    sem_init(&semaf_s, 0, SILLAS);
    
    int i;
    for (i = 0; i < ENANOS; ++i) {
        pthread_mutex_init(&mutex_e[i], NULL);
        pthread_mutex_lock(&mutex_e[i]);
    }
    
    pthread_t enanito_threads[ENANOS];
    crear_threads(ENANOS, enanito_threads, enanito);
    
    pthread_t blancanieves_t[1];
    crear_threads(1, blancanieves_t, blancanieves);
    
    for (i = 0; i < ENANOS; ++i) {
        pthread_join(enanito_threads[i], NULL);
    }
    
    pthread_join(blancanieves_t[1], NULL);
    
    pthread_cond_destroy(&esperando_turno);
    
    pthread_exit(NULL);
    
}

void crear_threads(int size, pthread_t *threads, void *(*func)(void *)) {
    int i;
    int ids[size];
    for (i = 0; i < size; ++i) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, func, &ids[i]);
    }
}

void *blancanieves(void *arg) {
    int id = *(int *) arg;
    while (ciclo) {
        pthread_mutex_lock(&mutex_b);
        printf("\nCocinando..\n", id);
        usleep(rand() % 10000000);
        printf("Platillo listo\n", id);
        printf("Sali a dar una vuelta\n", id);
        pthread_cond_signal(&esperando_turno);
    }
}

void *enanito(void *arg) {
    int id = *(int *) arg;
    while (ciclo) {
        printf("el enanito %i esta en la mina\n", id);
        usleep(rand() % 10000000);
        printf("el enanito %i busca donde sentarse\n", id);
        sem_wait(&semaf_s);
        printf("el enanito %i encontro lugar\n", id);
        pthread_mutex_unlock(&mutex_b);
        pthread_cond_wait(&esperando_turno, &mutex_e[id]);
        printf("el enanito %i esta comiendo\n", id);
        usleep(rand() % 10000000);
        printf("el enanito %i termino\n", id);
        sem_post(&semaf_s);
    }
}