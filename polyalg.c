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


void GF28_longdiv(uint8_t * q, uint8_t * r, const uint8_t f, const uint8_t g) {
    
    if (g == 0) {
        return;
    }

    uint8_t f_ord = 0,
            g_ord = 0;
    
    *q = 0;
    *r = f;

    while (g >> (g_ord + 1)) {
        g_ord++;
    }

    while (f >> (f_ord + 1)) {
        f_ord++;
    }

    while (f_ord >= g_ord && *r) {

        *r ^= g << (f_ord - g_ord);
        *q += 1U << (f_ord - g_ord);

        f_ord = 0;
        while (*r >> (f_ord + 1)) {
            f_ord++;
        }
    }
}


void GF216_longdiv(uint16_t * q, uint16_t * r, const uint16_t f, 
                   const uint16_t g) {
    
    if (g == 0) {
        return;
    }

    uint8_t f_ord = 0,
            g_ord = 0;
    
    *q = 0;
    *r = f;

    while (g >> (g_ord + 1)) {
        g_ord++;
    }

    while (f >> (f_ord + 1)) {
        f_ord++;
    }

    // Runs while [f] is at least same order as [g]
    while (f_ord >= g_ord && *r) {

        *r ^= g << (f_ord - g_ord);
        *q += 1U << (f_ord - g_ord);

        f_ord = 0;
        while (*r >> (f_ord + 1)) {
            f_ord++;
        }
    }
}


uint8_t GF28_inv(const uint8_t p) {

    uint16_t r0 = 0,     s0 = 0,
             r1 = p,     s1 = 1,
             r2 = 0x11B, s2 = 0,
             q = 0;

    while (r2) {

        r0 = r1;
        s0 = s1;
        r1 = r2;
        s1 = s2;

        GF216_longdiv(&q, &r2, r0, r1);
        // 8-bit arithmetic is sufficient here because q can only exceed 0xFF
        // when p = 1, in which case the function returns the correct value
        // before the incorrectly computed s2 is involved.
        s2 = s0 ^ GF28_mult(q, s1);
    }

    return s1;
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

    int64_t b0 = 0, x0 = 0,
            b1 = poly_concl(x, mod), x1 = 1,
            b2 = mod, x2 = 0;

    if (mod < 0) {
        b1 = -b1;
        b2 = -b2;
    }

    while (b2) {
        b0 = b1;
        b1 = b2;
        x0 = x1;
        x1 = x2;

        b2 = b0 % b1;
        x2 = x0 - (b0/b1)*x1;
    }

    if (b1 > 1) {
        // Return -GCD if there is no inverse
        return -b1;
    } else {
        // Return the inverse
        return poly_concl(x1, mod);
    }
}


size_t poly_order(const int64_t p[], const size_t max_ord) {

    for (size_t i = max_ord; i > 0; i--) {
        if (p[i]) {
            return i;
        }
    }

    return 0;
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


bool poly_GFsame(const int64_t a[], const int64_t b[], const int64_t mod, 
                 const size_t max_ord) {
    
    for (size_t i = 0; i <= max_ord; i++) {
        if (poly_concl(a[i], mod) != poly_concl(b[i], mod)) {
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
            c += a[k-i]*b[i];
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


uint8_t poly_GFdiv(int64_t q[], int64_t p[], const int64_t mod_p[], 
                const int64_t mod, const size_t max_ord) {

    int64_t divisor[max_ord + 1],
            div_copy[max_ord + 1];
    size_t p_ord = poly_order(p, max_ord),
           m_ord;

    poly_copy(divisor, mod_p, max_ord);
    poly_mod(divisor, mod, max_ord);
    m_ord = poly_order(divisor, max_ord);
    if (m_ord == 0 && divisor[0] == 0) {
        return 1;
    }

    if (mod == 0) {
        return 2;
    }

    for (size_t i = 0; i <= max_ord; i++) {
        q[i] = 0;
    }

    while (p_ord >= m_ord && p[p_ord]) {

        int64_t b = p[p_ord];
        poly_copy(div_copy, divisor, max_ord);
        poly_add_ord(div_copy, p_ord - m_ord, max_ord);

        // At this point, [p] and [div_copy] should have the same order.

        b *= poly_mult_inv(poly_concl(poly_leadc(div_copy, max_ord), mod), mod);
        q[p_ord - m_ord] = poly_concl(b, mod);

        // At this point, multiplying [div_copy] by [b] should make the leading
        // coefficient the same as for [p].

        poly_add_mult(p, div_copy, -b, max_ord);
        poly_mod(p, mod, max_ord);
        p_ord = poly_order(p, p_ord);
    }

    poly_mod(p, mod, max_ord);
    return 0;
}


void poly_GFinv(int64_t p_inv[], const int64_t p[], const int64_t mod_p[],
                const int64_t mod, const size_t max_ord) {
    
    int64_t r0[max_ord + 1],
            r1[max_ord + 1],
            r2[max_ord + 1],
            s0[max_ord + 1],
            s1[max_ord + 1],
            s2[max_ord + 1],
            q[max_ord + 1],
            qs[2*max_ord + 1],
            wide_mod_p[2*max_ord + 1];

    poly_copy(r1, p, max_ord);
    poly_GFrem(r1, mod_p, mod, max_ord);
    poly_copy(r2, mod_p, max_ord);

    for (size_t i = 0; i <= max_ord; i++) {
        s1[i] = 0;
        s2[i] = 0;
        p_inv[i] = 0;
    }
    s1[0] = 1;

    for (size_t i = 0; i <= 2*max_ord; i++) {
        qs[i] = 0;
        wide_mod_p[i] = 0;
    }
    poly_copy(wide_mod_p, mod_p, max_ord);

    while (poly_leadc(r2, max_ord) != 0) {
        
        // row0 = row1, row1 = row 2
        poly_copy(r0, r1, max_ord);
        poly_copy(s0, s1, max_ord);
        poly_copy(r1, r2, max_ord);
        poly_copy(s1, s2, max_ord);

        // r2 = r0 % r1, q = r0 / r1
        poly_copy(r2, r0, max_ord);
        poly_GFdiv(q, r2, r1, mod, max_ord);

        // s2 = s0 - q*s1
        poly_copy(s2, s0, max_ord);
        poly_mult(qs, q, s1, max_ord);
        poly_GFrem(qs, wide_mod_p, mod, 2*max_ord);
        poly_add_mult(s2, qs, -1, max_ord);
        poly_GFrem(s2, mod_p, mod, max_ord);
    }

    // If gcd(p, mod_p) == 1, inverse exists
    if (poly_order(r1, max_ord) == 0 && r1[0] == 1) {
        poly_copy(p_inv, s1, max_ord);
    }

    // If there's no inverse, leave [p_inv] as all 0's.
}

#endif
