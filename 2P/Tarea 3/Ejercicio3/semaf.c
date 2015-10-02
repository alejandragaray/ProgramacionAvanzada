#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/sem.h>


int main()
{
    long f;
    int id;
    int ipc = IPC_PRIVATE;
	id = semget(ipc, 1, SHM_R | SHM_W);


  int value;                       
	
	printf("Entra el numero: \n");
      	scanf("%d", &value);

      	union semun arg;
	
	arg.val = value;
	semctl(id, 0, SETVAL, arg);  

	value = semctl(id, 0, GETVAL);
	f = 1;
    int i;
    for (i = 2; i <= value; ++i) 
        f *= i;
    
        printf("El factorial es: %ld\n", f);

        if (semctl(id, 0, IPC_RMID, NULL) == -1){
		perror("Error al eliminar semaforo");
		exit(-1);
	}

    
}