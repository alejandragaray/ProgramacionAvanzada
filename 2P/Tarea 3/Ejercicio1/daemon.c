#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


void leer();

int main(int argc, char **argv)
{
    pid_t child, sid;
    char *arg_values = NULL;
    int c = 0;
   
    
    while ((c = getopt(argc, argv, "m:")) != -1)
    {
        switch (c)
        {
            case 'm':
                arg_values = optarg;
                break;
                
            case '?':
                return 1;
            default:
                abort();
        }
    }
    
    int minutes = atoi(arg_values);
    
    if (fork() < 0)
        exit(EXIT_FAILURE);
    else
        exit(EXIT_SUCCESS);
    
    umask(0);
    
    sid = setsid();
    
    if (sid < 0)
        exit(EXIT_FAILURE);
    
    if ((chdir("/")) < 0)
       	exit(EXIT_FAILURE);
    
    
    while (1)
    {
        printf("\n");
        leer();
        printf("\n");
        
        int time = 60 * minutes;
        
        sleep(time);
    }
    
    return 0;
}

void leer()
{
    struct dirent *d;
    
    DIR *process;
    
    process = opendir ("/proc");
    
    if (process == NULL)
    {
        printf ("Error opening \n");
        return;
    }
    
    printf ("\npid    process      status\n");
    
    while ((d = readdir(process)) != NULL)
    {
        if (atoi(d->d_name) != 0)
        {
            char *str_p = (char *)malloc(150 * sizeof(char));
            
            strcpy(str_p,"/proc/");
            strcat(str_p,d->d_name);
            strcat(str_p,"/status");
            
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








