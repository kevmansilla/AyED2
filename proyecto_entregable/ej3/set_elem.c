#include <stdio.h>
#include <stdbool.h>
#include "set_elem.h"
#include "item.h"
#include "string.h"

bool set_elem_eq(set_elem e1, set_elem e2) {
    return string_eq(item_id(e1), item_id(e2));
}

set_elem set_elem_clone(set_elem elem) {
    return item_clone(elem);
}

void set_elem_dump(set_elem elem) {
    printf("%s [$%u:%u]", string_ref(item_id(elem)),
                          item_value(elem),
                          item_weight(elem));
}

set_elem set_elem_destroy(set_elem elem) {
    return item_destroy(elem);
}

