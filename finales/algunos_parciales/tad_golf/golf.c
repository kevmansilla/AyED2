#include "golf.h"
#include <stdlib.h>
#include <stdio.h>

struct _hoyos{
    int tipo;
    int golpes;
    hoyos next;
};

/*Crea un hoyo*/
hoyos new_h (){
    hoyos new_h = calloc(1, sizeof(struct _hoyos));
    new_h->golpes = 0;
    new_h->tipo = 0;
    new_h->next = NULL;
    return new_h;
}
/*Agrega un hoyo nuevo a un hoyo ya creado*/
hoyos add_h (hoyos h, int golpes, int tipo){
    hoyos add = calloc(1, sizeof(struct _hoyos));
    add->golpes = golpes;
    add->tipo = tipo;
    add->next = NULL;
    if(h != NULL){
        add->next = h;
        h = add;
    } else {
        h = add;
    }
    return h;
}
/*Suma la cantidad de golpes totales del jugador*/
int sum_golpes(hoyos h){
    int suma;
    hoyos h_aux = h;
    if(h_aux != NULL){
        while(h_aux != NULL){
            suma = suma + h_aux->golpes;
            h_aux = h_aux->next;
        }
    } else {
        printf("NO HAY HOYOS");
    }
    return suma;
}
/*Suma la cantidad de golpes totales de la cancha*/
int sum_cancha(hoyos h){
    int suma = 0;
    hoyos h_aux = h;
    if(h_aux != NULL){
        while(h_aux != NULL){
            suma = suma + h_aux->tipo;
            h_aux = h_aux->next;
        }
    } else {
        printf("NO HAY HOYOS");
    }
    return suma;
}
/*Devuelve true si el jugador esta haciendo menos golpes que los necesarios*/
bool is_good(hoyos h){
    bool resultado = false;
    int cant_golpes = sum_golpes(h);
    int cant_golpes_cancha = sum_cancha(h);
    return cant_golpes <= cant_golpes_cancha;
}
/*Destruye los hoyos*/
hoyos destroy_h(hoyos h){
    hoyos h_aux = h;
    while(h != NULL){
        h = h->next;
        h_aux = h;
    }
    free(h_aux);
    h_aux = NULL;
    return h;
}