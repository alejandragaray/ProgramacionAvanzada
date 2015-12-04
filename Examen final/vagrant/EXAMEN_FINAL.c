#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <signal.h>
#include <time.h>
#include <math.h>

#define N 18

int caminos = 0;
int *tablero;
int tamano ;

void manejador_sigusr(int signal);
void mover(int x, int y, int pasos);
void enviar_tableros(int numprocs);
int obtener_valor();

int main(int argc, char *argv[])
{
    int myid, numprocs, i, j;
    srand(time(NULL));
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    
    if (myid == 0)
    {
        signal(SIGUSR1, manejador_sigusr);
    }
    
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    
    tamano = N / sqrt(numprocs);
    
    if (myid == 0)
    {
        tablero = (int *) malloc(tamano * tamano * sizeof(int));
        for ( i = 0; i < tamano * tamano; ++i)
        {
            
            tablero[i] = obtener_valor();
        }
        
        enviar_tableros(numprocs);
        imprimir_tablero();
        
        mover(0, 0, 15);
        printf("La cantidad de caminos es: %d\n", caminos);
    }
    else
    {
        tablero = (int *) malloc(tamano * tamano * sizeof(int));
        MPI_Recv(tablero, tamano * tamano, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
    }
    
    MPI_Finalize();
    
    return 0;
    
}

int obtener_valor()
{
    int random = rand() % 10;
    
    if (random < 8)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void enviar_tableros(int numprocs)
{
    int i, j;
    for (i = 1; i < numprocs; ++i)
    {
        
        int *tablero_n = (int *) malloc(tamano * tamano * sizeof(int));
        for (j = 0; j < tamano * tamano; ++j)
        {
            tablero_n[j] = obtener_valor();
        }
        MPI_Send(tablero_n, tamano * tamano, MPI_INT, i, 0, MPI_COMM_WORLD);
        free(tablero_n);
        
    }
}

void imprimir_tablero()
{
    int i, j;
    for (i = 0; i < tamano; ++i)
    {
        for (j = 0; j < tamano; ++j)
        {
            printf("%d\t", tablero[i * tamano + j]);
        }
        
        printf("\n");
        
    }
}


void manejador_sigusr(int signal)
{
    printf("La cantidad de caminos es: %d.", caminos);
    
}

void mover(int x, int y, int pasos)
{
    if (pasos == 0)
    {
        return;
    }
    
    int pos = y*tamano+x;
    int ocupado = tablero[pos];
    
    if (x == tamano - 1)
    {
        if(y == tamano -1)
        {
            caminos += 1;
        }
    }
    
    else if (x < 0 || y < 0 || x == tamano|| y == tamano)
    {
        return;
    }
    else if (ocupado == 0)
    {
        mover(x, y + 1, pasos - 1);
        mover(x, y - 1, pasos - 1);
        mover(x + 1, y, pasos - 1);
        mover(x - 1, y, pasos - 1);
        
    }
    
}