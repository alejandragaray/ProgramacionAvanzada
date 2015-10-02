#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#define FILEPATH "map.txt"
#define FILESIZE sizeof(int)

int main()
{
    int i;
    int fd;
    int *map;

    fd = open(FILEPATH, O_RDONLY);
    
    if (fd == -1) 
    {
     perror("Error opening file for reading");
     exit(-1);
    }

    map = (int *)mmap(0, FILESIZE, PROT_READ, MAP_SHARED, fd, 0);
    
    if (map == MAP_FAILED) 
    {
     close(fd);
     perror("Error mmapping the file");
     exit(EXIT_FAILURE);
    }
    
    int c;
    long result = 1;
 
      for (c = 1; c <= *map; c++)
          result *= c;
    
    printf("El factorial es %ld\n",result);

    
    if (munmap(map, FILESIZE) == -1) 
    {
     perror("Error un-mmapping the file");
    }
    close(fd);
    
    return 0;
}

