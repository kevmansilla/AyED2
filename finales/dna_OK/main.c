#include "dna.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef TEST

int main() {

    printf("===Chequeo de crear un nodo===\n\n");
    dna_t dna1 = dna_T();
    dna_print(dna1);
    dna_t dna1_idem = dna_T();
    printf("\n");
    dna_t dna2 = dna_A();
    dna_print(dna2);
    printf("\n");
    dna_t dna3 = dna_G();
    dna_print(dna3);
    printf("\n");
    dna_t dna4 = dna_C();
    dna_print(dna4);
    printf("\n\n");

    printf("\n===Chequeo de join [PRIMARIO]===\n\n");
    dna1 = dna_join(dna1, dna2);
    dna1 = dna_join(dna1, dna3);
    dna1 = dna_join(dna1, dna4);
    dna_print(dna1);
    printf("\n\n");

    printf("\n===Chequeo de join [SECUNDARIO]===\n\n");
    dna1_idem = dna_join(dna1_idem, dna2);
    dna1_idem = dna_join(dna1_idem, dna3);
    dna_print(dna1_idem);
    printf("\n\n");

    printf("\n===Chequeo de length===\n\n");

    unsigned int length = dna_length(dna1);
    printf("length (joined1): %u", length);
    printf("\n");
    unsigned int length1 = dna_length(dna1_idem);
    printf("length (joined secundario): %u", length1);
    printf("\n\n");

    printf("\n===Chequeo de prefix [1]===\n\n");
    if (dna_is_prefix(dna1, dna2)) {
        printf("es prefijo\n");
    } else {
        printf("no es prefijo\n");
    }
    printf("\n\n");

    printf("\n===Chequeo de prefix [2]===\n\n");
    if (dna_is_prefix(dna1_idem, dna1)) {
        printf("es prefijo\n");
    } else {
        printf("no es prefijo\n");
    }
    printf("\n\n");

    printf("\n===Chequeo de equal [1] ===\n\n");
    if (dna_is_equal(dna2, dna2)) {
        printf("es igual\n");
    } else {
        printf("no es igual\n");
    }
    printf("\n\n");

    printf("\n===Chequeo de equal [2] ===\n\n");
    if (dna_is_equal(dna1, dna2)) {
        printf("es igual\n");
    } else {
        printf("no es igual\n");
    }
    printf("\n\n");

    printf("\n===Chequeo de cut===\n\n");
    dna_t *array = dna_cut(dna1, 2);
    printf("Primera parte:\n");
    dna_print(array[0]);
    printf("\n");
    printf("Segunda parte:\n");
    dna_print(array[1]);
    printf("\n\n");

    dna1 = dna_destroy(dna1);
    dna1_idem = dna_destroy(dna1_idem);
    dna2 = dna_destroy(dna2);
    dna3 = dna_destroy(dna3);
    dna4 = dna_destroy(dna4);
    array[0] = dna_destroy(array[0]);
    array[1] = dna_destroy(array[1]);
    free(array);
    array = NULL;

    return (0);
}

#endif
