#ifndef POLYALG_H
#define POLYALG_H

#include <stdint.h>
#include "polyalg.c"

// Multiplies two polynomials in GF(2^8)
uint8_t GF28_mult(uint8_t f, uint8_t g);

#endif