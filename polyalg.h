#ifndef POLYALG_H
#define POLYALG_H

#include <stdint.h>
#include "polyalg.c"

// Multiplies two polynomials in GF(2^8)
// Returns the product as a byte where MSB is the coefficient of x^7
uint8_t GF28_mult(uint8_t f, uint8_t g);

// Returns the congruence class of n in Z_[modulo] arithmetic
int64_t poly_concl(int64_t n, int64_t modulo);

// Converts the coefficients of polynomial [p] to the respective residues
// in Z_[modulo] arithmetic.
void poly_mod(int64_t p[], int64_t modulo, size_t max_ord);

// Returns the order of the highest non-zero term from x^0 to x^[order],
// inclusively. Returns -1 if all coefficients are 0.
int64_t poly_order(int64_t p[], size_t max_ord);

// Returns the leading coefficient of [p] up to the order of [max_ord].
// Returns 0 if all coefficients are 0.
int64_t poly_leadc(int64_t p[], size_t max_ord);

// Returns the multiplicative inverse of [x] modulo [mod] if [x] and [mod]
// are coprime. If x and mod are not coprime, then it returns negative GCD
// of the two.
int64_t poly_mult_inv(int64_t x, int64_t mod);

// Adds two polynomials [dest] and [add] modulo [mod]; the result is stored
// in [dest]. [order] specifies up to which order the addition must happen. 
// There will be [order]+1 additions in total, so both [dest] and [add] should
// be at least that large.
uint8_t poly_add(int64_t dest[], int64_t add[], size_t max_ord, int64_t mod);

#endif
