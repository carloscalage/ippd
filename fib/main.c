#include <stdio.h>
#include "omp.h"

int fib(int n, int type) {
  int i, j;

  if (n < 2) {
    return n;
  }
  else {

    if (type == 0) {
      i = fib(n - 1, 0);
      j = fib(n - 2, 0);
    }
    else {
      #pragma omp task shared(i)
      i = fib(n - 1, 1);

      #pragma omp task shared(j)
      j = fib(n - 2, 1);

      #pragma omp taskwait
    }

    return i+j;
   }
}

int main (int argc, char *argv[]) {
  int begin = omp_get_wtime();
  int result;
  int n = atoi(argv[1]);

  /* Parallel */

  #pragma omp parallel 
  {
    #pragma omp single
    result = fib(n, 1);
  } 

  int end = omp_get_wtime();
  
  printf("Result: %d\n", result);
  printf("Time: %ds\n", end - begin);

  /* Sequential */

  begin = omp_get_wtime();

  result = fib(n, 0);

  end = omp_get_wtime();

  printf("Result: %d\n", result);
  printf("Time: %ds\n", end - begin);

  return 0;
}
