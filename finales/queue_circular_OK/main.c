/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Then, this project's includes, alphabetically ordered */
#include "queue.h"

size_t parse_queue_max_size(int argc, char *argv[]) {
    /* Parse max queue size*/
    int conversion = 0;
    // Program takes exactly two arguments
    // (the program's name itself and the input-filepath)
    bool valid_args_count = (argc == 2);

    if (!valid_args_count) {
        printf("You must provide a max queue size for testing");
        exit(EXIT_FAILURE);
    }

    conversion = atoi(argv[1]);
    if (conversion < 0) {
        printf("Cannot define a negative value for max queue size");
        exit(EXIT_FAILURE);
    }

    return (size_t)conversion;
}

static void test1(size_t max_size){
    //crear una cola vacia de tamaño max_size
    queue q = queue_empty(max_size);
    //verifica que cola este vacia
    if (queue_is_empty(q)) {
        printf("Queue is empty\n");
    } else {
        //imprimir cola
        queue_print(q);
    }
    // destroy
    q = queue_destroy(q);
}

static void test2(size_t max_size){
    //crear una cola vacia de tamaño max_size
    queue q = queue_empty(max_size);
    //imprimir cola
    queue_print(q);
    //introducir max_size elementos de orden consecutivo
    for (size_t i = 0; i < max_size; i++) {
        q = queue_enqueue(q, i);
    }
    //imprimir cola
    queue_print(q);
    //verificar que la cola este llena "Queue is full"
    if (queue_is_full(q)) {
        printf("Queue if full\n");
    }
    // destroy
    q = queue_destroy(q);
}

static void test3(size_t max_size){
    //crear una cola vacia de tamaño max_size
    queue q = queue_empty(max_size);
    //Imprimir la cola
    queue_print(q);
    //Introducir max_size elementos en orden consecutivo
    for (size_t i = 0; i < max_size; i++) {
        q = queue_enqueue(q, i);
    }
    //Imprimir la cola
    queue_print(q);
    //Verificar que la cola esté llena
    if (queue_is_full(q)) {
        printf("Queue if full\n");
    }
    // Obtener el primer elemento de la cola
    printf("Firs elemen -> %d\n", queue_first(q));
    // Desencolar 2 elementos
    q = queue_dequeue(q);
    q = queue_dequeue(q);
    // Imprimir la cola
    queue_print(q);
    // Encolar 2 elementos adicionales (4 y 5)
    q = queue_enqueue(q, 4);
    q = queue_enqueue(q, 5);
    // Imprimir la cola
    queue_print(q);
    //destroy
    q = queue_destroy(q);
}

int main(int argc, char *argv[]) {
    size_t max_size = 0u;

    /* parse the filepath given in command line arguments */
    max_size = parse_queue_max_size(argc, argv);
    test1(max_size);
    test2(max_size);
    test3(max_size);
    return EXIT_SUCCESS;
}

