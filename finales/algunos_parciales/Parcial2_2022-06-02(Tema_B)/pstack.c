#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"

struct s_pstack {
    struct s_node *first;
    unsigned int size;
};

struct s_node {
    pstack_elem elem;
    unsigned int priority;
    struct s_node *next;
};

static struct s_node * create_node(pstack_elem e, priority_t priority) {
    struct s_node *new_node = NULL;
    new_node = calloc(1, sizeof(struct s_node));
    assert(new_node != NULL);
    new_node->elem = e;
    new_node->priority = priority;
    new_node->next = NULL;
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    assert(node != NULL);
    free(node);
    node = NULL;
    assert(node == NULL);
    return node;
}

static bool invrep(pstack s) {
    bool check = true;
    struct s_node *tmp = s->first;
    while (check && tmp != NULL && tmp->next != NULL) {
        if (tmp->priority < tmp->next->priority) {
            check = false;
        }
        tmp = tmp->next;
    }
    return check;
}

// static bool invrep(pstack s)
// {
//     bool inv = (s != NULL);
//     if (inv)
//     {
//         struct s_node *p = s->first;
//         if (p != NULL)
//         {
//             while (p->next != NULL && inv)
//             {
//                 inv = inv && (p->prio >= p->next->prio);
//                 p = p->next;
//             }
//         }
//     }

//     return inv;
// }

pstack pstack_empty(void) {
    pstack s=NULL;
    s = calloc(1, sizeof(struct s_pstack));
    s->size = 0;
    s->first = NULL;
    return s;
}

pstack pstack_push(pstack s, pstack_elem e, priority_t priority) {
    assert(invrep(s));
    struct s_node *new_node = create_node(e, priority);
    if (pstack_is_empty(s)) {
        s->first = new_node;
    } else {
        struct s_node *tmp = s->first;
        if (new_node->priority >= tmp->priority) {
            new_node->next = tmp;
            s->first = new_node;
        } else {
            while (tmp->next != NULL && new_node->priority < tmp->next->priority) {
                tmp = tmp->next;
            }
            new_node->next = tmp->next;
            tmp->next = new_node;
        }
    }
    ++s->size;
    return s;
}

bool pstack_is_empty(pstack s) {
    return s->size == 0;
}

pstack_elem pstack_top(pstack s) {
    return s->first->elem;
}

priority_t pstack_top_priority(pstack s) {
    return s->first->priority;
}

unsigned int pstack_size(pstack s) {
    assert(invrep(s));
    return s->size;
}

pstack pstack_pop(pstack s) {
    struct s_node *tmp = s->first;
    s->first = tmp->next;
    tmp = destroy_node(tmp);
    --s->size;
    return s;
}

pstack pstack_destroy(pstack s) {
    assert(invrep(s));
    struct s_node *tmp = NULL;
    while (s->first != NULL) {
        tmp = s->first;
        s->first = tmp->next;
        free(tmp);
        tmp = NULL;
    }
    free(s);
    s = NULL;
    assert(s == NULL);
    return s;
}

