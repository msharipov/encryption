#ifndef POLYALG_H
#define POLYALG_H

#include <stdint.h>
#include "polyalg.c"

// Multiplies two polynomials in GF(2^8)
// Returns the product as a byte where MSB is the coefficient of x^7
uint8_t GF28_mult(uint8_t f, uint8_t g);

// Returns the congruence class of n in Z_[modulo] arithmetic
int64_t poly_concl(int64_t n, int64_t modulo);

// Returns the order of the highest non-zero term from x^0 to x^[order],
// inclusively. Returns -1 if all coefficients are 0.
int64_t poly_order(int64_t p[], size_t max_ord);

// Returns the leading coefficient of [p] up to the order of [max_ord].
// Returns 0 if all coefficients are 0.
int64_t poly_leadc(int64_t p[], size_t max_ord);

// Adds two polynomials [dest] and [add] modulo m(x); the result is stored
// in [dest]. [order] specifies up to which order the addition must happen. 
// There will be [order]+1 additions in total, so both [dest] and [add] should
// be at least that large. The size of [m] should also be at most [order]+1.
// returns:
// 0 - normal completion
// 1 - division by zero error
uint8_t poly_add(int64_t dest[], int64_t add[], 
                 size_t max_ord, int64_t m[]);

#endif
