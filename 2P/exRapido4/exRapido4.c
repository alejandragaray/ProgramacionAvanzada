#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>


pthread_mutex_t mutex_1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_3 = PTHREAD_MUTEX_INITIALIZER;

int elementos[3] = {1,2,3};

//1 = papel, 2 = tabaco, 3 = fosforo
int fumado;
int elemento = 0;
int elemento1;
int elemento2;
int elemento3;

void* fumador1(void* arg)
{
    elemento = 1;
    
    if(elemento < elemento2 && elemento < elemento3)
    {
        pthread_mutex_lock(&mutex_1);
        sleep(5);
        fumado = 1;
        pthread_mutex_unlock(&mutex_1);
    }
    else
    {
        fumado = 0;
    }
    
    
    pthread_exit(0);
}

void* fumador2(void* arg)
{
    elemento = 2;
    
    if(elemento < elemento3 && elemento < elemento1)
    {
        pthread_mutex_lock(&mutex_2);
        sleep(5);
        fumado = 1;
        pthread_mutex_unlock(&mutex_2);
    }
    else
    {
        fumado = 0;
    }
    
    pthread_exit(0);
}

void* fumador3(void* arg)
{
    elemento = 3;
    
    if(elemento > elemento2 && elemento > elemento1)
    {
        pthread_mutex_lock(&mutex_1);
        sleep(5);
        fumado = 1;
        pthread_mutex_unlock(&mutex_1);
    }
    else
    {
        fumado = 0;
    }
    
    pthread_exit(0);
}

void* agente(void* arg)
{
    int i;
    for(i = 0; i < 100; ++i)
    {
        elemento1 = rand()%3;
        elemento2 = rand()%3;
        
        while (pthread_mutex_trylock(&mutex_1))
        {
            pthread_mutex_unlock(&mutex_1);
            
            pthread_mutex_lock(&mutex_1);
        }
        
        while (pthread_mutex_trylock(&mutex_2))
        {
            pthread_mutex_unlock(&mutex_2);
            
            pthread_mutex_lock(&mutex_2);
        }
        
        while (pthread_mutex_trylock(&mutex_3))
        {
            pthread_mutex_unlock(&mutex_3);
            
            pthread_mutex_lock(&mutex_3);
        }
    }
    
    pthread_exit(0);
}


int main(int argc, char* arvg[])
{
    srand(time(NULL));
    pthread_t * tid;
    int nhilos;
    int i;
    
    nhilos = 4;
    
    tid = malloc(nhilos * sizeof(pthread_t));
    
    printf("Creando hilos ...\n");
    
    pthread_create(tid, NULL, agente, (void *)0);
    pthread_create(tid+1, NULL, fumador1, (void *)1);
    pthread_create(tid+2, NULL, fumador2, (void *)2);
    pthread_create(tid+3, NULL, fumador3, (void *)3);
    
    for (i = 0; i < nhilos; ++i) {
        pthread_join(*(tid+i), NULL);
        printf("TID = %d...\n", *(tid+i));
    }
    
    free(tid);
    return 0;
}