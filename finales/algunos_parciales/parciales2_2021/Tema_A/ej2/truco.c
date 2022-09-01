#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "truco.h"

struct _s_truco_card {
    int valor;
    char palo;
};

#define ESPADA "ESPADA"
#define BASTO  "BASTO"
#define ORO    "ORO"
#define COPA   "COPA"

static const char *suit_str(char p) {
    const char *str;
    if (p == 'e') {
        str = ESPADA;
    } else if (p=='b') {
        str = BASTO;
    } else if (p=='o') {
        str = ORO;
    } else if (p=='c') {
        str = COPA;
    }
    return str;
}

static void dump(int num, char suit) {
    printf(" ----------------\n"
           " : %2d           :\n"
           " :              :\n"
           " :              :\n"
           " :    ""%-7s""   :\n"
           " :              :\n"
           " :              :\n"
           " :              :\n"
           " :           %2d :\n"
           " ----------------\n",
           num, suit_str(suit), num);
}

static int card_rank(int num, char suit) {
    int rank=0;

    if (4 <= num && num <= 12) {
      rank = num - 4; // 4 ~ 12
    } else { // 1 ~ 3
      rank = num + 8;
    }
    // 0 <= rank <= 11
    if (num==1 && suit == 'e') {      // Ancho de espadas
      rank = 15;
    } else if (num==1 && suit=='b') { // Ancho de bastos
      rank = 14;
    } else if (num==7 && suit=='e') { // Siete de espadas
      rank = 13;
    } else if (num==7 && suit=='o') { // Siete de oro
      rank = 12;
    }
    return rank;
}

//The value for `num` must verify: 1 <= num <= 12 /\ num != 8 /\ num != 9
//The value for `p` must verify  : p=='e' \/ p=='o' \/ 'p=='c' \/ p=='b
/*
static bool invrep(truco_card c) {
    bool valid_card=true;

    valid_card = (c==NULL) || ((c->valor >= 1 && c->valor <=12 && c->valor != 7 && c->valor != 8)    && (c->palo == 'e' || c->palo == 'b' || c->palo == 'c' || c->palo == 'o'));

    return valid_card;
}*/

truco_card truco_card_new(int num, char p) {
    truco_card card;
    card = malloc(sizeof(struct _s_truco_card));
    card->valor = num;
    card->palo = p;

    return card;
}

bool truco_card_win(truco_card a, truco_card b) {
    bool card_a_win=false;

    if (card_rank(a->valor, a->palo) > card_rank(b->valor, a->palo)){
      card_a_win = true;
    } else {
      card_a_win =false;
    }


    return card_a_win;
}

bool truco_card_tie(truco_card a, truco_card b) {
    bool is_a_tie=false;

    if (card_rank(a->valor, a->palo) == card_rank(b->valor, b->palo)){
      is_a_tie = true;
    }
    return is_a_tie;
}

void truco_card_dump(truco_card c) {
    dump(c->valor, c->palo);
}

truco_card truco_card_destroy(truco_card c) {
    free(c);
    c = NULL;

    return c;
}
