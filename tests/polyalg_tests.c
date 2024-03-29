#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <polyalg.h>
#include <stdbool.h>

void print_array(int64_t a[], size_t n) {

    if (n == 0) {
        printf("\n");
        return;
    }

    if (n > 1) {
        for (size_t i = 0; i < n - 1; i++) {
            printf("%li, ", a[i]);
        }
    }

    printf("%li\n", a[n-1]);    
}

_Bool test_GF28_mult(void) {
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

    out = GF28_mult(0x99U, 0x56U);
    exp = 0x7F;
    if (out != exp) {
        fail = 1;
        printf("Failed multiplication in GF(2^8) test 5:\n");
        printf("Expected %x but got %x\n", exp, out);
    }

    return fail;
}

_Bool test_GF28_longdiv(void) {
    _Bool fail = 0;
    uint8_t r, q, exp_r, exp_q;

    GF28_longdiv(&q, &r, 0xB7, 0x35);
    exp_q = 0x06;
    exp_r = 0x09;
    if (r != exp_r) {
        fail = 1;
        printf("Failed GF28_longdiv test 0:\n");
        printf("Expected r:%x but got %x\n", exp_r, r);
    }
    if (q != exp_q) {
        fail = 1;
        printf("Failed GF28_longdiv test 0:\n");
        printf("Expected q:%x but got %x\n", exp_q, q);
    }

    GF28_longdiv(&q, &r, 0x6D, 0x23);
    exp_q = 0x03;
    exp_r = 0x08;
    if (r != exp_r) {
        fail = 1;
        printf("Failed GF28_longdiv test 1:\n");
        printf("Expected r:%x but got %x\n", exp_r, r);
    }
    if (q != exp_q) {
        fail = 1;
        printf("Failed GF28_longdiv test 1:\n");
        printf("Expected q:%x but got %x\n", exp_q, q);
    }

    GF28_longdiv(&q, &r, 0x7B, 0x01);
    exp_q = 0x7B;
    exp_r = 0x00;
    if (r != exp_r) {
        fail = 1;
        printf("Failed GF28_longdiv test 2:\n");
        printf("Expected r:%x but got %x\n", exp_r, r);
    }
    if (q != exp_q) {
        fail = 1;
        printf("Failed GF28_longdiv test 2:\n");
        printf("Expected q:%x but got %x\n", exp_q, q);
    }

    GF28_longdiv(&q, &r, 0x4F, 0x4F);
    exp_q = 0x01;
    exp_r = 0x00;
    if (r != exp_r) {
        fail = 1;
        printf("Failed GF28_longdiv test 3:\n");
        printf("Expected r:%x but got %x\n", exp_r, r);
    }
    if (q != exp_q) {
        fail = 1;
        printf("Failed GF28_longdiv test 3:\n");
        printf("Expected q:%x but got %x\n", exp_q, q);
    }

    return fail;
}

