#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define HOMBRES 10
#define MUJERES 10

typedef enum
{
    libre,
    ocupado_h,
    ocupado_m
} status;

pthread_mutex_t mutex_b;

pthread_mutex_t en_espera_h;

pthread_mutex_t en_espera_m;

pthread_cond_t hombres_filtro;

pthread_cond_t mujeres_filtro;

state_e status;

int fila_hombres = 0;

int fila_mujeres = 0;

int total_p = 0;

int ciclo = 1;

void *hombre(void *arg);

void *mujer(void *arg);

void crear_threads(int tamano, pthread_t *threads, void *(*func)(void *));

void func_hombre(int id);

void baño_en_espera(int id, pthread_mutex_t *mutex, pthread_cond_t *cond, char *tipo, int *cant);

void entrar_baño(int id, pthread_mutex_t *mutex, pthread_cond_t *cond, char *tipo, int *cant);

void verificar_baño(int cant, pthread_cond_t *cond);

int main() {
    srand(time(NULL));
    
    pthread_mutex_init(&mutex_b, NULL);
    
    pthread_cond_init(&hombres_filtro, NULL);
    pthread_cond_init(&mujeres_filtro, NULL);
    
    pthread_t hombres_t[HOMBRES];
    crear_threads(HOMBRES, hombres_t, hombre);
    
    pthread_t mujeres_t[MUJERES];
    crear_threads(MUJERES, mujeres_t, mujer);
    
    int i;
    for (i = 0; i < HOMBRES; ++i) {
        pthread_join(hombres_t[i], NULL);
    }
    
    for (i = 0; i < MUJERES; ++i) {
        pthread_join(mujeres_t[i], NULL);
    }
    
    pthread_exit(NULL);
}


void crear_threads(int tamano, pthread_t *threads, void *(*func)(void *)) {
    int i;
    int ids[tamano];
    for (i = 0; i < tamano; ++i) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, func, &ids[i]);
    }
}

void *hombre(void *arg) {
    int id = *(int *) arg;
    while (ciclo) {
        usleep(rand() % 500000);
        pthread_mutex_lock(&en_espera_h);
        printf("El hombre %d ahora esta en espera\n", ++fila_hombres);
        pthread_mutex_unlock(&en_espera_h);
        func_hombre(id);
    }
}

void func_hombre(int id) {
    switch (status) {
        case libre:
            status = ocupado_h;
        case ocupado_h:
            entrar_baño(id, &en_espera_h, &mujeres_filtro, "Hombre", &fila_hombres);
            break;
        case ocupado_m:
            baño_en_espera(id, &en_espera_h, &hombres_filtro, "Hombre", &fila_hombres);
            break;
    }
}

void func_mujer(int id) {
    switch (status) {
        case libre:
            status = ocupado_m;
        case ocupado_m:
            entrar_baño(id, &en_espera_m, &hombres_filtro, "Mujer", &fila_mujeres);
            break;
        case ocupado_h:
            baño_en_espera(id, &en_espera_h, &mujeres_filtro, "Mujer", &fila_mujeres);
            break;
    }
}

void entrar_baño(int id, pthread_mutex_t *mutex, pthread_cond_t *cond, char *tipo, int *cant) {
    pthread_mutex_lock(mutex);
    printf("%s En espera %d\n", tipo, --(*cant));
    pthread_mutex_unlock(mutex);
    
    pthread_mutex_lock(&mutex_b);
    ++total_p;
    pthread_mutex_unlock(&mutex_b);
    
    printf("%s %d Ocupado \n", tipo, id);
    usleep(rand() % 200000);
    
    pthread_mutex_lock(&mutex_b);
    --total_p;
    pthread_mutex_unlock(&mutex_b);
    
    verificar_baño(total_p, cond);
}

void verificar_baño(int cant, pthread_cond_t *cond) {
    if (cant == 0) {
        status = libre;
        printf("Desocupado\n");
        pthread_cond_broadcast(cond);
    }
}

void baño_en_espera(int id, pthread_mutex_t *mutex, pthread_cond_t *cond, char *tipo, int *cant) {
    pthread_cond_wait(cond, &mutex_b);
    entrar_baño(id, mutex, cond, tipo, cant);
}

void *mujer(void *arg) {
    int id = *(int *) arg;
    while (ciclo) {
        usleep(rand() % 500000);
        pthread_mutex_lock(&en_espera_m);
        printf("La mujer %d ahora esta en espera\n", ++fila_mujeres);
        pthread_mutex_unlock(&en_espera_m);
        func_mujer(id);
    }
}