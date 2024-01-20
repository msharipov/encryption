#ifndef POLYALG_C
#define POLYALG_C

#include <stdint.h>
#include <assert.h>

uint8_t GF28_mult(uint8_t f, uint8_t g) {

    uint8_t result = 0,
            fxn = f; // fxn = f * x^n

    for (uint8_t n = 0; n < 8; n++) {

        // If nth bit of g is set add nth power of f
        if (g >> n & 1U) {
            result ^= fxn;
        }

        // Multiply fxn by x
        fxn = fxn << 1 ^ (fxn & 0x80 ? 0x1B : 0);

    }

    return result;
}


int64_t poly_order(int64_t p[], size_t max_ord) {

    for (size_t i = max_ord; i >= 0; i--) {
        if (p[i]) {
            return i;
        }
    }

    return -1;
}


int64_t poly_leadc(int64_t p[], size_t max_ord) {

    for (size_t i = max_ord; i > 0; i--) {
        if (p[i]) {
            return p[i];
        }
    }

    return p[0];
}


uint8_t poly_add(int64_t dest[], int64_t add[], 
                 size_t max_ord, int64_t m[]) {

    if (poly_order(m, max_ord) == -1) {
        return 1;
    }

    for (size_t i = 0; i <= max_ord; i++) {
        dest[i] += add[i];
    }

    size_t m_order = poly_order(m, max_ord);

    return 0;
}

int64_t poly_concl(int64_t n, int64_t modulo) {

    int64_t simple_mod = n % modulo;
    
    if (simple_mod > 0) {
        return n % modulo;
    } else {
        return (modulo + (n % modulo)) % modulo;
    }
}

#endif