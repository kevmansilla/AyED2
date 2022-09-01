#include <stdlib.h>
#include <stdio.h>
#include "sorted_list.h"
#include "sort.h"

void sort(int a[], unsigned int length) {

    sorted_list_t list = sorted_list_empty();

    unsigned int index = 0U;
    while (index < length) {
        list = sorted_list_append(list, a[index]);
        index++;
    }
    
    index = 0U;
    while (index < length) {
        a[index] = sorted_list_elem_at(list, index);
        index++;
    }

    sorted_list_destroy(list);

}