_Bool test_GF216_longdiv(void) {

    _Bool fail = 0;
    uint16_t r, q, exp_r, exp_q;

    GF216_longdiv(&q, &r, 0x00B7, 0x0035);
    exp_q = 0x0006;
    exp_r = 0x0009;
    if (r != exp_r) {
        fail = 1;
        printf("Failed GF216_longdiv test 0:\n");
        printf("Expected r:%x but got %x\n", exp_r, r);
    }
    if (q != exp_q) {
        fail = 1;
        printf("Failed GF216_longdiv test 0:\n");
        printf("Expected q:%x but got %x\n", exp_q, q);
    }

    GF216_longdiv(&q, &r, 0xFFFF, 0xFFFF);
    exp_q = 0x0001;
    exp_r = 0x0000;
    if (r != exp_r) {
        fail = 1;
        printf("Failed GF216_longdiv test 1:\n");
        printf("Expected r:%x but got %x\n", exp_r, r);
    }
    if (q != exp_q) {
        fail = 1;
        printf("Failed GF216_longdiv test 1:\n");
        printf("Expected q:%x but got %x\n", exp_q, q);
    }

    GF216_longdiv(&q, &r, 0xFFFF, 0x0001);
    exp_q = 0xFFFF;
    exp_r = 0x0000;
    if (r != exp_r) {
        fail = 1;
        printf("Failed GF216_longdiv test 2:\n");
        printf("Expected r:%x but got %x\n", exp_r, r);
    }
    if (q != exp_q) {
        fail = 1;
        printf("Failed GF216_longdiv test 2:\n");
        printf("Expected q:%x but got %x\n", exp_q, q);
    }

    GF216_longdiv(&q, &r, 0x0000, 0xABCD);
    exp_q = 0x0000;
    exp_r = 0x0000;
    if (r != exp_r) {
        fail = 1;
        printf("Failed GF216_longdiv test 3:\n");
        printf("Expected r:%x but got %x\n", exp_r, r);
    }
    if (q != exp_q) {
        fail = 1;
        printf("Failed GF216_longdiv test 3:\n");
        printf("Expected q:%x but got %x\n", exp_q, q);
    }

    GF216_longdiv(&q, &r, 0xE52F, 0x0BE2);
    exp_q = 0x0018;
    exp_r = 0x041F;
    if (r != exp_r) {
        fail = 1;
        printf("Failed GF216_longdiv test 4:\n");
        printf("Expected r:%x but got %x\n", exp_r, r);
    }
    if (q != exp_q) {
        fail = 1;
        printf("Failed GF216_longdiv test 4:\n");
        printf("Expected q:%x but got %x\n", exp_q, q);
    }

    GF216_longdiv(&q, &r, 0x011B, 0x004E);
    exp_q = 0x0004;
    exp_r = 0x0023;
    if (r != exp_r) {
        fail = 1;
        printf("Failed GF216_longdiv test 5:\n");
        printf("Expected r:%x but got %x\n", exp_r, r);
    }
    if (q != exp_q) {
        fail = 1;
        printf("Failed GF216_longdiv test 5:\n");
        printf("Expected q:%x but got %x\n", exp_q, q);
    }

    return fail;
}

