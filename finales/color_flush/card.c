#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "card.h"

struct s_card {
    unsigned int number;
    char suit;
    unsigned int player;
};

#define DIAMANTE "DIAMANTE"
#define TREBOL "TREBOL"
#define CORAZON "CORAZON"
#define PICA "PICA"

static const char* suit_str(char p) {
    const char* str;
    if (p == 'd') {
        str = DIAMANTE;
    } else if (p == 't') {
        str = TREBOL;
    } else if (p == 'c') {
        str = CORAZON;
    } else {
        str = PICA;
    }
    return str;
}

/* Representation invariant */

static bool valid_suit(char p) {
    return p == 'd' || p == 't' || p == 'c' || p == 'p' || p == 'x';
}

static bool valid_player(int p) {
    return p == 1 || p == 2;
}

static bool invrep(card c) {
    bool valid_card = false;
    valid_card = c != NULL && 1 <= c->number && c->number <= 13 && valid_suit(c->suit) && valid_player(c->player);
    return valid_card;
}

/* Public functions */

card card_new(unsigned int num, char suit, unsigned int player) {
    assert(1 <= num && num <= 13 && valid_suit(suit) && valid_player(player));
    card new = malloc(sizeof(struct s_card));
    new->number = num;
    new->player = player;
    new->suit = suit;
    assert(invrep(new));
    return new;
}

unsigned int card_player(card c) {
    return c->player;
}

unsigned int card_number(card c) {
    return c->number;
}

char card_color(card c) {
    if (c->suit == 'd' || c->suit == 'c') {
        return 'R';
    }
    return 'N';
}

char card_suit(card c) {
    return c->suit;
}

bool card_equal_color(card fst, card snd) {
    return card_color(fst) == card_color(snd);
}

bool card_equal_number(card fst, card snd) {
    return card_number(fst) == card_number(snd);
}

int card_drop_points(card fst, card snd, bool isFlush, bool upwardsFlush) {
    int points = 0;
    // estoy en escalera
    if (isFlush) {
        // Si un jugador juega una carta del mismo número que la carta actual, ese jugador suma 7 puntos.
        // (solo si está en juego una escalera).
        if(fst->number == snd->number) {
            points = 7;
        } else {
            // Si un jugador juega una carta que continúa la escalera en el sentido actual, suma 3 puntos.
            if (upwardsFlush && fst->number+1 == snd->number) {
                points = 3;
            } else if (!upwardsFlush && fst->number-1 == snd->number) {
                points = 5;
            } else if (fst->number+1 != snd->number || fst->number-1 != snd->number) {
                points = -3;
            }
        }
    } 
    // no estoy en escalera
    else {
        // Si un jugador juega una carta que “comienza” una escalera no importa si es 
        // hacia arriba o abajo, ese jugador suma 5 puntos.
        if (fst->number == snd->number+1 || fst->number == snd->number-1) {
            points = 5;
        }
    }
    return points;
}

void card_dump(card c) {
    assert(invrep(c));
    printf("(%2d, %-7s, %2d)", c->number, suit_str(c->suit), c->player);
}

card card_destroy(card c) {
    free(c);
    c = NULL;
    return c;
}
