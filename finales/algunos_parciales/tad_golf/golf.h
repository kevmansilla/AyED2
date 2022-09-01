#ifndef GOLF_T
#define GOLF_T
#include <stdbool.h>

typedef struct _hoyos * hoyos;

/*Crea un hoyo*/
hoyos new_h ();
/*Agrega un hoyo nuevo a un hoyo ya creado*/
hoyos add_h (hoyos h, int golpes, int tipo);
/*Suma la cantidad de golpes totales del jugador*/
int sum_golpes(hoyos h);
/*Suma la cantidad de golpes totales de la cancha*/
int sum_cancha(hoyos h);
/*Devuelve true si el jugador esta haciendo menos golpes que los necesarios*/
bool is_good(hoyos h);
/*Destruye los hoyos*/
hoyos destroy_h(hoyos h);

#endif