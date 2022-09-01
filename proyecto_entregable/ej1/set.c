#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>            /* Definition of bool      */
#include <assert.h>
#include "set.h"
#include "set_elem.h"          /* Definition of set_elem */

struct s_set {
    set_elem elem;
    struct s_set *next;
};

static set new_node(set_elem e) {
    set new = calloc(1, sizeof(struct s_set));
    new->elem = e;
    return new;
}

/* CONSTRUCTORS */

set set_empty(void) {
    set s = NULL;
    return s;
}

set set_add(set s, set_elem e) {
    if (s != NULL) {
        set node = s;
        while (node->elem != e && node->next != NULL) {
            node = node->next;
        }
        if (node->elem != e) {
            node->next = new_node(e);
        }
    } else {
        s = new_node(e);
    }
    assert(s != NULL);
    return s;
}
/*  another option, but use tad functions
set set_clone(set s) {
    set copy = set_empty();
    set aux = s;
    while (aux != NULL) {
        copy = set_add(copy, aux->elem);
        aux = aux->next;
    }
    return copy;
}*/

set set_clone(set s) {
    set p,q,copy;
    if (!set_is_empty(s)){
        p = s;
        copy = calloc(1,sizeof(struct s_set));
        q = copy;
        while (!set_is_empty(p->next)){
            q->elem = p->elem;
            q->next = calloc(1,sizeof(struct s_set));
            q = q->next;
            p = p->next;
        }
        q->elem = p->elem;
        q->next = NULL;
    } else {
        copy = set_empty();
    }
    return copy;
}

/* OPERATIONS   */
unsigned int set_cardinal(set s) {
    unsigned int cardinal=0;
    while (s != NULL) {
        cardinal++;
        s = s->next;
    }
    return cardinal;
}

bool set_is_empty(set s) {
    return s == NULL;
}

bool set_member(set_elem e, set s) {
    set node = s;
    bool member = false;
    while (node != NULL && !member) {
        member = node->elem == e;
        node = node->next;
    }
    return member;
}

set set_elim(set s, set_elem e) {
    if (s != NULL) {
        if (s->elem == e) {
            set aux = s;
            s = s->next;
            free(aux);
        } else {
            set node = s->next, father = s;
            while (node != NULL && node->elem != e) {
                father = node;
                node = node->next;
            }
            if (node != NULL) {
                assert(node->elem == e);
                set aux = father->next;
                father->next = node->next;
                free(aux);
            }
        }
    }
    return s;
}

set_elem set_get(set s) {
    assert(s != NULL);
    return s->elem;
}

void set_dump(set s) {
    set node = s;
    printf("{ ");
    if (node != NULL) {
        while (node->next != NULL) {
            set_elem_dump(node->elem);
            printf(", ");
            node = node->next;
        }
        set_elem_dump(node->elem);
    }
    printf("}\n");
}

set set_destroy(set s) {
    while (s != NULL) {
        set aux = s;
        s = s->next;
        free(aux);
    }
    return s;
}
