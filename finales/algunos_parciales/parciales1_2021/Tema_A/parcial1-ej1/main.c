#include <stdio.h>
#include "pivot.h"
#include <assert.h>
#include <stdlib.h>

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
  int array[4];

  pedirArreglo(array, 4);

  bool res = is_pivot(array,4,1);

  printf("res=%d\n",res );

  return 0;

}
