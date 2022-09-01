#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "sorted.h"

void pedirArreglo (int a[], int n_max){
    int i = 0; //comienzan desde la posición cero.
    int elem;

    while (i < n_max){
    printf("Ingrese el elemento en la posicion %d\n", i), scanf("%d", &elem);
    a[i] = elem;
    i = i+1;
    }
}

int main(){
  int array[5];

  pedirArreglo(array, 5);

  unsigned int count = sorted_until(array,5);

  printf("res=%d\n",count);

  return 0;

}
