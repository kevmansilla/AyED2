#include <stdlib.h>
#include "fence.h"

struct _fence_t {
    fence_t next;
    type_t type;
};

fence_t fence_P() {
    fence_t f = calloc(1, sizeof(struct _fence_t));
    f->type = 0;
    f->next = NULL;

    return f;
}

fence_t fence_add_P(fence_t fence) {
    fence_t f = calloc(1, sizeof(struct _fence_t));
    f->type = 0;
    f->next = NULL;

    if (fence != NULL) {
        f->next = fence;
        fence = f;
    } else {
        fence = f;
    }

    return fence;
}

fence_t fence_add_A(fence_t fence) {
    fence_t f = calloc(1, sizeof(struct _fence_t));
    f->type = 1;
    f->next = NULL;

    if (fence != NULL) {
        f->next = fence;
        fence = f;
    } else {
        fence = f;
    }

    return fence;
}

fence_t fence_add_H(fence_t fence) {
    fence_t f = calloc(1, sizeof(struct _fence_t));
    f->type = 2;
    f->next = NULL;

    if (fence != NULL) {
        f->next = fence;
        fence = f;
    } else {
        fence = f;
    }

    return fence;
}

fence_t fence_add_T(fence_t fence) {
    fence_t f = calloc(1, sizeof(struct _fence_t));
    f->type = 3;
    f->next = NULL;

    if (fence != NULL) {
        f->next = fence;
        fence = f;
    } else {
        fence = f;
    }

    return fence;
}

static bool check_T(fence_t fence) {
    bool check = false;
    fence_t aux_f = fence;

    while (aux_f != NULL && aux_f->type != 3) {
        aux_f = aux_f->next;
    }
    if (aux_f != NULL) {
        check = true;
    }

    return check;
}

bool fence_is_correct(fence_t fence) {
    bool is_correct = false;
    bool T = false;
    bool P_by_side = true;

    if (fence != NULL) {
        fence_t aux_f = fence;
        T = check_T(fence);
        if (T && aux_f->type == 0) {
            fence_t anterior;
            while (aux_f->next != NULL && P_by_side) {
                anterior = aux_f;
                aux_f = aux_f->next;
                if (aux_f->type != 0) {
                    P_by_side = anterior->type == 0 && aux_f->next->type == 0;
                }
                else {
                    P_by_side = true;
                }
            }
        }
        else {
            P_by_side = false;
        }
    }
    is_correct = T && P_by_side;

    return is_correct;
}

unsigned int fence_perimeter(fence_t fence) {
    fence_t aux_f = fence;
    unsigned int perimeter = 0u;

    while (aux_f != NULL) {
        if (aux_f->type != 0) {
            perimeter = perimeter + 3u;
        }
        aux_f = aux_f->next;
    }

    return perimeter;
}

unsigned int fence_size(fence_t fence) {
    fence_t aux_f = fence;
    unsigned int n = 0u;

    while (aux_f != NULL) {
        n++;
        aux_f = aux_f->next;
    }

    return n;
}

type_t *fence_to_array(fence_t fence) {
    unsigned int size = fence_size(fence);
    fence_t aux_f = fence;
    type_t *a = NULL;

    if (aux_f != NULL) {
        a = calloc(size, sizeof(type_t));
        for (unsigned int i = 0u; i < size; i++) {
            a[i] = aux_f->type;
            aux_f = aux_f->next;
        }
    }

    return a;
}

fence_t fence_destroy(fence_t fence) {
    fence_t aux_f = fence;
    while (fence != NULL) {
        fence = fence->next;
        free(aux_f);
        aux_f = fence;
    }
    free(aux_f);
    aux_f = NULL;

    return fence;
}