#ifndef _SOLVE_KNAPSACK_H_
#define _SOLVE_KNAPSACK_H_

#include "knapsack.h"
#include "set.h"

/** Knapsack problem, Backtracking Algorithm
@param items    A given price money to pay with coins
@param coins     A set of coin denominations

@return The minimun amount of coins needed for pay the charge
*/

/** Knapsack Problem solved with Backtracking
@param items Available items
@param k The knapsack where the items that maximize value will be placed
@return A knapsack with the optimal solution
**/
knapsack solve_knapsack(set items, knapsack k);

#endif

