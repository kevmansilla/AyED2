#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include <assert.h>
#include "card.h"

struct s_card {
    unsigned int num;
    color_t color;
    type_t type;
};

static bool
invrep(card_t c) {
    // Invariante de representación
    bool valid=false;
    valid = c != NULL && c->num <= 9u && c->color <= 3 && c->type <= 2;

    return valid;
}

card_t
card_new(unsigned int num, color_t color, type_t s) {
    card_t card = malloc(sizeof(struct s_card));
    if (card == NULL) {
        printf("Error al dar memoria");
        exit(1);
    }
    card->num = num;
    card->color = color;
    card->type = s;

    return card;
}

type_t
card_get_number(card_t card) {
    assert(invrep(card));
    return card->num;
}

color_t
card_get_color(card_t card) {
    assert(invrep(card));
    return card->color;
}

type_t
card_get_type(card_t card) {
    assert(invrep(card));
    return card->type;
}

bool
card_samecolor(card_t c1, card_t c2) {
    assert(c1 != NULL && c2 != NULL);
    return (c1->color == c2->color);
}

bool
card_samenum(card_t c1, card_t c2) {
    assert(c1 != NULL && c2 != NULL);
    return (c1->num == c2->num);
}

static bool 
card_sametype(card_t c1, card_t c2) {
    assert(c1 != NULL && c2 != NULL);
    return (c1->type == c2->type);
}

bool card_compatible(card_t new_card, card_t pile_card) {
    bool compatible=false;
    assert(invrep(new_card) && invrep(pile_card));
    
    if (card_samecolor(new_card, pile_card)) {
        compatible = true;
    }
    if (card_samenum(new_card, pile_card) &&
                        card_sametype(new_card, pile_card)) {
        compatible = true;
    }
    if (card_get_type(new_card) == change_color) {
        compatible = true;
    }

    return compatible;
}

card_t
card_destroy(card_t card) {
    if (card != NULL) {
        free(card);
        card = NULL;
    }
    return card;
}
