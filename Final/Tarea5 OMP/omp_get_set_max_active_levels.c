#include <stdio.h>
#include <omp.h>

/*Ejemplo que involucra:
        omp_set_max_active_levels
        omp_get_max_active_levels
        omp_get_level
*/
/*cuando no se establece un maximo de niveles activos, el default es indefinido por
lo que si se obtiene, dara un numero muy grande, omp_get_level indica el nivel en el 
que se encuentra en el programa*/
int main (void)
{
    
     omp_set_nested(1);
     omp_set_max_active_levels(8); //Aqui se asigna el maximo de niveles deseados
     omp_set_dynamic(0);
     omp_set_num_threads(2); //Se establecen 2 threads
     #pragma omp parallel
       {
         omp_set_num_threads(1);
  
           #pragma omp parallel
             {
                printf ("Anidado: max_act_lev=%d, num_thds establecidos=%d, level = %d\n",
                       omp_get_max_active_levels(), omp_get_num_threads(), omp_get_level());/* aqui se obtiene el maximo de niveles 
                                                                                               activos y el nivel actual en el que 
                                                                                               se encuentra*/
                 
             }

           #pragma omp barrier
           #pragma omp single
             {
               printf ("Fuera: max_act_lev=%d, num_thds establecidos=%d, level = %d\n",
                       omp_get_max_active_levels(), omp_get_num_threads(), omp_get_level());
             }
       }
       
   }