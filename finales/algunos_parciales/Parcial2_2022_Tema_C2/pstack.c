#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"

#include <stdio.h>

struct s_pstack {
    struct s_node **elems;
    priority_t max_priority;
    unsigned int size;
};

struct s_node {
    pstack_elem elem;
    struct s_node *next;
};

static struct s_node *create_node(pstack_elem e) {
    struct s_node *new_node = calloc(1, sizeof(struct s_node));
    assert(new_node != NULL);
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

static bool invrep(pstack s) {
    bool res = s != NULL;
    return res;
}

pstack pstack_empty(priority_t max_priority) {
    pstack s = malloc(sizeof(struct s_pstack));
    s->size = 0u;
    s->elems = calloc(max_priority+1, sizeof(struct s_node));
    s->max_priority = max_priority;
    assert(invrep(s) && pstack_is_empty(s));
    return s;
}

pstack pstack_push(pstack s, pstack_elem e, priority_t priority) {
    assert(invrep(s));
    struct s_node *new_node = create_node(e);
    if (s->elems[priority] == NULL) {
        s->elems[priority] = new_node;
    } else {
        struct s_node *tmp = s->elems[priority];
        // while (tmp != NULL) {
        //     tmp = tmp->next;
        // }
        new_node->next = tmp->next;
        tmp->next = new_node;
    }
    s->size++;
    if (priority >= s->max_priority) {
        priority = s->max_priority;
    }
    assert(invrep(s) && !pstack_is_empty(s));
    return s;
}

bool pstack_is_empty(pstack s) {
    assert(invrep(s));
    return s->size == 0;
}

pstack_elem pstack_top(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    pstack_elem res = 0;
    pstack tmp = s;
    priority_t i = 0u;
    while (tmp->elems[i] == NULL) {
        ++i;
    }
    res = tmp->elems[i]->elem;
    return res;
}

priority_t pstack_top_priority(pstack s) {
    pstack tmp = s;
    priority_t i = 0u;
    while (tmp->elems[i] == NULL) {
        i++;
    }
    return i;
}

size_t pstack_size(pstack s) {
    assert(invrep(s));
    return s->size;
}

pstack pstack_pop(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    pstack tmp = s;
    priority_t i = 0u;
    while (tmp->elems[i] == NULL) {
        ++i;
    }
    struct s_node *node_tmp = tmp->elems[i];
    tmp->elems[i] = tmp->elems[i]->next;
    node_tmp = destroy_node(node_tmp);
    tmp->size = tmp->size - 1;
    s = tmp;
    assert(invrep(s));
    return s;
}

pstack pstack_destroy(pstack s) {
    assert(invrep(s));
    struct s_node *tmp = NULL;
    for (unsigned int i = 0u; i <= s->max_priority; ++i) {
        while (s->elems[i] != NULL) {
            tmp = s->elems[i];
            s->elems[i] = s->elems[i]->next;
            tmp = destroy_node(tmp);
        }
    }
    free(s->elems);
    free(s);
    s = NULL;
    return s;
}
