#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "card.h"
#include "cf_match.h"

struct s_match {
    card elem;
    struct s_match * next;
};

cf_match match_new(void) {
    return NULL;
}

cf_match match_add(cf_match match, card c) {
    struct s_match * new_node = calloc(1, sizeof(struct s_match));
    new_node->elem = c;
    new_node->next = NULL;
    if (match != NULL) {
        struct s_match * tmp = match;
        while (tmp->next!=NULL) {
            tmp = tmp->next;
        }
        tmp->next = new_node;
        return match;
    } else {
        return new_node;
    }
}

unsigned int match_size(cf_match match) {
    unsigned int size = 0U;
    struct s_match * tmp = match;
    while (tmp != NULL) {
        tmp = tmp->next;
        size++;
    }
    return size;
}

bool is_match_correct(cf_match match) {
    // - El jugador 1 inició la partida.
    // - La cantidad de cartas es par.
    if (card_player(match->elem)!=1 || match_size(match)%2!=0) {
        return false;
    } 
    bool is_correct = true;
    struct s_match * tmp = match;
    while (tmp->next!=NULL) {
        // - Cada carta c del jugador 1, está seguida de una carta c’ del jugador 2.
        if (card_player(tmp->elem)==1 && card_player(tmp->next->elem)!=2) {
            is_correct = false;
        }
        // - Nunca dos cartas contiguas pertenecen al mismo jugador.
        if (card_player(tmp->elem) == card_player(tmp->next->elem)) {
            is_correct = false;
        }
        // - Nunca dos cartas contiguas tienen el mismo color.
        if (card_color(tmp->elem) == card_color(tmp->next->elem)) { 
            is_correct = false;
        }
        tmp = tmp->next;
    }
    return is_correct;    
}

static int player_score(cf_match match, unsigned int player) {
    int points = 0;
    struct s_match * tmp = match;
    bool is_Flush = false;
    bool is_Upwards = false;
    unsigned int len = match_size(match);

    while (len > 0 && tmp->next->next != NULL) {
        if (card_player(tmp->next->elem) == player) {
            points += card_drop_points(tmp->elem, tmp->next->elem, is_Flush, is_Upwards);
        }
        if (card_number(tmp->elem) == card_number(tmp->next->elem)-1) {
            is_Flush = true;
            is_Upwards = true;
        } else if (card_number(tmp->elem) == card_number(tmp->next->elem)+1){
            is_Flush = true;
            is_Upwards = false;
        } else {
            is_Flush = false;
        }
        tmp = tmp->next;
        len--;
    }
    return points;
}

unsigned int match_winner(cf_match match) {
    if (is_match_correct(match)) {
        int playerOneScore = player_score(match, 1);
        int playerTwoScore = player_score(match, 2);

        if (playerOneScore == playerTwoScore) {
            return 0;
        } 
        return (playerOneScore > playerTwoScore) ? 1U : 2U;

    } else {
        return -1;
    }
}

unsigned int winner_total_points(cf_match match) {
    if (!is_match_correct(match)) {
        return -1;
    }

    int playerOneScore = player_score(match, 1);
    int playerTwoScore = player_score(match, 2);

    if (playerOneScore == playerTwoScore) {
        return 0;
    }
    return playerOneScore > playerTwoScore ? playerOneScore : playerTwoScore;
}

card* match_to_array(cf_match match) {
    card* array = calloc(match_size(match), sizeof(card));
    struct s_match * tmp = match;
    unsigned int i = 0U;
    while (tmp!=NULL) {
        array[i] = tmp->elem;
        tmp = tmp->next;
        i++;
    }
    return array;
}

void match_dump(cf_match match) {
    card* array = match_to_array(match);
    for (unsigned int i = 0u; i < match_size(match); i++) {
        card_dump(array[i]);
    }
    free(array);
}

cf_match match_destroy(cf_match match) {
    while (match!=NULL) {
        struct s_match * tmp = match->next;
        card_destroy(match->elem);
        free(match);
        match = tmp;
    }
    free(match);
    match = NULL;
    return match;
}
