#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "polyalg.h"

_Bool test_GF28mult(void) {
    _Bool fail = 0;
    uint8_t out, exp;

    out = GF28_mult(0xAD, 1U);
    exp = 0xAD;
    if (out != exp) {
        fail = 1;
        printf("Failed multiplication in GF(2^8) test 0:\n");
        printf("Expected %x but got %x\n", exp, out);
    }

    out = GF28_mult(0xAD, 0x02);
    exp = 0x41;
    if (out != exp) {
        fail = 1;
        printf("Failed multiplication in GF(2^8) test 1:\n");
        printf("Expected %x but got %x\n", exp, out);
    }

    out = GF28_mult(0xAD, 0x04);
    exp = 0x82;
    if (out != exp) {
        fail = 1;
        printf("Failed multiplication in GF(2^8) test 2:\n");
        printf("Expected %x but got %x\n", exp, out);
    }

    out = GF28_mult(0xAD, 0x03);
    exp = 0xEC;
    if (out != exp) {
        fail = 1;
        printf("Failed multiplication in GF(2^8) test 3:\n");
        printf("Expected %x but got %x\n", exp, out);
    }

    out = GF28_mult(0xAD, 0x08);
    exp = 0x1F;
    if (out != exp) {
        fail = 1;
        printf("Failed multiplication in GF(2^8) test 4:\n");
        printf("Expected %x but got %x\n", exp, out);
    }

    out = GF28_mult(0b10011001U, 0b01010110U);
    exp = 0b01111111;
    if (out != exp) {
        fail = 1;
        printf("Failed multiplication in GF(2^8) test 10:\n");
        printf("Expected %x but got %x\n", exp, out);
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