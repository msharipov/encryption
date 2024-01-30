#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../polyalg.h"

void print_array(int64_t a[], size_t n) {
    if (n > 1) {
        for (size_t i = 0; i < n - 1; i++) {
            printf("%li, ", a[i]);
        }
    }
    printf("%li\n", a[n-1]);    
}

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
    exp = 0;
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
    out = poly_same(a0, a0, 5);
    exp = 1;
    if (out != exp) {
        fail = 1;
        printf("Failed poly_same test 0:\n");
        printf("Expected %li but got %li\n", exp, out);
    }

    int64_t a1[8] = {5, 3, -7, 1, 3, 2, 5, -11};
    out = poly_same(a0, a1, 5);
    exp = 1;
    if (out != exp) {
        fail = 1;
        printf("Failed poly_same test 1:\n");
        printf("Expected %li but got %li\n", exp, out);
    }

    int64_t a2[5] = {1, 2, 3, 4, 5};
    out = poly_same(a0, a2, 4);
    exp = 0;
    if (out != exp) {
        fail = 1;
        printf("Failed poly_same test 2:\n");
        printf("Expected %li but got %li\n", exp, out);
    }

    return fail;
}

_Bool test_poly_copy(void) {
    _Bool fail = 0;

    int64_t a0[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9},
            b0[9] = {0, 1, 2, 0, 1, 2, 0, 1, 2},
            exp0[9] = {0, 1, 2, 0, 1, 2, 0, 1, 2};

    poly_copy(a0, b0, 8);
    if (!poly_same(a0, exp0, 8)) {
        fail = 1;
        printf("Failed poly_copy test 0.\n");
    }

    int64_t a1[9] = {0},
            b1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9},
            exp1[9] = {1, 2, 3, 4, 5, 0, 0, 0, 0};

    poly_copy(a1, b1, 4);
    if (!poly_same(a1, exp1, 8)) {
        fail = 1;
        printf("Failed poly_copy test 1.\n");
    }

    return fail;
}

_Bool test_poly_mod(void) {
    _Bool fail = 0;

    int64_t a0[9] = {-3, -2, -1, 0, 1, 2, 3, 4, 5},
            exp0[9] = {1, 2, 3, 0, 1, 2, 3, 0, 1};

    poly_mod(a0, 4, 8);
    if (!poly_same(a0, exp0, 8)) {
        fail = 1;
        printf("Failed poly_mod test 0.\n");
    }

    int64_t a1[7] = {5, 6, 1, 2, -3, 0, 4},
            exp1[7] = {0};

    poly_mod(a1, 1, 6);
    if (!poly_same(a1, exp1, 6)) {
        fail = 1;
        printf("Failed poly_mod test 1.\n");
    }

    int64_t a2[5] = {2, 2, 2, 2, 2},
            exp2[5] = {0, 0, 0, 2, 2};

    poly_mod(a2, 2, 2);
    if (!poly_same(a2, exp2, 2)) {
        fail = 1;
        printf("Failed poly_mod test 2.\n");
    }

    return fail;
}

_Bool test_poly_add(void) {
    _Bool fail = 0;

    int64_t a0[6] = {5, 3, -7, 1, 3, 2},
            b0[6] = {0},
            exp0[6] = {5, 3, -7, 1, 3, 2};

    poly_add(a0, b0, 5);
    if (!poly_same(a0, exp0, 5)) {
        fail = 1;
        printf("Failed poly_add test 0.\n");
    }

    int64_t a1[6] = {0},
            b1[6] = {5, 3, -7, 1, 3, 2},
            exp1[6] = {5, 3, -7, 1, 3, 2};
            
    poly_add(a1, b1, 5);
    if (!poly_same(a1, exp1, 5)) {
        fail = 1;
        printf("Failed poly_add test 1.\n");
    }

    int64_t a2[6] = {1, 2, 3, 4, 5, 6},
            b2[6] = {-1, -2, -3, -4, -5, -6},
            exp2[6] = {0};
            
    poly_add(a2, b2, 5);
    if (!poly_same(a2, exp2, 5)) {
        fail = 1;
        printf("Failed poly_add test 2.\n");
    }

    int64_t a3[6] = {1, 2, 3, 4, 5, 6},
            b3[6] = {-1, -2, -3, -4, -5, -6},
            exp3[6] = {0, 0, 0, 4, 5, 6};
            
    poly_add(a3, b3, 2);
    if (!poly_same(a3, exp3, 5)) {
        fail = 1;
        printf("Failed poly_add test 3.\n");
    }

    return fail;
}

