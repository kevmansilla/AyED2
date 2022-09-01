#ifndef _CURRENCY_H_
#define _CURRENCY_H_

/**
Type for amount of money
*/
typedef unsigned int currency_t;

/**
Coin denominations
*/
typedef currency_t coin_t;

/** Show a coin on the screen
@param c A given coin
*/
void coin_dump(coin_t c);

#endif

