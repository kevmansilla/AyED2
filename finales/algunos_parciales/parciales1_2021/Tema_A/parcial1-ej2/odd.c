#include <stdbool.h>

#include "odd.h"
/*
bool is_odd_sorted(int array[], unsigned int length) {
    // -- Completar --
    if (length <= 3){
      return true;
    } else{
      bool res = true;
      for (unsigned int i=1u; i < length; i=i+2){
        res = res && (array[i] < array[i+2]);
      }
      return res;
    }
  }*/
  bool is_odd_sorted(int array[], unsigned int length){
      if (length <= 3){
          return true;
      }
      else{
          bool res = true;
          for (unsigned int i = 1u; i < length-1; ++i){
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
