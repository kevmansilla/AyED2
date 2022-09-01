#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "queue.h"

struct s_queue {
    queue_elem *elems; //array to store elements
    int maxsize;       //max capacity of queue
    int front;         //front point
    int last;          //last element
    int size;          //current capacity
};

static bool invrep(queue q) {
    return (q != NULL ? ((q->size <= q->maxsize) &&
                                (q->elems != NULL) && (q->size >= 0)) : true);
}

queue queue_empty(size_t max_size) {
    queue q = (struct s_queue*) malloc(sizeof(struct s_queue));
    if (q == NULL) {
        fprintf(stderr, "--ERROR-- could not allocate memory.\n");
        return NULL;
    }
    q->elems = calloc(max_size, sizeof(queue_elem));
    if (q->elems == NULL) {
        fprintf(stderr, "--ERROR-- could not allocate memory.\n");
        return NULL;
    }
    q->maxsize = max_size;
    q->front = 0;
    q->last = -1; 
    q->size = 0;
    assert(invrep(q) && queue_is_empty(q));
    return q;
}

queue queue_enqueue(queue q, queue_elem e) {
    assert(invrep(q) && !queue_is_full(q));
    printf("Inserting element-> %d\n", e);
    q->last = (q->last + 1) % q->maxsize;
    q->elems[q->last] = e;
    q->size++;
    printf("front-> %d, last-> %d\n", q->front, q->last);
    printf("size-> %d\n", q->size);
    assert(invrep(q) && !queue_is_empty(q));
    return q;
}

bool queue_is_empty(queue q) {
    assert(invrep(q));
    return q->size == 0;
}

bool queue_is_full(queue q) {
    assert(invrep(q));
    return q->size == q->maxsize;
}

queue_elem queue_first(queue q) {
    assert(invrep(q) && !queue_is_empty(q));
    return q->elems[q->front];
}

size_t queue_size(queue q) {
    assert(invrep(q));
    return q->size;
}

queue queue_dequeue(queue q) {
    assert(invrep(q) && !queue_is_empty(q));
    printf("Removing element-> %d\n", queue_first(q));
    q->front = (q->front + 1) % q->maxsize;
    q->size--;
    printf("front-> %d, last-> %d\n", q->front, q->last);
    printf("size-> %d\n", q->size);
    assert(invrep(q) && !queue_is_full(q));
    return q;
}

void queue_print(queue q) {
    if (queue_is_empty(q)) {
        printf("[]\n");
    } else {
        printf("[%d", q->elems[0]);
        for (size_t i = 1; i < queue_size(q); i++){
            printf(",%d", q->elems[i]);
        }
        printf("]\n");
    }
    assert(invrep(q));
}

queue queue_destroy(queue q) {
    assert(invrep(q));
    if (q != NULL) {
        if (q->elems != NULL) {
            free(q->elems);
            q->elems = NULL;
        }
        free(q);
        q = NULL;
    }
    assert(q == NULL);
    return q;
}
