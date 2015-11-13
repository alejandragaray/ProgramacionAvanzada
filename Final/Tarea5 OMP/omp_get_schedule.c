#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<sys/time.h>
#include<math.h>
#include<time.h>
#include<unistd.h>

#define MAX 10
#define MIN 2
/*omp_get_schedule sirve para obtener el método de scheduling, el primer argumento
especifica el tipo, puede ser omp_sched_static, omp_sched_dynamic, omp_sched_guided o omp_sched_auto
el segundo argumento es el modifier y especifica el tamaño del chunk*/ 

int resultado = 0;

int suma(int p)
{
    resultado += p;
    
    return resultado;
}

int main(int argc, char*argv[])
{
    int max = MAX;
    int min = MIN;
    int tam = (max-min)/2;
    int * sumas = (int*) malloc(sizeof(int)*tam);
    int i;
    double start;
    double end;
    int opcion = 0;
    int num_threads = 2;
    int modifier = 0;
    
    omp_sched_t schedule = 1;
    omp_set_num_threads(num_threads);
    omp_set_schedule(3,2); // Aqui se asigna el tipo de schedule
    
    start = omp_get_wtime();
	omp_set_dynamic(0);
#pragma omp parallel for
    for(i = 1; i < tam; i++)
    {
        sumas[i] = suma(2*i);
        printf("\nSuma acumulada = %d", sumas[i]);
    }
	
	
#pragma omp parallel for
    for(i = 1; i < tam; i++)
	if(sumas[i] == 0)
	    fprintf(stdout,"Se pasa en %d\n",2*i);
	    
    end = omp_get_wtime();
    printf("\nSuma total = %d \n", resultado);
    printf("Tiempo de ejecucion %f segundos\n", end-start);
    
    omp_get_schedule(&schedule, &modifier); //aqui se obtiene el tipo de schedule
    switch(schedule)
        {
            case 1:
                printf("\nSe selecciono schedule estatico\n");
                break;
    	    case 2:
        		printf("\nSe selecciono schedule dinamico\n");
    		break;
    	    case 3:
    		    printf("\nSe selecciono schedule Guiado\n");
    		break;
    		case 4:
    		    printf("\nSe selecciono schedule Auto\n");
    		break;
    		exit(0);
                default:
                    break;
        }
        
        printf("\nSe selecciono modifier de chunk = %d\n", modifier);

        
    return 0;
}
 
