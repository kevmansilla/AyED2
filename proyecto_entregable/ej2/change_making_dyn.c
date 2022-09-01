#include <stdlib.h>
#include <stdio.h>
#include "currency.h"
#include "../ej1/amount.h"

/** minimum between two elements of type amount_t
@param am1 first amount
@param am2 second amount
@return res is the minimum of the two parameters
*/
static amount_t min(amount_t am1, amount_t am2){
    amount_t res;
    if (amount_le(am1, am2)){
        res = am1;
    } else {
        res = am2;
    }
    return res;
}

/** Change-Making Dynamic
@param charge    A given price money to pay with coins
@param coins     An array of coin denominations

@return The minimun amount of coins needed for pay the charge
*/
amount_t change_making_dyn(currency_t charge, coin_t *coins, unsigned int n_coins){
    //amount_t aux;
    amount_t res;
    //create table (array[0..n,0..k])
    amount_t **table = calloc(n_coins + 1u, sizeof(amount_t*));
    for (unsigned int i = 0u; i <= n_coins; ++i){
        table[i] = calloc(charge + 1u, sizeof(amount_t));
    }
    //complete the table
    for (unsigned int i = 0u; i <= n_coins; ++i){
        table[i][0u] = 0u;
    }
    for (unsigned int j = 1u; j <= charge; ++j){
        table[0u][j] = amount_inf();
    }
    //complete missing rows and columns
    for (unsigned int i = 1u; i <= n_coins; ++i){
        for (unsigned int j = 1u; j <= charge; ++j){
            if (coins[i - 1u] > j){
                table[i][j] = table[i - 1u][j];
            } else {
                table[i][j] = min(table[i - 1u][j], amount_sum(1u, table[i][j - coins[i - 1]]));
            }
        }
    }
    res = table[n_coins][charge]; //main function call
    //release table
    for (unsigned int i = 0u; i <= n_coins; ++i){
        free(table[i]);
        table[i] = NULL;
    }
    free(table);
    table = NULL;
    return res;
}
