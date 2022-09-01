#ifndef _AMOUNT_H_
#define _AMOUNT_H_

#include <stdbool.h>

/* TODO: COMPLETAR: Definir el tipo */
typedef unsigned int amount_t;

/**
Returns an infinite amount of coins
*/
amount_t amount_inf();

/** Checks if the amount of coins `a` is infinite
@param amount
@return true if amount is infinite, false otherwise
*/
bool amount_is_inf(amount_t a);

/** Amount Less or Equal relation
@param a1 first amount
@param a2 second amount
*/
bool amount_le(amount_t a1, amount_t a2);

/** Amount Less Than (strictly) relation
@param a1 first amount
@param a2 second amount
*/
bool amount_lt(amount_t a1, amount_t a2);

/** Amount Sum (addition) operation
@param a1 first amount
@param a2 second amount
*/
amount_t amount_sum(amount_t a1, amount_t a2);

/** Prints a amount in stdout
@param amount
*/
void amount_dump(amount_t amount);

#endif
