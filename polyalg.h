#ifndef POLYALG_H
#define POLYALG_H

#include <stdint.h>
#include "polyalg.c"

// Multiplies two polynomials in GF(2^8)
// Returns the product as a byte where MSB is the coefficient of x^7
uint8_t GF28_mult(const uint8_t f, const uint8_t g);

// Carries out long division of [f] by [g] in GF(2^8). The quotient is stored
// in [q] and the remainder in [r]. 
void GF28_longdiv(uint8_t * q, uint8_t * r, const uint8_t f, const uint8_t g);

// Carries out long division of [f] by [g] in GF(2^16). The quotient is stored
// in [q] and the remainder in [r].
void GF216_longdiv(uint16_t * q, uint16_t * r, const uint16_t f, 
                   const uint16_t g);

// Returns the multiplicative inverse of [p] in GF(2^8).
uint8_t GF28_inv(const uint8_t p);

// Returns the congruence class of n in Z_[modulo] arithmetic
int64_t poly_concl(const int64_t n, const int64_t modulo);

// Returns the multiplicative inverse of [x] modulo [mod] if [x] and [mod]
// are coprime. If x and mod are not coprime, then it returns negative GCD
// of the two.
int64_t poly_mult_inv(const int64_t x, const int64_t mod);

// Returns the order of the highest non-zero term from x^0 to x^[max_ord],
// inclusively. Returns 0 if all coefficients are 0.
size_t poly_order(const int64_t p[], const size_t max_ord);

// Returns the leading coefficient of [p] up to the order of [max_ord].
// Returns 0 if all coefficients are 0.
int64_t poly_leadc(const int64_t p[], const size_t max_ord);

// Compares two polynomials [a] and [b]. Returns true if all coefficients up
// to order [max_ord] match; returns false otherwise.
bool poly_same(const int64_t a[], const int64_t b[], const size_t max_ord);

// Compares two polynomials [a] and [b] over GF([mod]). Returns true if all
// coefficients up to order [max_ord] are congruent modulo [mod]; returns 
// false otherwise.
bool poly_GFsame(const int64_t a[], const int64_t b[], const int64_t mod, 
                 const size_t max_ord);

// Copies polynomial [p] into [dest] up to order [max_ord].
void poly_copy(int64_t dest[], const int64_t p[], const size_t max_ord);

// Converts the coefficients of polynomial [p] to the respective residues
// in Z_[modulo] arithmetic.
void poly_mod(int64_t p[], const int64_t modulo, const size_t max_ord);

// Adds two polynomials [dest] and [add]; the result is stored in [dest].
// [max_ord] specifies up to which order the addition must happen. There will
// be [max_ord]+1 additions in total, so both [dest] and [add] should be at 
// least that large.
void poly_add(int64_t dest[], const int64_t add[], const size_t max_ord);

// Adds [add] times [b] to [dest], similarly to poly_add.
void poly_add_mult(int64_t dest[], const int64_t add[], const int64_t b, 
                   const size_t max_ord);

// Multiplies the polynomial [p](x) by x^[power]. Requires that [power] >= 0 
// and that the size of [p] must be at least [max_ord]+[power]+1.
void poly_add_ord(int64_t p[], const size_t power, const size_t max_ord);

// Multiplies polynomials [a] and [b]. Result is stored in [dest], the size
// of which must be at least [max_ord]*2+1.
void poly_mult(int64_t dest[], const int64_t a[], const int64_t b[],
               const size_t max_ord);

// Changes [p] to be its own remainder from division by mod_p [mod_p] with
// coefficients in GF([mod]). [mod] has to be prime.
void poly_GFrem(int64_t p[], const int64_t mod_p[], const int64_t mod, 
                 const size_t max_ord);

// Divides polynomial [p] by [mod_p] over GF([mod]). The quotient is stored
// in [q] and the remainder - in [p]. [mod] has to be prime. Returns 0 if
// division was completed successfully; returns 1 if [mod_p] is 0; returns 2
// if [mod] is 0.
uint8_t poly_GFdiv(int64_t q[], int64_t p[], const int64_t mod_p[], 
                   const int64_t mod, const size_t max_ord);

// Computes the multiplicative inverse of [p] in the polynomial field over
// GF([mod]) modulo [mod_p]. [mod] has to be prime and [mod_p] has to be
// irreducible. If the inverse does not exist, all coefficients [p_inv] are
// set to 0.
void poly_GFinv(int64_t p_inv[], const int64_t p[], const int64_t mod_p[], 
                const int64_t mod, const size_t max_ord);

#endif
