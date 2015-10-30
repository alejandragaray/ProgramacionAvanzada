#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>
#include <bits/pthreadtypes.h>

#define ENANOS 7
#define SILLAS 4

pthread_mutex_t mutex_e[ENANOS];
pthread_mutex_t mutex_b;
pthread_cond_t esperando_turno;
sem_t semaf_s;

void *enanito(void *arg)
{
    int num = *(int *) arg;
    
    while (1)
    {
        printf("el enanito %d esta en la mina\n", num);
        
        usleep(rand() % 2000000);
        
        printf("el enanito %d busca donde sentarse\n", num);
        
        sem_wait(&semaf_s);
        
        printf("el enanito %d encontro lugar\n", num);
        
        pthread_mutex_unlock(&mutex_b);
        pthread_cond_wait(&esperando_turno, &mutex_e[num]);
        
        printf("el enanito %d esta comiendo\n", num);
        
        usleep(rand() % 2000000);
        
        printf("el enanito %d termino\n", num);
        
        sem_post(&semaf_s);
    }
    
    pthread_exit(NULL);
}

void *blancanieves(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex_b);
        
        printf("\nCocinando..\n");
        
        usleep(rand() % 2000000);
        
        pthread_cond_signal(&esperando_turno);
        
        printf("Platillo listo\n");
        printf("Sali a dar una vuelta\n");
    }
    
    pthread_exit(NULL);
}


int main()
{
    srand(time(NULL));
    
    sem_init(&semaf_s, 0, SILLAS);
    
    pthread_cond_init(&esperando_turno, 0);
    pthread_mutex_init(&mutex_b, NULL);
    
    int i;
    
    for (i = 0; i < ENANOS; ++i)
    {
        pthread_mutex_init(&mutex_e[i], NULL);
        
        pthread_mutex_lock(&mutex_e[i]);
    }
    
    pthread_t enanito_threads[ENANOS];
    
    for (i = 0; i < ENANOS; ++i)
    {
        pthread_create(&enanito_threads[i], NULL, enanito, &i);
    }
    
    pthread_t blancanieves_t;
    
    pthread_create(&blancanieves_t, NULL, blancanieves, NULL);
    
    for (i = 0; i < ENANOS; ++i)
    {
        pthread_join(enanito_threads[i], NULL);
    }
    
    pthread_join(blancanieves_t, NULL);
    
    pthread_cond_destroy(&esperando_turno);
    
    return 0;
}