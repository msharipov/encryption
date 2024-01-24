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

_Bool test_poly_order(void) {
    _Bool fail = 0;
    int64_t out, exp;
    int64_t a[15]    = {-4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 0, 0, 0},
            empty[5] = {0};


    out = poly_order(a, 14);
    exp = 11;
    if (out != exp) {
        fail = 1;
        printf("Failed poly_order test 0:\n");
        printf("Expected %li but got %li\n", exp, out);
    }

    out = poly_order(a, 6);
    exp = 6;
    if (out != exp) {
        fail = 1;
        printf("Failed poly_order test 1:\n");
        printf("Expected %li but got %li\n", exp, out);
    }

    out = poly_order(a, 4);
    exp = 3;
    if (out != exp) {
        fail = 1;
        printf("Failed poly_order test 2:\n");
        printf("Expected %li but got %li\n", exp, out);
    }

    out = poly_order(empty, 4);
    exp = -1;
    if (out != exp) {
        fail = 1;
        printf("Failed poly_order test 3:\n");
        printf("Expected %li but got %li\n", exp, out);
    }

    return fail;
}

_Bool test_poly_leadc(void) {
    _Bool fail = 0;
    int64_t out, exp;
    int64_t a[15]    = {-4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 0, 0, 0},
            empty[5] = {0};

    out = poly_leadc(a, 14);
    exp = 7;
    if (out != exp) {
        fail = 1;
        printf("Failed poly_leadc test 0:\n");
        printf("Expected %li but got %li\n", exp, out);
    }

    out = poly_leadc(a, 9);
    exp = 5;
    if (out != exp) {
        fail = 1;
        printf("Failed poly_leadc test 1:\n");
        printf("Expected %li but got %li\n", exp, out);
    }

    out = poly_leadc(a, 4);
    exp = -1;
    if (out != exp) {
        fail = 1;
        printf("Failed poly_leadc test 2:\n");
        printf("Expected %li but got %li\n", exp, out);
    }

    out = poly_leadc(empty, 4);
    exp = 0;
    if (out != exp) {
        fail = 1;
        printf("Failed poly_leadc test 3:\n");
        printf("Expected %li but got %li\n", exp, out);
    }

    return fail;
}

_Bool test_poly_concl(void) {
    _Bool fail = 0;
    int64_t out, exp;

    out = poly_concl(15, 5);
    exp = 0;
    if (out != exp) {
        fail = 1;
        printf("Failed poly_concl test 0:\n");
        printf("Expected %li but got %li\n", exp, out);
    }

    out = poly_concl(12, 7);
    exp = 5;
    if (out != exp) {
        fail = 1;
        printf("Failed poly_concl test 1:\n");
        printf("Expected %li but got %li\n", exp, out);
    }

    out = poly_concl(6, 35);
    exp = 6;
    if (out != exp) {
        fail = 1;
        printf("Failed poly_concl test 2:\n");
        printf("Expected %li but got %li\n", exp, out);
    }

    out = poly_concl(0, 11);
    exp = 0;
    if (out != exp) {
        fail = 1;
        printf("Failed poly_concl test 3:\n");
        printf("Expected %li but got %li\n", exp, out);
    }

    out = poly_concl(-7, 5);
    exp = 3;
    if (out != exp) {
        fail = 1;
        printf("Failed poly_concl test 4:\n");
        printf("Expected %li but got %li\n", exp, out);
    }

    out = poly_concl(-18, 9);
    exp = 0;
    if (out != exp) {
        fail = 1;
        printf("Failed poly_concl test 5:\n");
        printf("Expected %li but got %li\n", exp, out);
    }

    return fail;
}

_Bool test_poly_mult_inv(void) {
    _Bool fail = 0;
    int64_t out, exp;

    out = poly_mult_inv(0, 7);
    exp = -7;
    if (out != exp) {
        fail = 1;
        printf("Failed poly_mult_inv test 0:\n");
        printf("Expected %li but got %li\n", exp, out);
    }

    out = poly_mult_inv(3, 6);
    exp = -3;
    if (out != exp) {
        fail = 1;
        printf("Failed poly_mult_inv test 1:\n");
        printf("Expected %li but got %li\n", exp, out);
    }

    out = poly_mult_inv(9, 5);
    exp = 4;
    if (out != exp) {
        fail = 1;
        printf("Failed poly_mult_inv test 2:\n");
        printf("Expected %li but got %li\n", exp, out);
    }

    out = poly_mult_inv(2, 7);
    exp = 4;
    if (out != exp) {
        fail = 1;
        printf("Failed poly_mult_inv test 3:\n");
        printf("Expected %li but got %li\n", exp, out);
    }

    out = poly_mult_inv(1, 8);
    exp = 1;
    if (out != exp) {
        fail = 1;
        printf("Failed poly_mult_inv test 4:\n");
        printf("Expected %li but got %li\n", exp, out);
    }

    out = poly_mult_inv(12, 12);
    exp = -12;
    if (out != exp) {
        fail = 1;
        printf("Failed poly_mult_inv test 5:\n");
        printf("Expected %li but got %li\n", exp, out);
    }

    return fail;
}

_Bool test_poly_same(void) {
    _Bool fail = 0;
    int64_t out, exp;

    int64_t a0[6] = {5, 3, -7, 1, 3, 2};
    out = poly_same(a0, a0, 6);
    exp = 1;
    if (out != exp) {
        fail = 1;
        printf("Failed poly_same test 0:\n");
        printf("Expected %li but got %li\n", exp, out);
    }

    return fail;
}

int main (void) {

    _Bool fail = 0;

    fail += test_GF28mult();
    fail += test_poly_order();
    fail += test_poly_leadc();
    fail += test_poly_concl();
    fail += test_poly_mult_inv();
    fail += test_poly_same();

    if (!fail) {
        printf("\x1b[32mAll tests passed successfully!\x1b[0m\n");
    }
    exit(EXIT_SUCCESS);
}