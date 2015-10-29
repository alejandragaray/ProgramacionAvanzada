#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <bits/pthreadtypes.h>

#define COMPLEJO 5
#define SALAS_COMPLEJO 2
#define CLIENTES 5
#define ASIENTOS_SALA 2

pthread_mutex_t asientos_mutex[COMPLEJO * SALAS_COMPLEJO];

int asientos[COMPLEJO * SALAS_COMPLEJO * ASIENTOS_SALA];

void *cliente(void *arg)
{
    int id = *(int *) arg;
    
    while (1)
    {
        
        int complejo;
        int sala;
        int asiento;
        int pos;
        
        printf("%d - .........\n", id);
        
        usleep(rand() % 500000);
        
        complejo = rand() % COMPLEJO;
        printf("%d Selecciono el complejo %d\n", id, complejo);
        
        usleep(rand() % 500000);
        
        sala = rand() % SALAS_COMPLEJO;
        printf("%d Selecciono la sala %d\n", id, sala);
        
        usleep(rand() % 500000);
        
        asiento = rand() % ASIENTOS_SALA;
        printf("%d Selecciono el asiento %d\n", id, asiento);
        
        pos = (complejo * SALAS_COMPLEJO + sala) * ASIENTOS_SALA + asiento;
        
        pthread_mutex_lock(&asientos_mutex[pos]);
        
        int temp = asientos[pos];
        if (!temp)
        {
            asientos[pos] = 1;
            
            printf("%d: Asiento %d lo ocupe\n", id, asiento);
            
            pthread_mutex_unlock(&asientos_mutex[pos]);
            
            break;
        }
        else
        {
            printf("%d Asiento %d ocupado\n", id, asiento);
            
            pthread_mutex_unlock(&asientos_mutex[pos]);
        }
    }
}

int main()
{
    srand(time(NULL));
    
    int i;
    
    for (i = 0; i < COMPLEJO * SALAS_COMPLEJO * ASIENTOS_SALA; ++i)
    {
        pthread_mutex_init(&asientos_mutex[i], NULL);
        asientos[i] = 0;
    }
    
    pthread_t clientes_t[CLIENTES];
    int ids[CLIENTES];
    
    for (i = 0; i < CLIENTES; ++i)
    {
        ids[i] = i;
        pthread_create(&clientes_t[i], NULL, cliente, &ids[i]);
    }
    
    for (i = 0; i < CLIENTES; ++i)
    {
        pthread_join(clientes_t[i], NULL);
    }
    
    pthread_exit(NULL);
    
}