_Bool test_GF28_inv(void) {
    _Bool fail = 0;
    uint8_t out, exp;

    out = GF28_inv(0x01);
    exp = 0x01;
    if (out != exp) {
        fail = 1;
        printf("Failed GF28_inv test 0:\n");
        printf("Expected %x but got %x\n", exp, out);
    }

    out = GF28_inv(0x0F);
    exp = 0xC7;
    if (out != exp) {
        fail = 1;
        printf("Failed GF28_inv test 1:\n");
        printf("Expected %x but got %x\n", exp, out);
    }

    out = GF28_inv(0x2E);
    exp = 0xA2;
    if (out != exp) {
        fail = 1;
        printf("Failed GF28_inv test 2:\n");
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
    
    out = poly_mult_inv(-18, 24);
    exp = -6;
    if (out != exp) {
        fail = 1;
        printf("Failed poly_mult_inv test 6:\n");
        printf("Expected %li but got %li\n", exp, out);
    }

    out = poly_mult_inv(9, -3);
    exp = -3;
    if (out != exp) {
        fail = 1;
        printf("Failed poly_mult_inv test 7:\n");
        printf("Expected %li but got %li\n", exp, out);
    }

    out = poly_mult_inv(-25, -15);
    exp = -5;
    if (out != exp) {
        fail = 1;
        printf("Failed poly_mult_inv test 8:\n");
        printf("Expected %li but got %li\n", exp, out);
    }

    out = poly_mult_inv(-63, 27);
    exp = -9;
    if (out != exp) {
        fail = 1;
        printf("Failed poly_mult_inv test 9:\n");
        printf("Expected %li but got %li\n", exp, out);
    }

    out = poly_mult_inv(-41, 13);
    exp = 6;
    if (out != exp) {
        fail = 1;
        printf("Failed poly_mult_inv test 10:\n");
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

_Bool test_poly_GFsame(void) {
    _Bool fail = 0;
    int64_t out, exp;

    int64_t a0[6] = {5, 3, -7, 1, 3, 2};
    out = poly_GFsame(a0, a0, 7, 5);
    exp = 1;
    if (out != exp) {
        fail = 1;
        printf("Failed poly_GFsame test 0:\n");
        printf("Expected %li but got %li\n", exp, out);
    }

    int64_t a1[6] = {12, 17, 0, -6, 10, -12};
    out = poly_GFsame(a0, a1, 7, 5);
    exp = 1;
    if (out != exp) {
        fail = 1;
        printf("Failed poly_GFsame test 1:\n");
        printf("Expected %li but got %li\n", exp, out);
    }

    out = poly_GFsame(a0, a1, 9, 5);
    exp = 0;
    if (out != exp) {
        fail = 1;
        printf("Failed poly_GFsame test 2:\n");
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

    int64_t a3[10] = {8, 4, 1, 0, -2, 6, 5},
            b3[10] = {1, -2, 0, -9, 8, 5, 3},
            c3[20] = {0},
            exp3[20] = {8, -12, -7, -74, 26, 73, 45, 25, -67, -7, 64, 43, 15};

    poly_mult(c3, a3, b3, 9);
    if (!poly_same(c3, exp3, 19)) {
        fail = 1;
        printf("Failed poly_mult test 3.\n");
        printf("out: "), print_array(c3, 20);
        printf("exp: "), print_array(exp3, 20);
    }

    int64_t a4[5] = {1, 2, 3, 4, 5},
            b4[5] = {-1},
            c4[10] = {0},
            exp4[10] = {-1, -2, -3, -4, -5};

    poly_mult(c4, a4, b4, 4);
    if (!poly_same(c4, exp4, 9)) {
        fail = 1;
        printf("Failed poly_mult test 4.\n");
        printf("out: "), print_array(c4, 9);
        printf("exp: "), print_array(exp4, 9);
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

_Bool test_poly_GFdiv(void) {
    _Bool fail = 0;

    int64_t a0[5] = {1, 2, 3, 4, 5},
            b0[5] = {1, 2, 3, 4, 5},
            q0[5] = {0},
            expa0[5] = {0},
            expq0[5] = {1};

    poly_GFdiv(q0, a0, b0, 11, 4);
    if (!poly_same(a0, expa0, 4)) {
        fail = 1;
        printf("Failed poly_GFdiv test 0.\n");
        printf("a: "), print_array(a0, 5);
        printf("expa: "), print_array(expa0, 5);
    }
    if (!poly_same(q0, expq0, 4)) {
        fail = 1;
        printf("Failed poly_GFdiv test 0.\n");
        printf("q: "), print_array(q0, 5);
        printf("expq: "), print_array(expq0, 5);
    }
    
    int64_t a1[5] = {0},
            b1[5] = {6, 2, -12, 1},
            q1[5] = {0},
            expa1[5] = {0},
            expq1[5] = {0};

    poly_GFdiv(q1, a1, b1, 11, 4);
    if (!poly_same(a1, expa1, 4)) {
        fail = 1;
        printf("Failed poly_GFdiv test 1.\n");
        printf("a: "), print_array(a1, 5);
        printf("expa: "), print_array(expa1, 5);
    }
    if (!poly_same(q1, expq1, 4)) {
        fail = 1;
        printf("Failed poly_GFdiv test 1.\n");
        printf("q: "), print_array(q1, 5);
        printf("expq: "), print_array(expq1, 5);
    }

    int64_t a2[7] = {-1, 0, 7, 3, -6, 0, 8},
            b2[7] = {-2, 0, 4},
            q2[7] = {0},
            expa2[7] = {2, 7},
            expq2[7] = {7, 9, 5, 0, 2};

    poly_GFdiv(q2, a2, b2, 11, 6);
    if (!poly_GFsame(a2, expa2, 11, 6)) {
        fail = 1;
        printf("Failed poly_GFdiv test 2.\n");
        printf("a: "), print_array(a2, 7);
        printf("expa: "), print_array(expa2, 7);
    }
    if (!poly_GFsame(q2, expq2, 11, 6)) {
        fail = 1;
        printf("Failed poly_GFdiv test 2.\n");
        printf("q: "), print_array(q2, 7);
        printf("expq: "), print_array(expq2, 7);
    }

    int64_t a3[7] = {0, 1, 2, 3, 4, 5, 6},
            b3[7] = {0},
            q3[7] = {0},
            expa3[7] = {0, 1, 2, 3, 4, 5, 6},
            expq3[7] = {0};

    uint8_t expr3 = 1,
            r3;

    r3 = poly_GFdiv(q3, a3, b3, 11, 6);
    if (r3 != expr3) {
        fail = 1;
        printf("Failed poly_GFdiv test 3:\n");
        printf("Expected %x but got %x\n", expr3, r3);
    }
    if (!poly_GFsame(a3, expa3, 11, 6)) {
        fail = 1;
        printf("Failed poly_GFdiv test 3.\n");
        printf("a: "), print_array(a3, 7);
        printf("expa: "), print_array(expa3, 7);
    }
    if (!poly_GFsame(q3, expq3, 11, 6)) {
        fail = 1;
        printf("Failed poly_GFdiv test 3.\n");
        printf("q: "), print_array(q3, 7);
        printf("expq: "), print_array(expq3, 7);
    }

    int64_t a4[7] = {0, 1, 2, 3, 4, 5, 6},
            b4[7] = {5, -10, -25, 0, 10},
            q4[7] = {0},
            expa4[7] = {0, 1, 2, 3, 4, 5, 6},
            expq4[7] = {0};

    uint8_t expr4 = 1,
            r4;

    r4 = poly_GFdiv(q4, a4, b4, 5, 6);
    if (r4 != expr4) {
        fail = 1;
        printf("Failed poly_GFdiv test 4:\n");
        printf("Expected %x but got %x\n", expr4, r4);
    }
    if (!poly_GFsame(a4, expa4, 5, 6)) {
        fail = 1;
        printf("Failed poly_GFdiv test 4.\n");
        printf("a: "), print_array(a4, 7);
        printf("expa: "), print_array(expa4, 7);
    }
    if (!poly_GFsame(q4, expq4, 5, 6)) {
        fail = 1;
        printf("Failed poly_GFdiv test 4.\n");
        printf("q: "), print_array(q4, 7);
        printf("expq: "), print_array(expq4, 7);
    }

    return fail;
}

_Bool test_poly_GFinv(void) {
    _Bool fail = 0;

    int64_t a0[5] = {0, 1},
            b0[5] = {1, 1, 1},
            c0[5] = {0},
            exp0[5] = {1, 1};

    poly_GFinv(c0, a0, b0, 2, 4);
    if (!poly_same(c0, exp0, 4)) {
        fail = 1;
        printf("Failed poly_GFinv test 0.\n");
        printf("out: "), print_array(c0, 5);
        printf("exp: "), print_array(exp0, 5);
    }

    int64_t a1[5] = {1, 1, 1},
            b1[5] = {1, 1, 1},
            c1[5] = {0},
            exp1[5] = {0};

    poly_GFinv(c1, a1, b1, 2, 4);
    if (!poly_same(c1, exp1, 4)) {
        fail = 1;
        printf("Failed poly_GFinv test 1.\n");
        printf("out: "), print_array(c1, 5);
        printf("exp: "), print_array(exp1, 5);
    }

    int64_t a2[5] = {1, 1, 0, 1, 1},
            b2[5] = {1, 1, 1},
            c2[5] = {0},
            exp2[5] = {0};

    poly_GFinv(c2, a2, b2, 2, 4);
    if (!poly_same(c2, exp2, 4)) {
        fail = 1;
        printf("Failed poly_GFinv test 2.\n");
        printf("out: "), print_array(c2, 5);
        printf("exp: "), print_array(exp2, 5);
    }

    int64_t a3[5] = {5, 0, 1, 5, 2},
            b3[5] = {6, 4, 0, 1},
            c3[5] = {0},
            exp3[5] = {3, 5, 2};

    poly_GFinv(c3, a3, b3, 7, 4);
    if (!poly_same(c3, exp3, 4)) {
        fail = 1;
        printf("Failed poly_GFinv test 3.\n");
        printf("out: "), print_array(c3, 5);
        printf("exp: "), print_array(exp3, 5);
    }

    return fail;
}

int main (void) {

    _Bool fail = 0;

    fail += test_GF28_mult();
    fail += test_GF28_longdiv();
    fail += test_GF216_longdiv();
    fail += test_GF28_inv();
    fail += test_poly_order();
    fail += test_poly_leadc();
    fail += test_poly_concl();
    fail += test_poly_mult_inv();
    fail += test_poly_same();
    fail += test_poly_GFsame();
    fail += test_poly_copy();
    fail += test_poly_mod();
    fail += test_poly_add();
    fail += test_poly_add_mult();
    fail += test_poly_mult();
    fail += test_poly_add_ord();
    fail += test_poly_GFrem();
    fail += test_poly_GFdiv();
    fail += test_poly_GFinv();

    if (!fail) {
        printf("\x1b[32mAll tests passed successfully!\x1b[0m\n");
    }
    exit(EXIT_SUCCESS);
}
