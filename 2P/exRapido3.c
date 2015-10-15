#include <signal.h>
#include <stdio.h>


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

    for( i= 0; i < 5; ++i)
    {
        printf("\n");
        sleep(10);
        sigpending(&pendientes);
        
        if (sigismember(&pendientes, SIGINT))
            printf("He recibido un Ctrl+C y no lo procesé por estar bloqueada. \n");
       
        
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