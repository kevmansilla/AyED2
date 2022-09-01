/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Then, this project's includes, alphabetically ordered */
#include "queue.h"

static const queue_elem ELEM1 = 1;
static const queue_elem ELEM2 = 7;
static const queue_elem ELEM3 = 12;
static const queue_elem ELEM4 = 17;
static const size_t QUEUE_SIZE = 3u;

static void test(void){
    queue q = queue_empty(QUEUE_SIZE);
    printf("Empty queue\n");
    queue_print(q);
    q = queue_enqueue(q, ELEM1);
    queue_print(q);
    q = queue_enqueue(q, ELEM2);
    queue_print(q);
    q = queue_enqueue(q, ELEM3);
    queue_print(q);
    q = queue_dequeue(q);
    queue_print(q);
    q = queue_dequeue(q);
    queue_print(q);
    q = queue_enqueue(q, ELEM4);
    queue_print(q);
    q = queue_destroy(q);
}


int main(void) {
    test();
    return EXIT_SUCCESS;
}

