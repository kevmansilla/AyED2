#include <assert.h>
#include <stddef.h>
#include "change_making.h"
#include "amount.h"
#include "set.h"
#include <stdio.h>
#include "currency.h"

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

/** Change-Making Algorithm
@param charge    A given price money to pay with coins
@param coins     A set of coin denominations

@return The minimun amount of coins needed for pay the charge
*/
amount_t change_making(currency_t charge, set coins){
    set_elem c;
    set C_aux;
    amount_t res;
    if (charge == 0u){
        res = 0u;   //base case
    } else if (set_is_empty(coins)){
        res = amount_inf();  //base case where there are no coins
    } else {  //recursive case
        C_aux = set_clone(coins);
        c = set_get(coins);
        C_aux = set_elim(C_aux, c);
        if (amount_le(c, charge)){
            res = min(amount_sum(1u, change_making(charge - c, coins)), change_making(charge, C_aux));
        } else {
            res = change_making(charge, C_aux);
        }
        C_aux = set_destroy(C_aux);
        C_aux = NULL;
    }
    return res;
}