_Bool test_poly_add_mult(void) {
    _Bool fail = 0;

    int64_t a0[6] = {1, 1, 1, 1, 1, 1},
            b0[6] = {1, 2, 3, 4, 5, 6},
            exp0[6] = {4, 7, 10, 13, 16, 19};

    poly_add_mult(a0, b0, 3, 5);
    if (!poly_same(a0, exp0, 5)) {
        fail = 1;
        printf("Failed poly_add_mult test 0.\n");
    }

    int64_t a1[7] = {3, 4, 5, 1, -4, 2, -8},
            b1[7] = {1, 2, 3, 4, 5, 6, 7},
            exp1[7] = {3, 4, 5, 1, -4, 2, -8};

    poly_add_mult(a1, b1, 0, 6);
    if (!poly_same(a1, exp1, 6)) {
        fail = 1;
        printf("Failed poly_add_mult test 1.\n");
    }

    int64_t a2[7] = {3, 4, 5, 1, -4, 2, -8},
            b2[7] = {3, 4, 5, 1, -4, 2, -8},
            exp2[7] = {0};

    poly_add_mult(a2, b2, -1, 6);
    if (!poly_same(a2, exp2, 6)) {
        fail = 1;
        printf("Failed poly_add_mult test 2.\n");
    }

    return fail;
}

_Bool test_poly_mult(void) {
    _Bool fail = 0;

    int64_t a0[8] = {0, 1, 2, 3, 4, 5, 6, 7},
            b0[8] = {0},
            c0[15] = {0},
            exp0[15] = {0};

    poly_mult(c0, a0, b0, 7);
    if (!poly_same(c0, exp0, 14)) {
        fail = 1;
        printf("Failed poly_mult test 0.\n");
        printf("out: "), print_array(a0, 15);
        printf("exp: "), print_array(exp0, 15);
    }

    int64_t a1[8] = {0},
            b1[8] = {0, 1, 2, 3, 4, 5, 6, 7},
            c1[15] = {0},
            exp1[15] = {0};

    poly_mult(c1, a1, b1, 7);
    if (!poly_same(c1, exp1, 14)) {
        fail = 1;
        printf("Failed poly_mult test 1.\n");
        printf("out: "), print_array(c1, 15);
        printf("exp: "), print_array(exp1, 15);
    }

    int64_t a2[8] = {3, -2, 0, 4},
            b2[8] = {1, 0, -2},
            c2[15] = {0},
            exp2[15] = {3, -2, -6, 8, 0, -8};

    poly_mult(c2, a2, b2, 7);
    if (!poly_same(c2, exp2, 14)) {
        fail = 1;
        printf("Failed poly_mult test 2.\n");
        printf("out: "), print_array(c2, 15);
        printf("exp: "), print_array(exp2, 15);
    }

    return fail;
}

_Bool test_poly_add_ord(void) {
    _Bool fail = 0;

    int64_t a0[7] = {2, 4, -2, 3, 0, 0, 0},
            exp0[7] = {0, 0, 2, 4, -2, 3, 0};

    poly_add_ord(a0, 2, 6);
    if (!poly_same(a0, exp0, 6)) {
        fail = 1;
        printf("Failed poly_add_ord test 0.\n");
    }

    int64_t a1[7] = {1, 2, 3, 4, 5, 6, 7},
            exp1[7] = {1, 2, 3, 4, 5, 6, 7};

    poly_add_ord(a1, 0, 6);
    if (!poly_same(a1, exp1, 6)) {
        fail = 1;
        printf("Failed poly_add_ord test 1.\n");
    }

    int64_t a2[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9},
            exp2[9] = {0, 0, 1, 2, 3, 4, 5, 8, 9};

    poly_add_ord(a2, 2, 6);
    if (!poly_same(a2, exp2, 8)) {
        fail = 1;
        printf("Failed poly_add_ord test 2.\n");
    }

    return fail;
}

_Bool test_poly_GFrem(void) {
    _Bool fail = 0;

    int64_t a0[5] = {1, 2, 3, 4, 5},
            b0[5] = {1, 2, 3, 4, 5},
            exp0[5] = {0};

    poly_GFrem(a0, b0, 11, 4);
    if (!poly_same(a0, exp0, 4)) {
        fail = 1;
        printf("Failed poly_GFrem test 0.\n");
    }

    int64_t a1[5] = {2, 2, 0, 2, 2},
            b1[5] = {1, 1, 0, 0, 0},
            exp1[5] = {0};

    poly_GFrem(a1, b1, 5, 4);
    if (!poly_same(a1, exp1, 4)) {
        fail = 1;
        printf("Failed poly_GFrem test 1.\n");
    }

    int64_t a2[7] = {6, 0, 1, 5, 3, 0, 5},
            b2[7] = {1, 1, 3},
            exp2[7] = {0, 1};

    poly_GFrem(a2, b2, 7, 6);
    if (!poly_same(a2, exp2, 6)) {
        fail = 1;
        printf("Failed poly_GFrem test 2.\n");
    }

    int64_t a3[16] = {0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1},
            b3[16] = {1, 1, 0, 1, 1, 0, 0, 0, 1},
            exp3[16] = {1, 1, 1, 1, 1, 1, 1};

    poly_GFrem(a3, b3, 2, 15);
    if (!poly_same(a3, exp3, 7)) {
        fail = 1;
        printf("Failed poly_GFrem test 3.\n");
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
    fail += test_poly_copy();
    fail += test_poly_mod();
    fail += test_poly_add();
    fail += test_poly_add_mult();
    fail += test_poly_mult();
    fail += test_poly_add_ord();
    fail += test_poly_GFrem();

    if (!fail) {
        printf("\x1b[32mAll tests passed successfully!\x1b[0m\n");
    }
    exit(EXIT_SUCCESS);
}