#ifndef POLYALG_C
#define POLYALG_C

#include <stdint.h>

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

#endif