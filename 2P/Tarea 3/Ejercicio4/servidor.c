#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#define FILESIZE sizeof(int)
#define FILEPATH "map.txt"

int main()
{
    int i;
    int fd;
    int result;
    int * map;  


    fd = open(FILEPATH, O_RDWR | O_CREAT | O_TRUNC, (mode_t)0600);
    
    if (fd == -1) 
    {
       perror("Error opening file for writing");
       exit(-1);
    }

    result = lseek(fd, FILESIZE+1, SEEK_SET);
    
    if (result == -1) 
    {
       close(fd);
       perror("Error calling lseek() to 'stretch' the file");
       exit(-1);
    }
 
    result = write(fd, "", 1);
    
    if (result != 1) 
    {
       close(fd);
       perror("Error writing last byte of the file");
       exit(-1);
    }

    lseek(fd, 0, SEEK_SET);

    map = (int *)mmap(0, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    
    if (map == MAP_FAILED) 
    {
       close(fd);
       perror("Error mmapping the file");
       exit(EXIT_FAILURE);
    }
    
    char * leido;

    printf("Numero \n");
    scanf("%ms",&leido);

    *map = atoi(leido);
    
    if (munmap(map, FILESIZE) == -1) 
    {
    perror("Error un-mmapping the file");
    }

    close(fd);
    free(leido);
    return 0;
}