#ifndef POLYALG_C
#define POLYALG_C

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

uint8_t GF28_mult(const uint8_t f, const uint8_t g) {

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


int64_t poly_concl(const int64_t n, const int64_t modulo) {

    int64_t simple_mod = n % modulo;

    if (simple_mod > 0) {
        return n % modulo;
    } else {
        return (modulo + (n % modulo)) % modulo;
    }
}


int64_t poly_mult_inv(const int64_t x, const int64_t mod) {

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


size_t poly_order(const int64_t p[], const size_t max_ord) {

    for (size_t i = max_ord; i > 0; i--) {
        if (p[i]) {
            return i;
        }
    }

    return p[0];
}


int64_t poly_leadc(const int64_t p[], const size_t max_ord) {

    return p[poly_order(p, max_ord)];
}


bool poly_same(const int64_t a[], const int64_t b[], const size_t max_ord) {

    for (size_t i = 0; i <= max_ord; i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }

    return true;
}


void poly_copy(int64_t dest[], const int64_t p[], const size_t max_ord) {

    for (size_t i = 0; i <= max_ord; i++) {
        dest[i] = p[i];
    }
}


void poly_mod(int64_t p[], const int64_t modulo, const size_t max_ord) {

    for (size_t i = 0; i <= max_ord; i++) {
        p[i] = poly_concl(p[i], modulo);
    }
}


void poly_add(int64_t dest[], const int64_t add[], const size_t max_ord) {

    for (size_t i = 0; i <= max_ord; i++) {
        dest[i] += add[i];
    }
}


void poly_add_mult(int64_t dest[], const int64_t add[], const int64_t b, 
                   const size_t max_ord) {

    for (size_t i = 0; i <= max_ord; i++) {
        dest[i] += b*add[i];
    }
}


void poly_add_ord(int64_t p[], const size_t power, const size_t max_ord) {
    
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


void poly_mult(int64_t dest[], const int64_t a[], const int64_t b[],
               const size_t max_ord) {
    
    size_t a_ord = poly_order(a, max_ord),
           b_ord = poly_order(b, max_ord);

    for (size_t k = 0; k <= a_ord + b_ord; k++) {

        // c[k] = sum(a[i-k]*b[i]) over i in [0,k]
        int64_t c = 0;

        // k-i <= a_ord and i >= 0
        size_t start_i = (k > a_ord) ? k - a_ord : 0;

        // k-i >= 0 and i <= b_ord
        size_t end_i = (b_ord < k) ? b_ord : k;

        for (size_t i = start_i; i <= end_i; i++) {
            c += a[i-k]*b[k];
        }

        dest[k] = c;
    }

    for (size_t k = a_ord + b_ord + 1; k <= 2*max_ord; k++) {
        dest[k] = 0;
    }

}


void poly_GFrem(int64_t p[], const int64_t mod_p[], const int64_t mod, 
                const size_t max_ord) {

    int64_t m_copy[max_ord + 1];
    size_t p_ord = poly_order(p, max_ord),
           m_ord = poly_order(mod_p, max_ord);

    while (p_ord >= m_ord && p[p_ord]) {

        int64_t b = p[p_ord];
        poly_copy(m_copy, mod_p, max_ord);
        poly_add_ord(m_copy, p_ord - m_ord, max_ord);

        // At this point, [p] and [m_copy] should have the same order.

        b *= poly_mult_inv(poly_concl(poly_leadc(m_copy, max_ord), mod), mod);

        // At this point, multiplying [m_copy] by [b] should make the leading
        // coefficient the same as for [p].

        poly_add_mult(p, m_copy, -b, max_ord);
        poly_mod(p, mod, max_ord);
        p_ord = poly_order(p, p_ord);
    }

    poly_mod(p, mod, max_ord);
}


void poly_GFinv(int64_t p_inv[], const int64_t p[], const int64_t mod_p[],
                const int64_t mod, const size_t max_ord) {
    // WIP
}

#endif
