#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NHILOS 1

pthread_mutex_t mutex_s = PTHREAD_MUTEX_INITIALIZER;

int suma[10000000];
int sumas = 0;
FILE *fp;


void * sumar(void * arg)
{

    int tid = (int) arg;
    int i = 0;
    
    while (feof(fp) == 0)
    {
        
        pthread_mutex_lock(&mutex_s);
        
        fscanf(fp, "%d", &suma[i]);
        sumas += suma[i];
        ++i;
        pthread_mutex_unlock(&mutex_s);
        
    }
    
    pthread_exit(0);
}


int main(int argc, const char * argv[])
{
    
    time_t start,end;
    double dif;
    
    fp = fopen ( "fichero1.txt", "r" );
    pthread_t * tid;
    int nhilos;
    int i;
    
    nhilos = NHILOS;
    
    tid = malloc(nhilos * sizeof(pthread_t));
    time (&start);
    
    
    for (i = 0; i < nhilos; ++i)
    {
        pthread_create(tid + i, NULL, sumar, (void *)0);
        
    }
    
    for (i = 0; i < nhilos; ++i)
    {
        pthread_join(*(tid+i), NULL);
    }
    
    time (&end);
    dif = difftime (end,start);
     printf("Suma = %d\n", sumas);
    printf ("Your calculations took %.2lf seconds to run.\n", dif );
    
   
    
    free(tid);
    
    return 0;
}