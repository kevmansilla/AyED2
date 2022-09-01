#include "dna.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

struct s_dna_t {
    unsigned int length;
    struct s_node * elems;
};

struct s_node {
    struct s_node * next;
    nucleobase_t elem;
};

static struct s_node * single_node(nucleobase_t e) {
    struct s_node * res = calloc(1, sizeof(struct s_node));
    res->elem = e;
    res->next = NULL;
    return res;
}

dna_t dna_T() {
    struct s_dna_t * res = calloc(1, sizeof(struct s_dna_t)) ;
    res->length = 1U;
    res->elems = single_node(T);
    return res;
}

dna_t dna_C() {
    dna_t res = calloc(1, sizeof(struct s_dna_t)) ;
    res->length = 1U;
    res->elems = single_node(C);
    return res;
}

dna_t dna_A() {
    dna_t res = calloc(1, sizeof(struct s_dna_t)) ;
    res->length = 1U;
    res->elems = single_node(A);
    return res;
}

dna_t dna_G() {
    dna_t res = calloc(1, sizeof(struct s_dna_t)) ;
    res->length = 1U;
    res->elems = single_node(G);
    return res;
}

dna_t dna_join(dna_t first, dna_t second) {
    if (second->elems!=NULL) {
        struct s_node * p1 = first->elems;
        while (p1->next!=NULL) {
            p1 = p1->next;
        }

        // en este momento puedo asumir que p2!=NULL
        struct s_node * p2 = second->elems;
        while (p2!=NULL) {
            p1->next = single_node(p2->elem);
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    first->length +=second->length;
    return first;
}

unsigned int dna_length(dna_t dna) {
    return dna->length;
}

void print_elem(nucleobase_t e) {
    // T, C, A, G
    if (e==T) {
        printf("T");        
    } else if (e==C) {
        printf("C");        
    } else if (e==A) {
        printf("A");        
    } else if (e==G) {
        printf("G");        
    }
}

void dna_print(dna_t dna) {
    struct s_node * tmp = dna->elems;
    while (tmp!=NULL) {
        print_elem(tmp->elem);
        tmp = tmp->next;
    }
    printf("\n");
}

bool dna_is_prefix(dna_t first, dna_t second) {
    if (first->length <= second->length) {
        bool is_prefix = true;
        struct s_node * p1 = first->elems;
        struct s_node * p2 = second->elems;
        is_prefix = (p1->elem == p2->elem);
        while (is_prefix && p1->next!=NULL) {
            is_prefix = (p1->elem == p2->elem);
            p1 = p1->next;
            p2 = p2->next;
        }
        return is_prefix;
    } else {
        return false;
    }
}

bool dna_is_equal(dna_t first, dna_t second) {
    if(first->length == second->length) {
        bool is_equal = dna_is_prefix(first, second) && dna_is_prefix(second, first);
        return is_equal;
    } else {
        return false;
    }
}

dna_t *dna_cut(dna_t dna, unsigned int count) {
    dna_t* res = calloc(2, sizeof(struct s_dna_t));
    struct s_dna_t * dna1 = calloc(1, sizeof(struct s_dna_t));
    struct s_dna_t * dna2 = calloc(1, sizeof(struct s_dna_t));
    dna1->length = count;
    dna2->length = dna_length(dna) - count;
    unsigned int i = 0;
    struct s_node * p1 = dna->elems;
    struct s_node * tmp;
    while (i < count) {
        if (i==0) {
            dna1->elems = single_node(p1->elem);
            tmp = dna1->elems;
        } else {
            tmp->next = single_node(p1->elem);
            tmp = tmp->next;
        }
        p1 = p1->next;
        i++;
    }
    while (i < dna_length(dna)) {
        if (i==count) {
            dna2->elems = single_node(p1->elem);
            tmp = dna2->elems;
        } else {
            tmp->next = single_node(p1->elem);
            tmp = tmp->next;
        }
        p1 = p1->next;
        i++;
    }
    res[0] = dna1;
    res[1] = dna2;
    return res;
}

dna_t dna_destroy(dna_t dna) {
    while (dna->elems!=NULL) {
        struct s_node * tmp = dna->elems->next;
        free(dna->elems);
        dna->elems = tmp;
    }
    free(dna->elems);
    free(dna);
    dna = NULL;
    return dna;
}
