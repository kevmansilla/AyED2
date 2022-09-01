#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct _queue_ *queue;
typedef struct _node_ *node;
typedef int T;

struct _queue_ {
    node last;
    node first;
};

struct _node_ {
    node before;
    T value;
    node after;
};  


queue empty_queue(void){
    queue cola;
    cola = malloc(sizeof(struct _queue_));
    cola->first = NULL;
    cola->last = NULL;
    return cola; 
}

queue enqueue(queue cola, T elem){
    node new_node;
    new_node = malloc(sizeof(struct _node_));
    new_node->value = elem;
    new_node->before = NULL;

    //Primer nodo
    if (cola->first == NULL && cola->last == NULL){    
        new_node->after = NULL;
        cola->first = new_node;
        cola->last = new_node;
            
    }
    
    ////Al menos un nodo
    else{
        cola->last->before = new_node;
        new_node->after = cola->last;
        cola->last = new_node;
    }
    return cola;
}

bool is_empty(queue cola){
    return (cola->first == NULL && cola->last == NULL);
}

T first(queue cola){
    return cola->first->value;
}

queue dequeue(queue cola){

    if (cola->first != NULL && cola->last != NULL){
        node old = cola->first;

        if (cola->first->before == NULL){
            cola->last = NULL;
        }

        cola->first = cola->first->before;
        free(old);
    }
    return cola;
}

queue destry_queue(queue cola){
    node aux,aux2;
    aux = cola->first;
    while(aux != NULL){
        aux2 = aux;
        aux = aux->before;
        free(aux2);
    }    
    free(cola);
    return cola;
}



#include <stdio.h>
void print_que(queue cola){
    node aux;
    int contador = 1;
    aux = cola->first;
    while(aux != NULL){
        printf("Itercion %d, elemento %d \n",contador,aux->value);
        aux = aux->before;
        contador = contador + 1;
    }
    printf("--------------------- \n");
}


int main(void){
    
    queue q = empty_queue();

    q = enqueue(q,1);
    print_que(q);
    
    q = enqueue(q,2);
    print_que(q);

    printf("es empty?: %d \n", is_empty(q));
    
    printf("Primer elemento %d\n",first(q));

    q = dequeue(q);
    print_que(q);

    q = destry_queue(q);
    return 0;
}
