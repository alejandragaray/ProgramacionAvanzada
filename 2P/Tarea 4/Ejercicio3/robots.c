#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


#define ROBOTS 10
#define NIVELES 10

typedef struct {
    int limite_peso;
    int peso_real;
} nivel;

pthread_mutex_t mutex_lvl[NIVELES];

pthread_cond_t lvl_filtro[NIVELES];

nivel niveles[NIVELES];

int ciclo = 1;

void *robot(void *arg);

void crear_threads(int tamano, pthread_t *threads, void *(*func)(void *));

void siguiente_nivel(int id, int nivel, int peso);

int main() {
    srand(time(NULL));
    
    int i;
    for (i = 0; i < NIVELES; ++i) {
        niveles[i].peso_real = 0;
        niveles[i].limite_peso = rand() % 20 + 15;
        printf("Creating nivel with max peso: %i\n", niveles[i].limite_peso);
    }
    
    for (i = 0; i < NIVELES; ++i) {
        pthread_mutex_init(&mutex_lvl[i], NULL);
        pthread_cond_init(&lvl_filtro[i], NULL);
    }
    
    pthread_t robot_t[ROBOTS];
    crear_threads(ROBOTS, robot_t, robot);
    
    for (i = 0; i < ROBOTS; ++i) {
        pthread_join(robot_t[i], NULL);
    }
    
    return 0;
}


void crear_threads(int tamano, pthread_t *threads, void *(*func)(void *)) {
    int i;
    int ids[tamano];
    for (i = 0; i < tamano; ++i) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, func, &ids[i]);
    }
}

void *robot(void *arg) {
    int id = *(int *) arg;
    int peso = rand() % 10 + 10;
    int nivel_actual = 0;
    while (ciclo) {
        usleep(rand() % 2000000);
        printf("El robot %i esta en el nivel %i\n", id, nivel_actual);
        if (nivel_actual >= NIVELES) {
            nivel_actual = 0;
        } else {
            siguiente_nivel(id, nivel_actual, peso);
            ++nivel_actual;
        }
    }
    pthread_exit(NULL);
}

void siguiente_nivel(int id, int nivel, int peso) {
    pthread_mutex_lock(&mutex_lvl[nivel]);
    while (niveles[nivel].peso_real + peso > niveles[nivel].limite_peso) {
        printf("El robot %i del nivel %i tiene peso de: %i y su limite es: %i) | Mi peso: %i\n",
               id,
               nivel,
               niveles[nivel].peso_real,
               niveles[nivel].limite_peso,
               peso);
        
        pthread_cond_wait(&lvl_filtro[nivel], &mutex_lvl[nivel]);
    }
    
    if (nivel > 0) {
        niveles[nivel - 1].peso_real -= peso;
        pthread_cond_broadcast(&lvl_filtro[nivel - 1]);
    } else if (nivel < NIVELES) {
        niveles[nivel].peso_real += peso;
    }
    pthread_mutex_unlock(&mutex_lvl[nivel]);
}