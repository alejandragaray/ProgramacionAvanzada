#include <omp.h>
#include <stdio.h>
/*omp_get_wtime obtiene el tiempo en segundos por thread
  omp_get_wtick obtiene la precision del reloj, el numero de 
  segundos entre 2 tiks de reloj*/
int main()
{
  int i,n=5;
  int fac=1;
  double start_time = omp_get_wtime();
  
#pragma omp parallel for shared(n) private(i) reduction(*:fac)

  for(i=1;i<=n;i++)
    fac*=i;
    
  double end_time = omp_get_wtime();
  double wtick = omp_get_wtick();
  
  printf("Factorial de %d = %d en %g segundos \n",n,fac, end_time-start_time);
  printf("Precision del reloj: %g\n", wtick);

return 0;
	
}