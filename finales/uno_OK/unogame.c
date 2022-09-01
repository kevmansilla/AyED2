#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>

#include "unogame.h"
#include "card.h"

#define NO_PLAYER -1

struct s_ugame {
    card_t card;
    player_t player;
    unogame_t next;
};

unogame_t
uno_newgame(card_t card) {
    unogame_t discard_pile = malloc(sizeof(struct s_ugame));
    if (discard_pile == NULL) {
        printf("No se pudo asignar memoria");
        exit(1);
    }
    discard_pile->card = card;
    discard_pile->player = NO_PLAYER;
    discard_pile->next = NULL;
    return discard_pile;
}

card_t
uno_topcard(unogame_t uno) {
    assert(uno != NULL);
    return uno->card;
}

unogame_t
uno_addcard(unogame_t uno, card_t c) {
    assert(uno != NULL && c != NULL);
    unogame_t new_card = malloc(sizeof(struct s_ugame));
    new_card->card = c;
    new_card->player = uno_nextplayer(uno);
    new_card->next = uno;
    uno = new_card;
    return uno;
}

unsigned int
uno_count(unogame_t uno) {
    assert(uno != NULL);

    unsigned int count = 0u;
    unogame_t aux = uno;
    while (aux != NULL) {
        count++;
        aux = aux->next;
    }
    return count;
}

bool uno_validpile(unogame_t uno) {
    assert(uno != NULL);
    bool valid = true;
    card_t first_card;
    unogame_t aux = uno;
    while (aux->next != NULL) {
        aux = aux->next;
    }
    first_card = aux->card;

    valid = (card_get_type(first_card) != change_color);

    aux = uno;
    while (aux->next != NULL && valid) {
        valid = card_compatible(aux->card, aux->next->card);
        aux = aux->next;
    }
    return valid;
}

color_t
uno_currentcolor(unogame_t uno) {
    assert(uno != NULL);
    return card_get_color(uno->card);
}

player_t
uno_nextplayer(unogame_t uno) {
    assert(uno != NULL);
    player_t next_player;
    if (card_get_type(uno->card) == skip) {
        if (uno->player == NUM_PLAYERS - 1) {
            next_player = 1;
        }
        else {
            next_player = uno->player + 1;
            if (next_player == NUM_PLAYERS - 1) {
                next_player = 0;
            }
            else {
                next_player = next_player + 1;
            }
        }
    }
    else {
        if (uno->player == NUM_PLAYERS - 1) {
            next_player = 0;
        }
        else {
            next_player = uno->player + 1;
        }
    }
    return next_player;
}

card_t *
uno_pile_to_array(unogame_t uno) {
    card_t *array = NULL;
    unogame_t aux = uno;
    unsigned int length = uno_count(uno);
    array = calloc(length, sizeof(struct s_ugame));

    for (unsigned int i = length-1; i < length; i--) {
        array[i] = aux->card;
        aux = aux->next;
    }
    return array;
}

unogame_t
uno_destroy(unogame_t uno) {
    unogame_t aux = NULL;
    while (uno != NULL) {
        aux = uno;
        uno = uno->next;
        aux->card = card_destroy(aux->card);
        free(aux);
    }
    aux = NULL;
    return uno;
}
