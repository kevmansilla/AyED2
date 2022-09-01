#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdbool.h>

typedef struct s_queue * queue;

typedef int queue_elem;

queue queue_empty(size_t max_size);
/*
 * DESC: Creates a new instance of queue for storing maximum 'max_size' elems
 *
 * PRE: {true}
 *  q = queue_empty(max_size);
 * POS: {q --> queue && queue_is_empty(q)}
 *
 */

queue queue_enqueue(queue q, queue_elem e);
/*
 * DESC: Adds element 'e' to the queue 'q'
 *
 * PRE: {q --> queue && !queue_is_full(q)}
 *  q = queue_enqueue(q, e);
 * POS: {q --> queue && !queue_is_empty(q)}
 *
 */

bool queue_is_empty(queue q);
/*
 * DESC: Indicates whether the queue 'q' is empty or not
 *
 */

bool queue_is_full(queue q);
/*
 * DESC: Indicates whether the queue 'q' is full or not
 *
 */

size_t queue_size(queue q);
/*
 * DESC: Return the number of elements inside the queue 'q'
 *
 */

queue_elem queue_first(queue q);
/*
 * DESC: Return the first element of the queue 'q'
 *
 * PRE: {q --> queue && !queue_is_empty(q)}
 *  e = queue_first(q);
 * POS: {q --> queue}
 */

queue queue_dequeue(queue q);
/*
 * DESC: Remove the first element of the queue 'q'
 *
 * PRE: {q --> queue && !queue_is_empty(q)}
 *  q = queue_dequeue(q);
 * POS: {q --> queue !queue_is_full(q)}
 *
 */

void queue_print(queue q);
/*
 * DESC: prints elements of q in queue order
 *       WARNING: this procedure cannot alter q elements. It's read only
 *
 * PRE: {q --> queue}
 *  queue_print(q);
 * POS: {q --> queue}
 *
 */

queue queue_destroy(queue q);
/*
 * DESC: Destroy instance of queue, freeing all memory used by 'q'.
 *
 * PRE: {q --> queue}
 *  q = queue_destroy(q);
 * POS: {q == NULL}
 *
 */

#endif
