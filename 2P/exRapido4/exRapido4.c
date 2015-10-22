#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


pthread_mutex_t mutex_1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_3 = PTHREAD_MUTEX_INITIALIZER;

int * elementos = malloc(3 * sizeof(int));

int fumado;

void* fumador1(void* arg)
{
    
}

void* fumador2(void* arg)
{
    pthread_mutex_lock(&mutex_s);
    sleep(5);
    fumado = 0;
	   
    pthread_mutex_unlock(&mutex_s);
    
    pthread_exit(0);
}

void* fumador3(void* arg)
{
    pthread_mutex_lock(&mutex_s);
    sleep(5);
    fumado = 0;
	   
    pthread_mutex_unlock(&mutex_s);
    
    pthread_exit(0);
}

void* agente(void* arg)
{
    
    pthread_mutex_lock(&mutex_s);
    sleep(5);
    
    fumado = 0;
    
    pthread_mutex_unlock(&mutex_s);
    
    pthread_exit(0);
}


int main(int argc, char* arvg[])
{
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
    
    
    return 0;
}