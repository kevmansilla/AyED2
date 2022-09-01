#ifndef _CHANGE_MAKING_DYN_H_
#define _CHANGE_MAKING_DYN_H_

#include "../ej1/amount.h"
#include "currency.h"

/** Change-Making Dynamic
@param charge    A given price money to pay with coins
@param coins     An array of coin denominations
@param n_coins   The size of array `coins`

@return The minimun amount of coins needed for pay the charge

*/
amount_t change_making_dyn(currency_t charge, coin_t *coins, unsigned int n_coins);



#endif
