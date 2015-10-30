#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define ROBOTS 10
#define NIVELES 10

pthread_mutex_t mutex_lvl[NIVELES];
pthread_cond_t lvl_filtro[NIVELES];

int peso_real[NIVELES];
int limite_peso[NIVELES];

void *robot(void *arg)
{
    int num = *(int *) arg;
    int peso = rand() % 20;
    int nivel = 0;
    
    while (1)
    {
        usleep(rand() % 100000);
        
        printf("El robot %i esta en el nivel %i\n", num, nivel);
        
        if (nivel < NIVELES)
        {
            pthread_mutex_lock(&mutex_lvl[nivel]);
            
            while (peso_real[nivel] + peso > limite_peso[nivel])
            {
                printf("robot %d pesa %d\n",num,  peso);
                
                printf("Esperando porque nivel %d tiene peso de: %d y su limite de: %d\n", nivel, peso_real[nivel], limite_peso[nivel]);
                
                pthread_cond_wait(&lvl_filtro[nivel], &mutex_lvl[nivel]);
            }
            
            if (nivel > 0)
            {
                peso_real[nivel - 1] = peso_real[nivel - 1] - peso;
                pthread_cond_broadcast(&lvl_filtro[nivel - 1]);
                
            }
            else if (nivel < NIVELES)
            {
                peso_real[nivel] = peso_real[nivel] + peso;
            }
            
            pthread_mutex_unlock(&mutex_lvl[nivel]);
            
            nivel++;
            
        }
        else
        {
            nivel = 0;
        }
       
    }
    
    pthread_exit(NULL);
}

int main()
{
    srand(time(NULL));
    
    int i;
    
    for (i = 0; i < NIVELES; ++i)
    {
        peso_real[i] = 0;
        limite_peso[i] = rand() % 25 + 20;
    }
    
    for (i = 0; i < NIVELES; ++i)
    {
        pthread_mutex_init(&mutex_lvl[i], NULL);
        
        pthread_cond_init(&lvl_filtro[i], NULL);
    }
    
    pthread_t robot_t[ROBOTS];
    
    for (i = 0; i < ROBOTS; ++i)
    {
        pthread_create(&robot_t[i], NULL, robot, &i);
    }
    for (i = 0; i < ROBOTS; ++i)
    {
        pthread_join(robot_t[i], NULL);
    }
    
    return 0;
}