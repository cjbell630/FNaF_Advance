//
// Created by cb106 on 1/25/2021.
//

#ifndef FNAF_ADVANCE_UTIL_H
#define FNAF_ADVANCE_UTIL_H

#include "../../include/tonclib/tonc.h"


/**
 * [Documentation coped from my Java implementation of the same code]
 *
 * Calculates and returns the smallest number of positive steps equivalent to the given value
 * within the cyclic function (0 ... `range`).
 * <dl>
 * <dt>When the signs of both parameters are the same:</dt>
 * <dd>it returns the same values as `number % range`.</dd>
 * <dt>When the signs are different:</dt>
 * <dd>it essentially moves `number` in increments of `range` until it is within (0 ... `range`).</dd>
 * </dl>
 * Example: You are turning in a circle in increments of 90 degrees clockwise (to the right).
 * You turn 7 times to the left (represented as -7). What is the smallest number of right
 * turns you can make to face the same direction (assuming you start facing the same direction)?
 * logicallyCorrectModulus(-7, 4) = 1
 * <p>
 * Generally speaking, `range` should be positive, but changing the sign is the equivalent of changing the
 * "direction" of the resultant. Using the example above, `logicallyCorrectModulus(-7, -4)` would return
 * the smallest number of <i>left</i> turns equivalent to 7 left turns, expressed as a negative number: -3.
 * TODO: consider making it return an absolute value for this reason.
 *
 * @param number the number to perform the operation on
 * @param range  the maximum value (exclusive) for the number to be in (0 ... `range`)
 * @return the resulting value (see above)
 */
INLINE int logically_correct_modulus(int number, int range) {
    return (range + (number % range)) % range;
}

#endif //FNAF_ADVANCE_UTIL_H
