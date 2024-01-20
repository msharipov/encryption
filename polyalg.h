#ifndef POLYALG_H
#define POLYALG_H

#include <stdint.h>
#include "polyalg.c"

// Multiplies two polynomials in GF(2^8)
// Returns the product as a byte where MSB is the coefficient of x^7
uint8_t GF28_mult(uint8_t f, uint8_t g);

// Adds two polynomials [dest] and [add] modulo m(x); the result is stored
// in [dest]. [order] specifies up to which order the addition must happen. 
// There will be [order]+1 additions in total, so both [dest] and [add] should
// be at least that large. 
void poly_add(uint64_t dest[], uint64_t add[], size_t order, uint64_t m[]);

#endif