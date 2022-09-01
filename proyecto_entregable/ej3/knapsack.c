#include <stdlib.h>
#include <assert.h>
#include "item.h"
#include "knapsack.h"
#include "set.h"

struct _s_knap {
    set packed_items;
    unsigned int capacity;
    unsigned int weight;
    unsigned int value;
};

static bool invrep(knapsack k) {
    return (knapsack_capacity(k)>0);
}

knapsack knapsack_empty(unsigned int capacity) {
    knapsack new = calloc(1, sizeof(struct _s_knap));
    new->capacity = capacity;
    new->weight = 0;
    new->value = 0;
    return new;
}

knapsack knapsack_clone(knapsack k) {
    invrep(k);
    knapsack copy = calloc(1, sizeof(struct _s_knap));
    copy->packed_items = k->packed_items;
    copy->capacity = k->capacity;
    copy->weight = knapsack_weight(k);
    copy->value = knapsack_value(k);
    return copy;
}

knapsack knapsack_pack(knapsack k, item_t item) {
    knapsack new = calloc(1, sizeof(struct _s_knap));
    new->capacity = k->capacity;
    new->weight = item_weight(item);
    new->value = item_value(item);
    return new;
}

bool knapsack_greater_value(knapsack k1, knapsack k2) {
    return knapsack_value(k1) > knapsack_value(k2);
}

bool knapsack_is_full(knapsack k) {
    return knapsack_weight(k) == k->capacity;
}

bool knapsack_can_hold(knapsack k, item_t item) {
    bool res = true;
    weight_t cap = knapsack_capacity(k) - knapsack_weight(k);
    if (cap < item_weight(item)){
        res = true;
    } else {
        res = false;
    }
    return res;
}

weight_t knapsack_capacity(knapsack k) {
    weight_t res = k->capacity - knapsack_weight(k);
    return res;
}

weight_t knapsack_weight(knapsack k) {
    weight_t res = 0;
    set items_copy = set_clone(k->packed_items);
    item_t item;
    weight_t w_item;
    while (!set_is_empty(items_copy)){
        item = set_get(items_copy);
        w_item = item_weight(item);
        res = res + w_item;
        items_copy = set_elim(items_copy, item);
    }
    items_copy = set_destroy(items_copy);
    return res;
}

value_t knapsack_value(knapsack k) {
    value_t res = 0;
    set items_copy = set_clone(k->packed_items);
    item_t item;
    value_t v_item;
    while (!set_is_empty(items_copy)){
        item = set_get(items_copy);
        v_item = item_value(item);
        res = res + v_item;
        items_copy = set_elim(items_copy, item);
    }
    items_copy = set_destroy(items_copy);
    return res;
}

void knapsack_dump(knapsack k) {
    weight_t capacity, remind;
    assert(invrep(k));
    capacity = knapsack_capacity(k);
    remind = capacity - knapsack_weight(k);
    printf("knapsack value   : $%u\n", knapsack_value(k));
    printf("knapsack capacity: %u\n", capacity);
    printf("knapsack remind  : %u\n", remind);
    printf("**** packed items ****\n");
    set_dump(k->packed_items);
}

knapsack knapsack_destroy(knapsack k) {
    free(k);
    k = NULL;
    return k;
}
