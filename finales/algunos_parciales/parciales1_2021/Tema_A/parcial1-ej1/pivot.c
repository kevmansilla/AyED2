#include <stdbool.h>

#include "pivot.h"

/*
bool is_pivot(int array[], unsigned int length, unsigned int piv) {
  bool res = true;
  unsigned int i=0u;

  for (i = 0u; i < piv && res; ++i){
    if (array[i] <= array[i+1]){
      res = res && false;
    }
    for (i = piv +1; i < length && res;++i){
      if (array[piv] > array[i+1]){
        res = res && false;
      }
    }
  }
    return res;
}*/

#include <stdbool.h>

#include "pivot.h"

bool is_pivot(int array[], unsigned int length, unsigned int piv) {
    bool result = true;
    unsigned int i = 0;
    while (i < piv && result) {
        if(array[i] > array[piv])
            result = false;
        ++i;
    }
    unsigned int j = piv + 1;
    while (j < length && result) {
        if(array[piv] >= array[j])
            result = false;
        ++j;
    }
    return result;
}
