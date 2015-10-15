#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <sys/stat.h>

void leer();

void gestor(int id)
{
    printf("Gestor alarma");
}

int main()
{
	sigset_t todas, pendientes;

    sigfillset(&todas);

    sigdelset(&todas, SIGALRM);

    struct sigaction senal;
    
    senal.sa_handler = gestor;
    senal.sa_flags = SA_ONESHOT;
    
    if ( sigaction(SIGALRM, &senal, 0) == -1)
    {
        printf("Error ");
        exit(1);
    }
    
    int i;
    for( i= 0; i < 5; ++i)
    {
        printf("\n");
        sleep(10);
        sigpending(&pendientes);
     	
       
        
    }

	return 0;
}

void leer()
{
    struct dirent *d;
    
    DIR *process;
    
    process = opendir (".");
    
    if (process == NULL)
    {
        printf ("Error opening \n");
        return;
    }
    
    
    while ((d = readdir(process)) != NULL)
    {
        if (atoi(d->d_name) != 0)
        {
            char *str_p = (char *)malloc(150 * sizeof(char));
            
            strcpy(str_p,"/datos/");
            
            FILE *fl;
            fl = fopen (str_p,"r");
            
            char *str_pr = (char*)malloc(150 * sizeof(char));
            fgets(str_pr,150,fl);
            
            size_t length = strlen(str_pr);

            
            free(str_pr);
            free(str_p);
            fclose(fl);
        }
    }
    
    closedir (process);
}