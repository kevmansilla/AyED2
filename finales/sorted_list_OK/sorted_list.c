#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "sorted_list.h"
// #include "list.h"

struct s_node {
    struct s_node * next;
    elem_t elem;
};

struct s_node * create_node(elem_t e) {
    struct s_node * res = calloc(1, sizeof(struct s_node));
    res->next = NULL;
    res->elem = e;
    return res;
}

sorted_list_t sorted_list_empty() {
    struct s_node * res = NULL;
    return res;
}

bool sorted_list_is_empty(sorted_list_t list) {
    return (list==NULL);
}

elem_t sorted_list_head(sorted_list_t list) {
    return list->elem;
}

sorted_list_t sorted_list_tail(sorted_list_t list) {
    struct s_node * tmp = list->next;
    free(list);
    return tmp;
}

unsigned int sorted_list_length(sorted_list_t list) {
    unsigned int length = 0;
    struct s_node * tmp = list;
    while (tmp!=NULL) {
        length++;
        tmp = tmp->next;
    }
    return length;
}

elem_t sorted_list_elem_at(sorted_list_t list, unsigned int index) {
    unsigned int skipped = 0;
    struct s_node * tmp = list;
    while (skipped < index) {
        skipped++;
        tmp = tmp->next;
    }
    return tmp->elem;
}

sorted_list_t sorted_list_destroy(sorted_list_t list) {
    struct s_node * tmp;
    while (list!=NULL) {
        tmp = list->next;
        free(list);
        list = tmp;
    }
    free(list);
    list = NULL;
    return list;
}

void sorted_list_print(sorted_list_t list) {
    struct s_node * tmp = list;
    while (tmp != NULL) {
        printf("%d ", tmp->elem);
        tmp = tmp->next;
    }
}

sorted_list_t sorted_list_take(sorted_list_t list, unsigned int num) {
    // take 3 [1,2,3,4,5,6,7] = [1,2,3]
    if (list != NULL) {
        struct s_node * new_list = NULL;
        struct s_node * tmp = new_list;
        unsigned int taken = 0U;
        while (taken < num) {
            tmp = calloc(1, sizeof(struct s_node));
            tmp->elem = sorted_list_elem_at(list, taken);
            tmp->next = NULL;
            tmp = tmp->next;
            taken++;
        }
        return new_list;
    } else {
        return sorted_list_empty();
    }
}

sorted_list_t sorted_list_drop(sorted_list_t list, unsigned int num) {
    assert(num < sorted_list_length(list));
    struct s_node * new_list = NULL;
    struct s_node * tmp = new_list;
    unsigned int index = num;
    while (index < sorted_list_length(list)) {
        tmp = calloc(1, sizeof(struct s_node));
        tmp->elem = sorted_list_elem_at(list, index);
        tmp->next = NULL;
        tmp = tmp->next;
        index++;
    }
    return new_list;
}

sorted_list_t sorted_list_append(sorted_list_t list, elem_t elem) {
    struct s_node * new_node = create_node(elem);

    if (list != NULL) {
        struct s_node * left = NULL;
        struct s_node * current = list;

        while (current != NULL && current->elem <= elem) {
            left = current;
            current = current->next;
        }
        
        if (left == NULL) {
            new_node->next = current;
            return new_node;
        } else {
            left->next = new_node;
            new_node->next = current;
            return list;
        }
    } else {
        return new_node;
    }
}
