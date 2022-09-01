#ifndef _MINI_SET_H_
#define _MINI_SET_H_

#include <stdbool.h>           /* Definition of bool      */
#include "set_elem.h"          /* Definition of set_elem */

typedef struct s_set *set;

/* CONSTRUCTORS */

set set_empty(void);

set set_add(set s, set_elem e);

/** Makes a copy of a given set in new memory
@param s  A set instance to clone
@return A new set instance
@note
 s_copy = set_clone(s)
 POS: {set_cardinal(s_copy) == set_cardinal(s)
       /\ (s_copy != s || set_is_empty(s))}
*/
set set_clone(set s);

/* OPERATIONS   */

unsigned int set_cardinal(set s);

bool set_is_empty(set s);

bool set_member(set_elem e, set s);

set set_elim(set s, set_elem e);

set_elem set_get(set s);

void set_dump(set s);

set set_destroy(set s);

#endif
