//
//  main.c
//  ejemploSIGINT
//
//  Created by Alejandra Garay on 01/10/15.
//  Copyright (c) 2015 Alejandra Garay. All rights reserved.
//


#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>

int *ctrls;
int ctrl_c;
int ctrl_z;
int x = 3;

void manejador_al(int id)
{
    printf("Aparezco cada %d segundos", x);
}
void manejador_ctrl_c(int id)
{
    ctrls[0] = ctrl_c++;
}

void manejador_ctrl_z(int id)
{
    ctrls[1] = ctrl_z++;
}

void manejador_ctrl(int id){
    sleep(1);

    printf("Se ha pulsado %d veces CTRL+C y se ha pulsado %d veces CTRL+Z. Acabando… \n", ctrls[0], ctrls[1]);


}

int main(int argc, const char * argv[])
{
    int shmid;
    key_t key = 3425;


    pid_t pid;
    int i;

    if ((shmid = shmget(key, (sizeof(int)*2), IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }
    if ((ctrls = (int *) shmat(shmid, NULL, 0)) == (int *) -1) {
        perror("shmat");
        exit(1);
    }

        pid = fork();

        if(pid == 0)
        {
            if ((ctrls = (int *) shmat(shmid, NULL, 0)) == (int *) -1)
            {
                perror("shmat");
                exit(1);
            }

            sleep(10);

            alarm(x);

            kill(getppid(), SIGUSR1);


            alarm(0);

            exit(0);

        }
        else
        {
            if (signal(SIGALRM,manejador_al) == SIG_ERR) {
                printf("No se pudo establecer el manejador de la senal.....FAIL\n");
            }
            if (signal(SIGUSR1,manejador_ctrl_c) == SIG_ERR){
                printf("No se pudo establecer el manejador de la senal.....FAIL\n");
            }

            if (signal(SIGTSTP,manejador_ctrl_z) == SIG_ERR){
                printf("No se pudo establecer el manejador de la senal.....FAIL\n");
            }




        }


    return 0;
}
