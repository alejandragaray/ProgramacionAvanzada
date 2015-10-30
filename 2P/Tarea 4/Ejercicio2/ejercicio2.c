#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <bits/pthreadtypes.h>

pthread_mutex_t mutex_b;
pthread_mutex_t en_espera_h;
pthread_mutex_t en_espera_m;
pthread_cond_t hombres_filtro;
pthread_cond_t mujeres_filtro;

int estado;
int fila_hombres = 0;
int fila_mujeres = 0;
int total_p = 0;

void entrar_bano(int num, pthread_mutex_t *mutex, pthread_cond_t *cond, char *tipo, int *cant)
{
    pthread_mutex_lock(mutex);
    
    *cant = *cant - 1;
    
    printf("%s En espera %d\n", tipo, *cant);
    
    pthread_mutex_unlock(mutex);
    pthread_mutex_lock(&mutex_b);
    
    total_p = total_p + 1;
    
    pthread_mutex_unlock(&mutex_b);
    
    printf("%s %d Ocupado \n", tipo, num);
    
    usleep(rand() % 200000);
    
    pthread_mutex_lock(&mutex_b);
    
    total_p = total_p -1;
    
    pthread_mutex_unlock(&mutex_b);
    
    if (total_p == 0)
    {
        printf("Desocupado\n");
        
        estado = 0;
        pthread_cond_broadcast(cond);
    }
}

void *hombre(void *arg)
{
    int num = *(int *) arg;
    
    while (1)
    {
        usleep(rand() % 1000000);
        
        pthread_mutex_lock(&en_espera_h);
        
        printf("El hombre %d ahora esta en espera\n", ++fila_hombres);
        
        pthread_mutex_unlock(&en_espera_h);
        
        if (estado == 0)
        {
            estado = 1;
            entrar_bano(num, &en_espera_h, &mujeres_filtro, "Hombre", &fila_hombres);
        }
        else if (estado == 1)
        {
            entrar_bano(num, &en_espera_h, &mujeres_filtro, "Hombre", &fila_hombres);
        }
        else
        {
            pthread_cond_wait(&hombres_filtro, &en_espera_h);
            
            entrar_bano(num, &en_espera_h, &hombres_filtro, "Hombre", &fila_hombres);
        }
    }
    
    pthread_exit(NULL);
}

void *mujer(void *arg)
{
    int num = *(int *) arg;
    
    while (1)
    {
        usleep(rand() % 1000000);
        
        pthread_mutex_lock(&en_espera_m);
        
        fila_mujeres++;
        
        printf("La mujer %d ahora esta en espera\n", fila_mujeres);
        
        pthread_mutex_unlock(&en_espera_m);
        
        if (estado == 0)
        {
            estado = 2;
            
            entrar_bano(num, &en_espera_m, &hombres_filtro, "Mujer", &fila_mujeres);
        }
        else if (estado == 1)
        {
            pthread_cond_wait(&mujeres_filtro, &en_espera_h);
            entrar_bano(num, &en_espera_h, &mujeres_filtro, "Mujer",  &fila_mujeres);
        }
        else
        {
            entrar_bano(num, &en_espera_m, &hombres_filtro, "Mujer", &fila_mujeres);
        }
    }
    
    pthread_exit(NULL);
}


int main()
{
    pthread_cond_init(&hombres_filtro, NULL);
    pthread_cond_init(&mujeres_filtro, NULL);
    pthread_mutex_init(&mutex_b, NULL);
    
    srand(time(NULL));
    
    pthread_t hombres_t[10];
    
    pthread_t mujeres_t[10];
    
    int i;
    
    for (i = 0; i < 10; ++i)
    {
        pthread_create(&hombres_t[i], NULL, hombre, &i);
        
        pthread_create(&mujeres_t[i], NULL, mujer, &i);
    }
    
    for (i = 0; i < 10; ++i)
    {
        pthread_join(hombres_t[i], NULL);
        
        pthread_join(mujeres_t[i], NULL);
    }
    
    return 0;
}