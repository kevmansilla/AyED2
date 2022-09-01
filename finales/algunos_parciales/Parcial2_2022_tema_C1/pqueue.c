#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue {
    unsigned int size;
    struct s_node **array;
    priority_t min_priority;
};

struct s_node {
    pqueue_elem elem;
    struct s_node *next;
};

static struct s_node *create_node(pqueue_elem e) {
    struct s_node* new_node = calloc(1, sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->next = NULL;
    return new_node;
}

static struct s_node *destroy_node(struct s_node *node) {
    assert(node != NULL);
    free(node);
    node = NULL;
    return node;
}

static bool invrep(pqueue q) {
    return q != NULL;
}

pqueue pqueue_empty(priority_t min_priority) {
    pqueue queue = malloc(sizeof(struct s_pqueue));
    queue->size = 0u;
    queue->array = calloc(min_priority+1, sizeof(struct s_node));
    queue->min_priority = min_priority;
    assert(invrep(queue) && pqueue_is_empty(queue));
    return queue;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, priority_t priority) {
    assert(invrep(q));
    struct s_node *new_node = create_node(e);

    if (q->array[priority] == NULL) {
        q->array[priority] = new_node;
    } else{
        struct s_node *tmp = q->array[priority];
        while(tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp->next = new_node;
    }
    q->size++;
    if (priority > q->min_priority) {
        q->min_priority = priority;
    }

    assert(invrep(q) && !pqueue_is_empty(q));
    return q;
}

bool pqueue_is_empty(pqueue q) {
    assert(invrep(q));
    return q->size == 0u; 
}

pqueue_elem pqueue_peek(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    pqueue_elem res;
    pqueue tmp = q;
    priority_t i = 0u;
    while(tmp->array[i] == NULL){
        ++i;
    }
    res = tmp->array[i]->elem;
    return res;
}

priority_t pqueue_peek_priority(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    pqueue tmp = q;
    priority_t i = 0u;
    while(tmp->array[i] == NULL){
        ++i;
    }
    return i;
}

size_t pqueue_size(pqueue q) {
    assert(invrep(q));
    return q->size; 
}

pqueue pqueue_dequeue(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    pqueue tmp = q;
    priority_t i = 0u;
    while(tmp->array[i] == NULL){
        ++i;
    }
    struct s_node *node_tmp = tmp->array[i];
    tmp->array[i] = tmp->array[i]->next;
    node_tmp = destroy_node(node_tmp);
    tmp->size = tmp->size - 1;
    q = tmp;
    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q) {
    assert(invrep(q));
    struct s_node *tmp = NULL;
    for (unsigned int i = 0u; i <= q->min_priority; ++i) {
        while (q->array[i] != NULL) {
            tmp = q->array[i];
            q->array[i] = q->array[i]->next;
            destroy_node(tmp);
            tmp = NULL;
        }
    }
    free(q->array);
    free(q);
    q = NULL;
    return q;
}
