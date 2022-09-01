#ifndef _KNAPSACK_H
#define _KNAPSACK_H

#include "item.h"

/**
* @brief Knapsack type definition
*/
typedef struct _s_knap * knapsack;

/**
* @brief Creates an empty knapsack that supports at most [capacity] weight
* @param capacity The max capacity for knapsack
* @return An empty knapsack
*/
knapsack knapsack_empty(unsigned int capacity);


/**
* @brief Makes a copy of a knapsack
* @param k The original knapsack to clone
* @return A new knapsack in new memory
*/
knapsack knapsack_clone(knapsack k);

/**
* @brief Packs an item in the knapsack
* @param k A knapsack
* @param item An object to insert into k
* @return the same knapsack with [item] inside
*
* @note PRE: {knapsack_can_hold(k, item)}
*
*/
knapsack knapsack_pack(knapsack k, item_t item);

/**
* @brief Indicates whether the items in knapsack [k1] add more valuethan those
*        in knapsack [k2]
* @param k1 A knapsack to check
* @param k2 A knapsack to check
* @return true if thea [k1] has more value than [k2]
*/
bool knapsack_greater_value(knapsack k1, knapsack k2);

/**
* @brief Indicates if ther is enough room for [item] in the knapsack
* @param k A knapsack
* @param item The item to check
* @return true if the sum of the weight of the items in knapsack [k] plus
*              weight of [item] does noet exceeds the capacity of [k]
*/
bool knapsack_can_hold(knapsack k, item_t item);

/**
* @brief Check if the given knapsack is full
* @param k A knapsack
* @return true if the weight of [k] equals his capacity
*/
bool knapsack_is_full(knapsack k);

/**
* @brief Returns the sum of values of the items that knaspack holds
* @param k A knapsack
* @return The total value that [k] holds
*/
value_t knapsack_value(knapsack k);

/**
* @brief Returns the sum of weights of the items that knaspack holds
* @param k A knapsack
* @return The total weight that [k] holds
*/
weight_t knapsack_weight(knapsack k);

/**
* @brief Returns the max capacity of weight that [k] supports
* @param k A knapsack
* @return The capacity of [k]
*/
weight_t knapsack_capacity(knapsack k);

/**
* @brief Show a knapsack in stdout
* @param k A knapsack
* @return The total value that [k] holds
*/
void knapsack_dump(knapsack k);

/**
* @brief Destroy knapsack and free all memory
* @param k A knapsack
* @return A NULL value
*/
knapsack knapsack_destroy(knapsack k);

#endif
