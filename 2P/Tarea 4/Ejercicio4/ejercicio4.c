#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

int valores_regulares[15];
int valores_alarm[15];

pthread_mutex_t mutex_s[15];
pthread_mutex_t mutex_al[15];
pthread_t reporte_t;

FILE *f;

void manejador_alarma(int signal)
{
    int i;
    
    for (i = 0; i < 15; ++i)
    {
        if (valores_alarm[i] != 0 )
        {
            pthread_mutex_lock(&mutex_al[i]);
            
            fprintf(f,"El sensor %d indica el valor critico %d \n", i,valores_alarm[i]);
            
            valores_alarm[i] = 0;
            
            pthread_mutex_unlock(&mutex_al[i]);
        }
    }
}


void *sensor(void *arg)
{
    int num = *(int*) arg;
    
    while (1)
    {
        usleep(rand() % 150000);
        
        int valor = rand() % 20;
        
        if (valor >= 12)
        {
            pthread_mutex_lock(&mutex_al[num]);
           
            valores_alarm[num] = valor;
           
            pthread_mutex_unlock(&mutex_al[num]);
            
            if (reporte_t)
                pthread_kill(reporte_t, SIGUSR1);
        }
        else
        {
            pthread_mutex_lock(&mutex_s[num]);
            
            valores_regulares[num] = valor;
            
            pthread_mutex_unlock(&mutex_s[num]);
        }
    }
    
    pthread_exit(NULL);
}

void *reporte(void *arg)
{
    signal(SIGUSR1, manejador_alarma);
    
    while (1)
    {
        usleep(rand() % 150000);
    
        int i;
        
        for (i = 0; i < 15; i++)
        {
            if (valores_alarm[i] != 0)
            {
                pthread_mutex_lock(&mutex_s[i]);
        
                printf("El sensor %d da el valor %d\n", i, valores_regulares[i]);
                
                fprintf(f, "El sensor %d da el valor %d\n", i, valores_regulares[i]);
                
                valores_regulares[i] = 0;
                pthread_mutex_unlock(&mutex_s[i]);
            }
        }
    }
    
    pthread_exit(NULL);
}


int main()
{
    srand(time(NULL));
    
    f = fopen("info.txt", "w+");
    
    if (f == NULL)
    {
        printf("Error abriedo f!\n");
        exit(1);
    }
    
    int i;
    
    for (i = 0; i < 15; ++i)
    {
        pthread_mutex_init(&mutex_s[i], NULL);
       
        pthread_mutex_init(&mutex_al[i], NULL);
    }
    
    pthread_create(&reporte_t, NULL, reporte, NULL);
    pthread_t sensor_threads[15];
    
    for (i = 0; i < 15; ++i)
    {
        pthread_create(&sensor_threads[i], NULL, sensor, &i);
    }
    
    for (i = 0; i < 15; ++i)
    {
        pthread_join(sensor_threads[i], NULL);
    }
    
    pthread_join(reporte_t, NULL);
    
    fclose(f);
    return 0;
}