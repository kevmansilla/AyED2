#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "stack.h"

struct _s_stack {
   stack_elem elem;
   struct _s_stack *next;
};

/*tope en primer elemento para no recorrer, podria poner como invariante de representacion TRUE*/

stack stack_empty (){
  stack s = NULL;
  return (s);
}

stack stack_push (stack s, stack_elem e){
  stack new_nodo = NULL;
  new_nodo = malloc(sizeof(struct _s_stack));
  new_nodo->elem = e;
  new_nodo->next = s;
  s = new_nodo;

  return (s);
}

stack stack_pop (stack s){
  assert(s != NULL);
  stack aux_stack = s;
  s = s->next;
  free(aux_stack);
  aux_stack = NULL;

  return (s);
}

unsigned int stack_size (stack s){
  stack new_nodo = s;
  unsigned int n = 0u;
  while (new_nodo != NULL) {
    n = n + 1;
    new_nodo = new_nodo->next;
  }

  return (n);
}

stack_elem stack_top (stack s){
  assert(s != NULL);
  return (s->elem);
}

bool stack_is_empty (stack s){

  return (s == NULL);
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

/* visualización de la pila
void muestra (Pila * tas){
  Elemento *actual;
  int i;
  actual = tas->inicio;

  for(i=0;i<tas->tamaño;++i){
    printf("\t\t%s\n", actual->dato);
    actual = actual->siguiente;
}*/

stack stack_destroy (stack s){
  stack aux_stack = s;
  while (s != NULL){
    s = s->next;
    free(aux_stack);
    aux_stack = NULL;
  }

  return (s);
}
