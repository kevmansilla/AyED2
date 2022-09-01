#include <stdbool.h>
#include "even.h"


bool is_even_sorted(int array[], unsigned int length){
      if (length <= 2){
          return true;
      }
      else{
          bool res = true;
          for (unsigned int i = 0u; i < length-2; i= i+2){
              if (array[i]<array[i+2]){
                  res = res && true;
              }
              else{
                  res = res && false;
              }
          }
          return res;
      }
  }
