#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>

#include "domino_line.h"
#include "domino.h"

struct _s_line {
    domino tile;
    domino_line next;
    domino_line previous;
};

domino_line line_new(domino first) {
    assert(first != NULL);
    domino_line line = calloc(1, sizeof(struct _s_line));
    if (line != NULL) {
        line->tile = first;
        line->next = NULL;
        line->previous = NULL;
    } else {
        fprintf(stderr, "--ERROR AL PEDIR MEMORIA--");
    }

    return line;
}

domino_line line_add(domino_line line, domino t) {
    /* COMPLETAR */
    assert(line != NULL && t != NULL);
    domino_line aux = NULL;
    aux = line_new(t);
    aux->previous = line;
    line->next = aux;
    line = aux;

    return line;
}

unsigned int line_length(domino_line line) {
    assert(line != NULL);
    unsigned int size = 0u;
    domino_line line_temp = line;

    while (line_temp != NULL) {
        line_temp = line_temp->previous;
        size++;
    }

    return size;
}

bool line_n_correct(domino_line line, unsigned int n) {
    /* COMPLETAR */
    assert(n < line_length(line));
    bool check = true;
    domino_line aux = line;
    unsigned int size = line_length(line);
   
    while (size - n - 1 > 0 && aux->previous != NULL) {
        aux = aux->previous;
        n++;
    }
    if (aux->previous != NULL) {
        check = domino_matches(aux->previous->tile, aux->tile);
    }
    if (aux->next != NULL) {
        check = check && domino_matches(aux->tile, aux->next->tile);
    }

    return check;
}

int line_total_points(domino_line line) {
    assert(line != NULL);
    int point = 0;
    domino_line line_temp = line;

    while (line_temp != NULL) {
        point += domino_up(line_temp->tile) + domino_down(line_temp->tile);
        line_temp = line_temp->previous;
    }

    return point;
}

domino * line_to_array(domino_line line) {
    assert(line != NULL);
    unsigned int i = 0u;
    unsigned int n = line_length(line);
    domino *array = (domino *)malloc(n * sizeof(domino));
    domino_line line_temp = line;

    while(i < n && line_temp != NULL) {
        array[n-i-1] = line_temp->tile;
        line_temp = line_temp->previous;
        i++;
    }

    return array;
}

void line_dump(domino_line line) {
    domino *array=line_to_array(line);
    for (unsigned int i=0u; i < line_length(line); i++) {
        domino_dump(array[i]);
    }
    free(array);
}

domino_line line_destroy(domino_line line) {
    domino_line line_temp = line;
    while(line != NULL) {
        line_temp = line;
        line = line->previous;
        domino_destroy(line_temp->tile);
        free(line_temp);
        line_temp = NULL;
    }

    return line;
}
