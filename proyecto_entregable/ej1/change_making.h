#ifndef _CHANGE_MAKING_H_
#define _CHANGE_MAKING_H_

#include "amount.h"
#include "currency.h"
#include "set.h"

/** Change-Making Algorithm
@param charge    A given price money to pay with coins
@param coins     A set of coin denominations

@return The minimun amount of coins needed for pay the charge
*/
amount_t change_making(currency_t charge, set coins);

#endif

