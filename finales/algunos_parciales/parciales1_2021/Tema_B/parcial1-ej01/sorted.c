#include "sorted.h"
#include <stdio.h>

unsigned int sorted_until(int array[], unsigned int size) {
    // -- Completar --
    if (size <= 0){
      printf("The array is ordered\n");
    }
    unsigned int count =0u;
    for (unsigned int i=0u; i < size; ++i){
      count = array[i] <= array[i+1] ? count : i;
    }
    return count;
}
