//
// Created by cb106 on 1/25/2021.
//

#ifndef FNAF_ADVANCE_UTIL_H
#define FNAF_ADVANCE_UTIL_H

#include "tonc.h"

//https://stackoverflow.com/a/7919546/12861567
//generates a number such as 0b11111 where the number of 1s equals n
#define GET_N_SET_BITS(n) (1U << n) - 1U

/**
 * Returns the modulo of the given number such that negative numbers indicate that number of steps from the origin (0),
 * rather than however C (and Java) normally handle them. <br/> <br/>
 * <pre>
 * Example: <br/>
 *  Standard: <br/>
 *  .  &nbsp x =   -5  -4  -3  -2  -1   0   1   2   3   4   5    <br/>
 * .       &#60;<---|---|---|---|---|---0---|---|---|---|---|---> <br/>
 *  .&nbsp x % 4 = -1   0  -3  -2  -1   0   1   2   3   0   1  <br/>
 *                  (Results are mirrored at 0, where the abs of the results increases in both directions) <br/> <br/>
 *  This version: <br/>
 *  . &nbsp x =   -5  -4  -3  -2  -1   0   1   2   3   4   5    <br/>
 * .      &#60;<---|---|---|---|---|---0---|---|---|---|---|---> <br/>
 *  .&nbsp x % 4 = 3   0   1   2   3   0   1   2   3   0   1  <br/>
 *                  (There is one continuous cycle which repeats across the whole number line)
 *</pre>
 * @param number the number to perform the operation on
 * @param modulus  the modulus (second number in standard modulo notation)
 * @return the resulting value (see above)
 */
INLINE int continuous_modulo(int number, int modulus) {
    //Calculates a corrected value (left of outside %),
    //then returns the modulo of that value.
    return (modulus + (number % modulus)) % modulus;
}

//TODO: could return a single bit
INLINE int is_multiple(int number, int factor) {
    return number % factor == 0;
}

INLINE bool any(bool *bools, int boolc) {
    for (int i = 0; i < boolc; i++) {
        if (bools[i]) {
            return true;
        }
    }
    return false;
}

INLINE bool all(bool *bools, int boolc) {
    for (int i = 0; i < boolc; i++) {
        if (~bools[i]) {
            return false;
        }
    }
    return true;
}

#endif //FNAF_ADVANCE_UTIL_H
