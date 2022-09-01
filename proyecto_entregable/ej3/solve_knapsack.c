#include "knapsack.h"
#include "set.h"

knapsack solve_knapsack(set items, knapsack k) {
    if (!set_is_empty(items) && !knapsack_is_full(k)) {
        item_t item = set_get(items);
        set items_without=set_elim(set_clone(items), item);
        if (!knapsack_can_hold(k, item)) {
            k = solve_knapsack(items_without, k);
        } else {
            /* Knapsack with extra item */
            knapsack solved_with=knapsack_clone(k);
            solved_with = knapsack_pack(solved_with, item_clone(item));
            /* Solution ussing item */
            solved_with = solve_knapsack(items_without, solved_with);
            /* Solution disscarding item */
            knapsack solved_without=knapsack_clone(k);
            solved_without = solve_knapsack(items_without, solved_without);
            /* Take the solution with better costs */
            k = knapsack_destroy(k);
            if (knapsack_greater_value(solved_with, solved_without)) {
                k = solved_with;
                solved_without = knapsack_destroy(solved_without);
            } else {
                k = solved_without;
                solved_with = knapsack_destroy(solved_with);
            }
        }
        items_without = set_destroy(items_without);
    }
    return k;
}
