#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "cf_match.h"
#include "card.h"

struct _s_match {
    card elem;
    struct _s_match *next;
};

cf_match match_new(void) {
    
    return NULL;
}

cf_match match_add(cf_match match, card c) {
    struct _s_match *new = malloc(sizeof(struct _s_match));
    struct _s_match *rec = match;
    new->elem = c;
    new->next = NULL;
    
    if(rec == NULL){
        match = new;
    }else{
        while(rec->next != NULL){
            rec = rec->next;
        }
        rec->next = new;
    }
    
    return match;
}

unsigned int match_size(cf_match match) {
    unsigned int size = 0u;
    struct _s_match *rec = match;
    while(rec != NULL){
        size++;
        rec = rec->next;
    }
    return size;
}

unsigned int match_length(cf_match match) {
    return (is_match_correct(match)) ? match_size(match)/2u : 0u;
}

bool is_match_correct(cf_match match) {
    bool valid_match = false;
    struct _s_match *rec = NULL;
    unsigned int size = 0u;
    if(match!=NULL){
        valid_match = (1u==card_player(match->elem));
        rec = match;
        size = 1u;
    }
    
    while(valid_match && (rec->next!=NULL)){
        valid_match = valid_match && (card_player(rec->elem) != card_player(rec->next->elem));
        rec = rec->next;
        size++;
    }
    return valid_match && (size%2==0);
}

static unsigned int player_score(cf_match match, unsigned int player) {
  /*
  * COMPLETAR:
  *
  * Calcula el puntaje de 'player' en el partido 'match'
  *
  */
    assert(is_match_correct(match));
    //unsigned int score = 0u;
    unsigned int scrone = 0u;
    unsigned int scrtwo = 0u;
    struct _s_match *rec = match;
    
    if(match != NULL){
        if(card_wins(rec->elem,rec->next->elem)){//1 gana
            scrone += card_match_points(rec->elem ,rec->next->elem);
        }else {//if(card_wins(rec->next->elem,rec->elem)){
            scrtwo += card_match_points(rec->elem ,rec->next->elem);
        }
    }
    
    while(rec->next->next != NULL){
        rec = rec->next->next;
        if(card_wins(rec->elem,rec->next->elem)){//1 gana
            scrone += card_match_points(rec->elem ,rec->next->elem);
        }else {//if(card_wins(rec->next->elem,rec->elem)){
            scrtwo += card_match_points(rec->elem ,rec->next->elem);
        }        
    }
    
    return (player == 1u)?scrone : scrtwo;
}

unsigned int winner_total_points(cf_match match) {
  /*COMPLETAR
  * tips:
  * * recordar que si is_match_correct es falso esto retorna 0
  * * usar player_score para calcular el puntaje de un jugador particular
  *
  */
    unsigned int points = 0u;
    unsigned int pointsone = 0u;
    unsigned int pointstwo = 0u;
    
    if(is_match_correct(match)){
        pointsone = player_score(match,1u);
        pointstwo = player_score(match,2u);
        
        if(pointsone > pointstwo){
            points = pointsone;
        }else if(pointsone < pointstwo){
            points = pointstwo;
        }
    }
    return points;
}

card * match_to_array(cf_match match) {
    card *array = NULL;
    assert(array==NULL);
    unsigned int size = match_size(match);
    unsigned int i = 0u;
    struct _s_match *rec = match;
    
    //array =(size!=0u)? calloc((size_t)size,sizeof(card)): NULL;
    array = calloc((size_t)size,sizeof(card));
    
    while(i<size){
        array[i] = rec->elem;
        rec = rec->next;
        i++;
    }
    
    assert(array!=NULL);
    return array;
}

void match_dump(cf_match match) {
  card *array = match_to_array(match);
  for (unsigned int i=0u; i < match_size(match); i++) {
    card_dump(array[i]);
  }
  free(array);
}

cf_match match_destroy(cf_match match) {
    struct _s_match *rec = match;
    struct _s_match *kill = NULL;
    match = NULL;
    while(rec!=NULL){
        kill = rec;
        rec = rec->next;
        free(kill);
        kill = NULL;
    }
    
    return rec;
}
