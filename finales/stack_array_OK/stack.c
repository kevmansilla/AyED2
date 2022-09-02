#include <stdlib.h>
#include <assert.h>

#include "stack.h"

#define CHUNK_CAPACITY 5

struct _s_stack {
    struct s_node *top;   //top
    unsigned int size;    //para contar nodos
};

struct s_node {
    unsigned int used;    //para contar los lugares del chunk
    stack_elem *chunk;    //chunk
    struct s_node *next;  //apunta al siguiente nodo
};

static bool
valid_chunks(stack s) {
    bool valid=true;
    struct s_node *check=s->top;
    if (check!=NULL) {
        valid = (check->used<=CHUNK_CAPACITY);
    }
    return valid;
}

static bool
invrep(stack s) {
    return ((s != NULL) && valid_chunks(s));
}

static struct s_node *
create_node(void) {
    struct s_node *new_node = calloc(1, sizeof(struct s_node));
    assert(new_node != NULL);
    new_node->chunk = calloc(CHUNK_CAPACITY+1, sizeof(stack_elem));
    assert(new_node->chunk != NULL);
    new_node->used = 0u;
    new_node->next = NULL;
    return new_node;
}

static struct s_node *
destroy_node(struct s_node *node) {
    assert(node != NULL);
    free(node->chunk);
    node->chunk = NULL;
    free(node);
    node = NULL;
    return node;
}

stack stack_empty(void) {
    stack new = calloc(1, sizeof(struct _s_stack));
    new->size = 0;
    new->top = NULL;
    assert(invrep(new) && stack_is_empty(new));
    return new;
}

stack stack_push(stack s, stack_elem e) {
    assert(invrep(s));
    s->size++;
    if (s->top == NULL) {
        struct s_node *aux = create_node();
        aux->chunk[aux->used] = e;
        aux->used++;
        s->top = aux;
    } else {
        struct s_node *otro = s->top;
        if (otro->used < CHUNK_CAPACITY) {
            otro->chunk[otro->used] = e;
            otro->used++;
        }
        else {
            struct s_node *new = create_node();
            new->chunk[new->used] = e;
            new->used++;
            new->next = s->top;
            s->top = new;
        }
    }
    assert(invrep(s) && !stack_is_empty(s));
    return s;
}

stack stack_pop(stack s) {
    assert(invrep(s) && !stack_is_empty(s));
    if (s->top != NULL) {
        struct s_node *aux = s->top;
        if (aux->used == 1 || aux->used == 0) {
            aux->used = aux->used - 1;
            s->top = aux->next;
            aux = destroy_node(aux);
        }
        else if (aux->used != 0) {
            aux->used--;
        }
        s->size--;
    }
    assert(invrep(s));
    return s;
}

unsigned int stack_size(stack s) {
    return s->size;
}

void stack_top(stack s, stack_elem *top) {
    if (s->top != NULL) {
        struct s_node *aux = s->top;
        *top = aux->chunk[aux->used - 1];
    }
}

bool stack_is_empty(stack s) {
    return s->size == 0 && s->top == NULL;
}

stack_elem *stack_to_array(stack s) {

    struct s_node *aux = s->top;
    unsigned int size = stack_size(s);
    stack_elem *array = calloc(size, sizeof(stack_elem));

    size = size - 1;
    while (aux != NULL) {
        unsigned int m = aux->used - 1;
        while (m < aux->used) {
            array[size] = aux->chunk[m];
            m--;
            size--;
        }
        aux = aux->next;
    }
    return array;
}

stack stack_destroy(stack s) {
    struct s_node *q = NULL;
    while (s->top != NULL) {
        q = s->top;
        s->top = s->top->next;
        q = destroy_node(q);
    }
    free(s);
    s = NULL;
    return s;
}