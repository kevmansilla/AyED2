#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "truco.h"


int main(){
    int valor;
    char palo;
    truco_card a = NULL;
    truco_card b = NULL;

    printf("Ingrese el valor de la carta 1\n");
    scanf("%d",&valor);
    printf("Ingrese el palo de la carta 1\n");
    scanf(" %c",&palo);
    a = truco_card_new(valor, palo);

    printf("Ingrese el valor de la carta 2\n");
    scanf("%d",&valor);
    printf("Ingrese el palo de la carta 2\n");
    scanf(" %c",&palo);

    b = truco_card_new(valor, palo);

    if(truco_card_win(a,b)){
      printf("a es mayor que b\n");
      truco_card_dump(a);
      truco_card_dump(b);
    } else if (truco_card_tie(a,b)) {
      printf("La mano esta parda\n");
      truco_card_dump(a);
      truco_card_dump(b);
    } else{
      printf("b es mayor que a\n");
      truco_card_dump(a);
      truco_card_dump(b);
    }

    a = truco_card_destroy(a);
    b = truco_card_destroy(b);

    return 0;
}
