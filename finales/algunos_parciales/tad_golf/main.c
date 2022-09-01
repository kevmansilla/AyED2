#include "golf.h"
#include <stdio.h>
#include <stdlib.h>

int main (){
    hoyos cancha = new_h();
    int golpes, tipo, handicap;
    printf("cuanto de handicap tiene?\n");
    scanf("%d", &handicap);
    for(unsigned int i = 1; i <= 3; ++i){
        printf("Cuantos golpes hizo en el hoyo %u?\n", i);
        scanf("%d", &golpes);
        printf("De cuantos golpes era el hoyo %u?\n", i);
        scanf("%d", &tipo);
        add_h(cancha, golpes, tipo);
        sum_golpes(cancha);
        sum_cancha(cancha);
    }
    int s_golpes = sum_golpes(cancha);
    int s_cancha = sum_cancha(cancha);
    int cuanto_hice = s_golpes - s_cancha;
    bool bueno_malo = is_good(cancha);
    destroy_h(cancha);

    if(bueno_malo == true){
        printf("Usted hizo menos tiros de lo debido, usted es bueno\n");
    } else{
        printf("Usted hizo mas tiros de lo debido, debe mejorar\n");
    }

    printf("Su resultado total bruto sin handicap es: %d\n", cuanto_hice);
    printf("Su resultado neto con handicap es: %d\n", cuanto_hice+handicap);

    return EXIT_SUCCESS;
}