#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>


pthread_mutex_t mutex_1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_3 = PTHREAD_MUTEX_INITIALIZER;

int elementos[3] = {1,2,3};

//1 = papel, 2 = tabaco, 3 = fosforo

int elemento = 0;

void* fumador1(void* arg)
{
    pthread_mutex_lock(&mutex_1);
    sleep(5);
    
    elemento = 1;
    pthread_mutex_unlock(&mutex_1);
    
    pthread_exit(0);
}

void* fumador2(void* arg)
{
    pthread_mutex_lock(&mutex_2);
    sleep(5);
    elemento = 2;
	   
    pthread_mutex_unlock(&mutex_2);
    
    pthread_exit(0);
}

void* fumador1(void* arg)
{
    pthread_mutex_lock(&mutex_3);
    sleep(5);
    elemento = 3;
	   
    pthread_mutex_unlock(&mutex_3);
    
    pthread_exit(0);
}

void* agente(void* arg)
{
    
    while (pthread_mutex_trylock(&mutex_1))
    {
        pthread_mutex_unlock(&mutex_1);
        
        pthread_mutex_lock(&mutex_1);
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