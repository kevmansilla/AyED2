#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "helpers/stack.h"
#include "helpers/queue.h"

static void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <phrase-to-check>\n\n"
           "Check if the phrase is a palindrome. Discards blank spaces from the "
           "given phrase when analysis is performed.\n",
           program_name);
}

static char* parse_phrase(int argc, char *argv[]) {
    /* Parse the phrase given by command line argument. */
    char *result=NULL;
    /* Program takes exactly one argument */
    if (argc != 2) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }
    /* Use the first argument ass the phrase */
    result = argv[1];
    /* return phrase */
    return result;
}

int main(int argc, char *argv[]) {
    // First parameter is used as phrase
    char *phrase=argv[1];
    //
    stack letters_lifo;
    bool is_palindrome=true;
    size_t i=0;
    // Parse arguments and get the phrase to be analysed
    phrase=parse_phrase(argc, argv);
    // Discard blank spaces
    queue letters_fifo;
    letters_fifo = queue_empty();
    while(phrase[i] != '\0'){
      if(phrase[i] != ' '){
        letters_fifo = queue_enqueue(letters_fifo, phrase[i]);
      }
      ++i;
    }
    /*
     * COMPLETAR: Crear una cola con todos los caracteres que no son espacios
     *
     */
    // A stack (lifo) needed for checking algorithm
    letters_lifo=stack_empty();
    // Save half phrase in the stack
    size_t size_noblank=0;  // COMPLETAR: Asignarle la cantidad de letras (sin espacios).
    size_t half_size=size_noblank / 2;
    while (stack_size(letters_lifo) != half_size) {
        queue_elem letter;
        letter = queue_first(letters_fifo);
        /*
         * COMPLETAR: Se deben ir sacando uno a uno los elementos de la cola
         * y agregarlos uno a uno en la pila
         */
        letters_lifo = stack_push(letters_lifo, letter);
        // COMPLETAR
    }
    if (size_noblank % 2 == 1) {
        // COMPLETAR: remover un elemento m??s de la cola
        letters_fifo = queue_dequeue(letters_fifo);
    }
    // For each letter in the stack must be one in the queue
    assert(queue_size(letters_fifo)==stack_size(letters_lifo));
    // Simetry check
    while (!stack_is_empty(letters_lifo)) {
        bool match_letter=false;
        /*
         * COMPLETAR: Se debe comparar el tope de la pila con el elemento que
         * sigue en la cola y verificar que coincidan. Luego se debe remover el
         * elemento de la cola.
         *
         */
        match_letter = match_letter && stack_top(letters_lifo);
        is_palindrome = is_palindrome && match_letter;
        letters_lifo = stack_pop(letters_lifo);
        // COMPLETAR
        letters_fifo = queue_dequeue(letters_fifo);
    }
    // Check emptyness simetry
    assert(queue_is_empty(letters_fifo));
    // Destroy instances (COMPLETAR)
    letters_lifo = stack_destroy(letters_lifo);

    printf(is_palindrome ? "es pal??ndromo!\n": "no es pal??ndromo\n");
    return 0;
}
