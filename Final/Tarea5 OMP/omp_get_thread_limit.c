#include <stdio.h>
#include <omp.h>

#define N 100

/*ejecucion: OMP_THREAD_LIMIT=5 ./limit 
  Regresa el maximo numero de threads en el programa, si no se establece 
  el valor de OMP_THREAD_LIMIT se tiene un valor indefinido*/
  
int main()
{
   
    int tid;
    int i;
    int suma = 0;
      
    #pragma omp parallel private(i, tid) reduction(+:suma)  
    {
        tid = omp_get_thread_num();
    #pragma omp for schedule(guided, 1000) 
        for(i = 0; i < N; ++i)
        {
                suma += i;
        }
    }
    
    printf("Suma = %d \n", suma);
    printf("OMP_THREAD_LIMIT = %d\n", omp_get_thread_limit());

    return 0;
}


