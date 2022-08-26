#include <stdio.h>
#include "omp.h"

int fib(int n) {
  int i, j;

  if (n < 2) {
    return n;
  }
  else {
    #pragma omp task shared(i)
    i=fib(n-1);

    #pragma omp task shared(j)
    j=fib(n-2);

    #pragma omp taskwait
    return i+j;
   }
}

int main () {
  int begin = omp_get_wtime();
  int result;

  #pragma omp parallel 
  {
    #pragma omp single
    result = fib(40);
  } 

  int end = omp_get_wtime();
  
  printf("Result: %d\n", result);
  printf("Time: %d\n", end - begin);

  return 0;
}
