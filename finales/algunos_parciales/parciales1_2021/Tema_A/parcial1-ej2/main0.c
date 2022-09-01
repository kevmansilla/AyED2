#include <stdio.h>
#include "odd.h"
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
  int N, array[1000];
  printf("\nIngrese el tamaño del arreglo: ");
  scanf("%d", &N);
  printf("\n");
  pedirArreglo(array, N);


  bool res = is_odd_sorted(array,N);

  printf("res=%d\n",res );

  return 0;

}
