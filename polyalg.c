#ifndef POLYALG_C
#define POLYALG_C

#include <stdint.h>

uint8_t GF28_mult(uint8_t f, uint8_t g) {

    uint8_t result = 0;

    for (uint8_t n = 0; n < 8; n++) {
        if (g >> n & 1U){
            // If nth bit of g is set


            result ^= f << n;
        }
    }

    return result;
}

#endif