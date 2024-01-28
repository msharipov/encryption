#ifndef POLYALG_C
#define POLYALG_C

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

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


int64_t poly_concl(int64_t n, int64_t modulo) {

    int64_t simple_mod = n % modulo;

    if (simple_mod > 0) {
        return n % modulo;
    } else {
        return (modulo + (n % modulo)) % modulo;
    }
}


int64_t poly_mult_inv(int64_t x, int64_t mod) {

    int64_t b0 = 0, x0 = 0, y0 = 0,
            b1 = x, x1 = 1, y1 = 0,
            b2 = mod, x2 = 0, y2 = 1;

    while (b2) {
        b0 = b1;
        b1 = b2;
        x0 = x1;
        x1 = x2;
        y0 = y1;
        y1 = y2;

        b2 = b0 % b1;
        x2 = x0 - (b0/b1)*x1;
        y2 = y0 - (b0/b1)*y1;
    }

    if (b1 > 1) {
        // Return -GCD if there is no inverse
        return -b1;
    } else {
        // Return the inverse
        return x1 + (x1 > 0 ? 0 : mod);
    }
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


bool poly_same(int64_t a[], int64_t b[], size_t max_ord) {

    for (size_t i = 0; i <= max_ord; i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }

    return true;
}


void poly_copy(int64_t dest[], int64_t p[], size_t max_ord) {

    for (size_t i = 0; i <= max_ord; i++) {
        dest[i] = p[i];
    }
}


void poly_mod(int64_t p[], int64_t modulo, size_t max_ord) {

    for (size_t i = 0; i <= max_ord; i++) {
        p[i] = poly_concl(p[i], modulo);
    }
}


void poly_add(int64_t dest[], int64_t add[], size_t max_ord) {

    for (size_t i = 0; i <= max_ord; i++) {
        dest[i] += add[i];
    }
}


void poly_add_mult(int64_t dest[], int64_t add[], int64_t b, size_t max_ord) {

    for (size_t i = 0; i <= max_ord; i++) {
        dest[i] += b*add[i];
    }
}


void poly_add_ord(int64_t p[], size_t power, size_t max_ord) {
    
    if (power == 0) {
        return;
    }

    for (int64_t i = max_ord; i >= power; i--) {
        p[i] = p[i - power];
    }

    for (int64_t i = 0; i < power; i++) {
        p[i] = 0;
    }
}


void poly_inring(int64_t p[], int64_t mod_p[], int64_t mod, size_t max_ord) {

    int64_t m_copy[max_ord + 1];
    int64_t p_ord = poly_order(p, max_ord),
            m_ord = poly_order(mod_p, max_ord);

    while (p_ord >= m_ord) {
        int64_t b = poly_leadc(p, max_ord);

        poly_copy(m_copy, mod_p, max_ord);
        poly_add_ord(m_copy, p_ord - m_ord, max_ord);

        // At this point, [p] and [m_copy] should have the same order.

        b *= poly_mult_inv(poly_concl(poly_leadc(m_copy, max_ord), mod), mod);

        // At this point, multiplying [m_copy] by [b] should make the leading
        // coefficient the same as for [p].

        poly_add_mult(p, m_copy, -b, max_ord);
        p_ord = poly_order(p, max_ord);
    }

    poly_mod(p, mod, max_ord);
}

#endif
