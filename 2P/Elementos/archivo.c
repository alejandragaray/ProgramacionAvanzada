#include <stdio.h>

int main ( int argc, char **argv )
{
    FILE *fp;
    
    int num;
    int n = 10000000;
    char caracter;
    
    fp = fopen ( "fichero.txt", "w" ); 
    
    while(n > 0)
    {
        num = rand()%100;
        fprintf(fp, " %d ", num);
        if(n%1000 == 0 && n != 10000000)
            fprintf(fp, "\n");
        n--;
    }
    
    fclose ( fp );
    
    return 0;
}