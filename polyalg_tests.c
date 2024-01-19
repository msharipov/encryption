#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "polyalg.h"

_Bool test_GF28mult(void) {
    _Bool fail = 0;
    uint64_t out, exp;

    out = GF28_mult(0b10011001U, 0b01010110U);
    exp = 0b01111111;
    if (out != exp) {
        fail = 1;
        printf("Failed multiplication in GF(2^8) test 0:\n");
        printf("Expected %lx but got %lx\n", exp, out);
    }

    return fail;
}

int main (void) {

    _Bool fail = 0;

    fail += test_GF28mult();

    if (!fail) {
        printf("\x1b[32mAll tests passed successfully!\x1b[0m\n");
    }
    exit(EXIT_SUCCESS);
}