#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "stack.h"

struct _s_stack {
    unsigned int size;
    stack_elem elem;
    struct _s_stack *next;
};


stack stack_empty () {
  return NULL;
}

stack stack_push (stack s, stack_elem e){
  stack new_nodo =  NULL;
  new_nodo = malloc(sizeof(struct _s_stack));
  new_nodo->elem = e;
  new_nodo->next = s;
  new_nodo->size = s == NULL ? 1 : s->size + 1;

  return (new_nodo);
}

stack stack_pop (stack s){
  assert(s != NULL);
  stack aux_stack;
  aux_stack = s->next;
  free(s);
  s = NULL;

  return aux_stack;
}

unsigned int stack_size (stack s){
  return s == NULL ? 0 : s->size;
}

stack_elem stack_top (stack s){
  assert(s != NULL);
  return (s->elem);
}

bool stack_is_empty (stack s){
  return s == NULL;
}

stack_elem *stack_to_array (stack s){
  unsigned int n = stack_size(s);
  stack_elem *array = NULL;
  stack aux_stack = s;
  unsigned int i = n - 1;

  if (s == NULL){
    array = NULL;
  } else {
    array = calloc(n,sizeof(stack_elem));

    while (aux_stack != NULL) {
      array[i] = aux_stack->elem;
      aux_stack = aux_stack->next;

      --i;
    }
    free(aux_stack);
    aux_stack = NULL;
  }

  return array;
}

stack stack_destroy (stack s){
  stack aux_stack = s;
  while (s != NULL){
    s = s->next;
    free(aux_stack);
    aux_stack = NULL;
  }

  return (s);
}
