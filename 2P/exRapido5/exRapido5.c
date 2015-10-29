#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define COMPLEJOS 2
#define SALAS 3
#define TAQUILLAS 2

pthread_mutex_t mutex_s = PTHREAD_MUTEX_INITIALIZER;

void *web(void *arg)
{
    int id = (int)arg;
    
    
    pthread_exit(NULL);
}

void *movil(void *arg)
{
    int id = (int)arg;
    
    
    pthread_exit(NULL);
}

void *presencial(void *arg)
{
    int id = (int)arg;
    
    
    pthread_exit(NULL);
}

int main()
{
    srand(time(NULL));
    int i;
    
    pthread_t web_h;
    pthread_create(&web_h,NULL,web,NULL);
    
    pthread_t movil_h;
    pthread_create(&movil_h,NULL,movil,NULL);
    
    pthread_t presencial_h;
    pthread_create(&presencial_h,NULL,presencial,NULL);
    
    pthread_join(web_h,NULL);
    free();
    return 0;
}



