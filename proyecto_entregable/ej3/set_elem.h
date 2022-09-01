#ifndef _SET_ELEM_H
#define _SET_ELEM_H

#include "item.h"

/* Type for elements */
typedef item_t set_elem;

bool set_elem_eq(set_elem e1, set_elem e2);

set_elem set_elem_clone(set_elem elem);

void set_elem_dump(set_elem elem);

set_elem set_elem_destroy(set_elem elem);

#endif
