#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define SHMSZ     32
long long factorial(int n);

main()
{
    int shmid;
    key_t key;
    int num;
    int *numeros;
    int resultado = 0;
    
    key = 8349;
    
    if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    if ((numeros = shmat(shmid, NULL, 0)) == (int *) -1) {
        perror("shmat");
        exit(1);
    }
    
    
    resultado = factorial(*numeros);
    
    printf("resultado\t%d", resultado);
    printf("\n");
    
    
    exit(0);
}

long long factorial(int n) {
    long long res = 1;
    int i;
    for (i = 2; i <= n; ++i) {
        res *= i;
    }
    return res;
}