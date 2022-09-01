#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "cn_match.h"
#include "card.h"

struct _s_match {
  struct _s_match *next;
  struct _s_card *card;
};

struct _s_card {
  unsigned int number;
  char suit;
  unsigned int player;
};

cn_match match_new(void) {
  cn_match match = NULL;
  return match;
}

cn_match match_add(cn_match match, card c) {
  struct _s_match *new_match = calloc(1, sizeof(struct _s_match));
  new_match->card = c;
  new_match->next = match;
  return new_match;
}

unsigned int match_size(cn_match match) {
  unsigned int size = 0u;
  struct _s_match *aux = match;

  while (aux != NULL) {
    aux = aux->next;
    size++;
  }
  
  return size;
}

unsigned int match_length(cn_match match) {
  unsigned int length = 0u;
  unsigned int size = match_size(match);

  if (match != NULL) {
    if (is_match_correct(match)) {
      length = size / 2;
    }
  }
  
  return length;
}

bool is_match_correct(cn_match match) {
  bool correctness = true;
  unsigned int counter = 0u;
  struct _s_match *izq = NULL;
  struct _s_match *der = match;

  while (der!= NULL) {
    izq = der;
    der = der->next;
    counter++;
  // Cartas intercaladas
    if (der != NULL) {
      correctness = (card_player(izq->card) != card_player(der->card)) ? correctness && true: false;
    }
  }
  
  // La primera carta es del player 1
  correctness = card_player(izq->card) == 1u ? correctness && true: false;

  // Cantidad de cartas par
  correctness = (counter % 2) == 0u ? correctness && true : false;

  return correctness;
}

unsigned int winner_total_points(cn_match match) {
  unsigned int points = 0;

  if(is_match_correct(match)) {

    unsigned int len = match_length(match);
    cn_match aux = match;
    cn_match prev_ref;

    unsigned int c1 = 0u;
    unsigned int c2 = 0u;
  
    if (len >= 1) {
      prev_ref = match;
      aux = aux->next;
      len = len -1;
      c1 = c1 + card_pair_points(aux->card,prev_ref->card,1);
      c2 = c2 + card_pair_points(aux->card,prev_ref->card,2);
    }

    while(len > 0) {
      //card fst, card snd, unsigned int player
      prev_ref = aux->next;
      aux = prev_ref->next;
      len = len - 1;
      c1 = c1 + card_pair_points(aux->card,prev_ref->card,1);
      c2 = c2 + card_pair_points(aux->card,prev_ref->card,2);
    } 

    points = (c1 > c2) ? c1 : c2;
  }
  
  assert((int)points >=0);
  return points;
}

card * match_to_array(cn_match match) {
  card *array = calloc(match_size(match), sizeof(card));
  for (int i = match_size(match)-1; i >= 0; i--) {
    array[i] = match->card;
    match = match->next;
  }

  return array;
}

void match_dump(cn_match match) {
  card *array = match_to_array(match);
  for (unsigned int i = 0u; i < match_size(match); i++) {
    card_dump(array[i]);
  }
}

cn_match match_destroy(cn_match match) {
  struct _s_match *killme;

  while (match != NULL) {
    killme = match;
    match->card = card_destroy(match->card);
    match = match->next;
    free(killme);
  }
  free(match);
  match = NULL;

  return NULL;
}
