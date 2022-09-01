/*
  @file sort.c
  @brief sort functions implementation
*/
#include <stdbool.h>
#include <assert.h>
#include "helpers.h"
#include "sort.h"
#include "movie.h"


bool goes_before(movie_t s1, movie_t s2) {
    // -- Completar --
    return s1.runtime <= s2.runtime;
}

unsigned int array_sorted_until(movie_t movielist[], unsigned int size) {
    // -- Completar --
    unsigned int count =0u;
    for (unsigned int i=0u; i < size-1; ++i){
      count = goes_before(movielist[i],movielist[i+1]) ? count :i;
    }

    return count;
}
