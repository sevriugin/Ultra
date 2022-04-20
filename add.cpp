#include <stdexcept>
#include "add.h"

using namespace std;

/**
 *
 * Calculate bitwise sum of two integer number, detecting `Overflow` and `Underflow`
 * @param {int64_t} a
 * @param {int64_t} b
 * @returns {int64_t} sum of two arguments or throw an exception
 *
 * */
int64_t add(int64_t a, int64_t b) {
    int64_t bitA;           // the current bit of number `a` ...
    int64_t bitB;           //  and `b`

    int64_t sum  { 0L };    // result of the function
    int64_t mask { 1L };    // mask for extracting bits
    int64_t over { 0L };    // carry over bit (c-out/c-in)

    /**
     * we are doing `sizeof(int64_t) * 8 - 1` steps here to
     *  process MSB of the result outside of the main loop
     *  where we can detect `Overflow` or `Underflow`
     */
    for ( int i = 0; i < sizeof(int64_t) * 8 - 1; i++ ) {
        /** select current bit using mask */
        bitA = a & mask;
        bitB = b & mask;
        /** calculate XOR for bits and carry over bit */
        sum |= bitA ^ bitB ^ over;
        /** calculate carry over bit for the next step */
        over = (bitA & bitB) | ((bitA ^ bitB) & over);
        /** shift mask and over for next step */
        over <<= 1;
        mask <<= 1;
    }
    /** Process MSB and check `Overflow` or `Underflow` */
    bitA = a & mask;
    bitB = b & mask;
    sum |= bitA ^ bitB ^ over;
    /** calculate carry over for MSB */
    int64_t c_out {(bitA & bitB) | ((bitA ^ bitB) & over)};

    /**
     * Check `Overflow` or `Underflow`
     *  if c_out != c_in (over) we have overflow condition and it's possible if bitA == bitB (0 | 1)
     *      if bitA == bitB == 0 and c_out != c_in -> `Overflow`
     *      if bitA == bitB == 1 and c_out != c_in -> `Underflow`
     * */
    if(c_out != over) {
        if (bitA == 0) {
            throw runtime_error("Overflow");
        } else {
            throw runtime_error("Underflow");
        }
    }

    return sum;
}


