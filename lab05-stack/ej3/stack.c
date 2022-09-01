#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "stack.h"

struct _s_stack {
    stack_elem *elems;      // Arreglo de elementos
    unsigned int size;      // Cantidad de elementos en la pila
    unsigned int capacity;  // Capacidad actual del arreglo elems
};

/**************************************/
/******** Funciones Auxiliares ********/
/**************************************/

/**
* @brief Representation invariant
* @param s A stack
*/
static bool inv_repre (stack s){
  return (s != NULL ? ((s->size <= s->capacity) && (s->elems != NULL) && (s->size>0)) : true);
}

/**
* @brief Ask for double the memory for the stack
* @param s A stack
* @return The new stack with with double memory
*/
static void double_stack (stack s){
  s->capacity = s->capacity * 2;
  s->elems =  realloc(s->elems,(s->capacity)*sizeof(stack_elem));
  printf("Array dobling happende successfully!\n"); //me dice las cuantas veces pedi memoria
}

/**************************************/

static stack_elem is_full (stack s){
  return (s->size == s->capacity);
}

stack stack_empty (){
  stack s = NULL;
  assert(inv_repre(s));

  return (s);
}

stack stack_push (stack s, stack_elem e){
  assert(inv_repre(s));
  if (s == NULL){
    s = malloc(sizeof(struct _s_stack));
    s->capacity = 1u;
    s->size = 0u;
    s->elems = (stack_elem*)calloc(s->capacity, sizeof(stack_elem));
  } else if (is_full(s)){
    double_stack(s);
  }
  s->elems[s->size] = e;
  ++s->size;

  return (s);
}

stack stack_pop (stack s){
  assert(inv_repre(s) && (s != NULL));
  --s ->size;

  assert(inv_repre(s) && (s != NULL));
  return (s);
}

unsigned int stack_size (stack s){

  assert(inv_repre(s));
  return (s == NULL ? 0u : s->size);
}

stack_elem stack_top (stack s){

  assert(inv_repre(s) && (s != NULL));
  return (s->elems[s->size-1u]);
}

bool stack_is_empty (stack s){

  return (s == NULL);
}

stack_elem *stack_to_array (stack s){
  assert(inv_repre(s));
  stack_elem *array = NULL;
  unsigned int length = stack_size(s);
  stack aux_stack = s;

  if (s == NULL){
    array = NULL;
  } else {
    array = calloc(length, sizeof(stack_elem));
    for (unsigned int i = 0u; i < aux_stack->size; ++i){
      array[i] = aux_stack->elems[aux_stack->size - 1];
    }
  }
  free(array);
  array = NULL;

  assert(inv_repre(s));
  return (array);
}

stack stack_destroy (stack s){
  assert(inv_repre(s));
  if (s == NULL){
    fprintf(stderr, "Cannot destroy stack\n");
    exit(EXIT_FAILURE);
  }

  free(s->elems);
  s->elems = NULL;
  free(s);
  s = NULL;

  assert(inv_repre(s));
  return (s);
}
