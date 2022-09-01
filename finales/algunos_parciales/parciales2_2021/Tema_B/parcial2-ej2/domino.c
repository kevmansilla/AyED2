#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "domino.h"

struct _s_domino {
    int arriba;
    int abajo;
};


/* auxiliary functions for dumping */

static char mark(bool b) {
    return b ? 'O' : ' ';
}

static void dump_num(int num) {
  printf("      | %c     %c |\n",
         mark(num > 1), mark(num > 3));
  printf("      | %c  %c  %c |\n",
         mark(num > 5), mark(num % 2 == 1), mark(num > 5));
  printf("      | %c     %c |\n",
         mark(num > 3), mark(num > 1));
}

static void dump_double_num(int num) {
  printf(" --------------------- \n");
  printf(" | %c  %c  %c ", mark(num > 3), mark(num > 5), mark(num > 1));
  printf( "| %c  %c  %c |\n", mark(num > 3), mark(num > 5), mark(num > 1));

  printf(" |    %c    ", mark(num % 2 == 1));
  printf( "|    %c    |\n", mark(num % 2 == 1));

  printf(" | %c  %c  %c ", mark(num > 1), mark(num > 5), mark(num > 3));
  printf( "| %c  %c  %c |\n", mark(num > 1), mark(num > 5), mark(num > 3));
  printf(" --------------------- \n");
}

void dump(int num_up, int num_down) {
    /* Pretty dump funcion for cool visualization :) */
    if (num_up != num_down)  {
        printf("      ----------- \n");
        dump_num(num_up);
        printf("      |---------| \n");
        dump_num(num_down);
        printf("      ----------- \n");
    } else {
        dump_double_num(num_up);
    }
}

/* Representation invariant */

static bool invrep(domino p) {
    bool valid_domino = true;

    valid_domino = ((p->arriba == 0) || (p->arriba == 1) || (p->arriba == 2) ||
                   (p->arriba == 3) || (p->arriba == 4) || (p->arriba == 5) ||
                   (p->arriba == 6)) &&
                   ((p->abajo == 0) || (p->abajo == 1) || (p->abajo == 2) ||
                   (p->abajo == 3) || (p->abajo == 4) || (p->abajo == 5) ||
                   (p->abajo == 6));
    return valid_domino;
}

/* Public functions */

domino domino_new(int num_up, int num_down) {
    domino p;
    p = malloc(sizeof(struct _s_domino));
    p->arriba = num_up;
    p->abajo = num_down;

    assert(invrep(p));
    return p;
}

bool domino_is_double(domino p) {
    assert(invrep(p));
    bool is_double=false;
    if (p->arriba == p->abajo){
      is_double = true;
    }

    return is_double;
}

bool domino_eq(domino p1, domino p2) {
    assert(invrep(p1) && invrep(p2));
    bool equals=false;
    if (p1->arriba == p2->arriba && p1->abajo == p2->abajo){
      equals = true;
    } else if (p1->arriba == p2->abajo && p1->abajo == p2->arriba){
      equals = true;
    }

    return equals;
}

bool domino_matches(domino p_top, domino p_bottom) {
    assert(invrep(p_top) && invrep (p_bottom) && !domino_eq(p_top, p_bottom));

    bool is_match=false;
    if (p_top->abajo == p_bottom->arriba){
      is_match = true;
    }
    return is_match;
}

domino domino_flip(domino p) {
    assert(invrep(p));
    return domino_new(p->abajo, p->arriba);
}

void domino_dump(domino p) {
    assert(invrep(p));
    dump(p->arriba, p->abajo);
}

domino domino_destroy(domino p) {
    free(p);
    p = NULL;
    return p;
}
