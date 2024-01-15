#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "DES.h"

_Bool test_expansion(void) {

    _Bool fail = 0;
    const uint64_t NUMBER64 = 
    //                                v32
    //FEDCBA9876543210FEDCBA9876543210FEDCBA9876543210FEDCBA9876543210
    0b0100101101001011010010110100101101001011010010110100101101001011;

    uint8_t out, exp;

    out = DES_get_expanded_word(NUMBER64, 0);
    exp = 0b101001;
    if (out != exp) {
        fail = 1;
        printf("Failed expansion test 0:\n");
        printf("Expected %x but got %x\n", exp, out);
    }

    out = DES_get_expanded_word(NUMBER64, 1);
    exp = 0b010110;
    if (out != exp) {
        fail = 1;
        printf("Failed expansion test 1:\n");
        printf("Expected %x but got %x\n", exp, out);
    }

    out = DES_get_expanded_word(NUMBER64, 2);
    exp = 0b101001;
    if (out != exp) {
        fail = 1;
        printf("Failed expansion test 2:\n");
        printf("Expected %x but got %x\n", exp, out);
    }

    out = DES_get_expanded_word(NUMBER64, 3);
    exp = 0b010110;
    if (out != exp) {
        fail = 1;
        printf("Failed expansion test 3:\n");
        printf("Expected %x but got %x\n", exp, out);
    }

    out = DES_get_expanded_word(NUMBER64, 4);
    exp = 0b101001;
    if (out != exp) {
        fail = 1;
        printf("Failed expansion test 4:\n");
        printf("Expected %x but got %x\n", exp, out);
    }

    out = DES_get_expanded_word(NUMBER64, 5);
    exp = 0b010110;
    if (out != exp) {
        fail = 1;
        printf("Failed expansion test 5:\n");
        printf("Expected %x but got %x\n", exp, out);
    }

    out = DES_get_expanded_word(NUMBER64, 6);
    exp = 0b101001;
    if (out != exp) {
        fail = 1;
        printf("Failed expansion test 6:\n");
        printf("Expected %x but got %x\n", exp, out);
    }

    out = DES_get_expanded_word(NUMBER64, 7);
    exp = 0b010110;
    if (out != exp) {
        fail = 1;
        printf("Failed expansion test 7:\n");
        printf("Expected %x but got %x\n", exp, out);
    }

    return fail;
}

_Bool test_s_boxes(void) {

    _Bool fail = 0;
    uint8_t out, exp;

    out = DES_substitute(0b000000, 0);
    exp = 14;
    if (out != exp) {
        fail = 1;
        printf("Failed S-box test 0:\n");
        printf("Expected %x but got %x\n", exp, out);
    }

    out = DES_substitute(0b101010, 3);
    exp = 11;
    if (out != exp) {
        fail = 1;
        printf("Failed S-box test 1:\n");
        printf("Expected %x but got %x\n", exp, out);
    }

    out = DES_substitute(0b111111, 2);
    exp = 12;
    if (out != exp) {
        fail = 1;
        printf("Failed S-box test 2:\n");
        printf("Expected %x but got %x\n", exp, out);
    }

    out = DES_substitute(0b000111, 6);
    exp = 7;
    if (out != exp) {
        fail = 1;
        printf("Failed S-box test 3:\n");
        printf("Expected %x but got %x\n", exp, out);
    }

    return fail;
}

_Bool test_p_box(void) {

    _Bool fail = 0;
    uint8_t words[] = {0xa, 0xa, 0xa, 0xa, 0xa, 0xa, 0xa, 0xa};
    uint64_t out = DES_permute(words),
             exp = 0b01011001111010100000011111000101;
    if (out != exp) {
        fail = 1;
        printf("Failed P-box test:\n");
        printf("Expected %lx but got %lx\n", exp, out);
    }

    return fail;
}

_Bool test_key_perm_1(void) {

    _Bool fail = 0;
    uint64_t out = DES_permute_initial_key(0x5555555555555555ULL),
             exp = 0x00ff00f00ff00fULL;
    if (out != exp) {
        fail = 1;
        printf("Failed initial key permutation test:\n");
        printf("Expected %lx but got %lx\n", exp, out);
    }

    return fail;
}

_Bool test_key_perm_2(void) {

    _Bool fail = 0;
    uint64_t out = DES_key_contraction(0x55555555555555ULL),
             exp = 0x9153e54319bdULL;
    if (out != exp) {
        fail = 1;
        printf("Failed key contraction test 0:\n");
        printf("Expected %lx but got %lx\n", exp, out);
    }

    out = DES_key_contraction(0xffffffffffffffULL);
    exp = 0xffffffffffffULL;
    if (out != exp) {
        fail = 1;
        printf("Failed key contraction test 1:\n");
        printf("Expected %lx but got %lx\n", exp, out);
    }

    out = DES_key_contraction(0);
    exp = 0;
    if (out != exp) {
        fail = 1;
        printf("Failed key contraction test 2:\n");
        printf("Expected %lx but got %lx\n", exp, out);
    }

    return fail;
}

_Bool test_key_shift(void) {

    _Bool fail = 0;
    uint64_t out = DES_key_shift(0x55555555555555ULL),
             exp = 0xaaaaaaaaaaaaaaULL;
    if (out != exp) {
        fail = 1;
        printf("Failed key shift test:\n");
        printf("Expected %lx but got %lx\n", exp, out);
    }

    return fail;
}

_Bool test_key_generation(void) {
    
    _Bool fail = 0;
    uint64_t out[16] = {0},
             exp[16] = {
                0b101100001001001011001010110101010000001001010100ULL,
                0b101100000001101011010010110100011000001001010100ULL,
                0b001101000111101001010000010100011010011010001100ULL,
                0b000001100111010101010100001110000011010010001101ULL,
                0b010011100100010101010101001010100111000010100111ULL,
                0b010011111100000100101001001001100110100110100011ULL,
                0b100010111000000110101011101001100000100101010011ULL,
                0b101110010000101010001011110001111000001101010010ULL,
                0b001110010001101010001010110001011000001101001010ULL,
                0b001100000011100011001100010101001001011001001100ULL,
                0b000100000110110001010100010110001001010011101100ULL,
                0b010001000110110100110100000010001111110010101001ULL,
                0b110001101010010100100101001010100111110000110001ULL,
                0b110010111000011000100011101010110100100100110010ULL,
                0b111010011001001010101010100001010100101100010010ULL,
                0b101000011001001010101010100101010000101101010000ULL
             };

    DES_generate_round_keys(out, 0x5555555555555555ULL);

    for (int r = 0; r < 15; r++) {
        if (out[r] != exp[r]) {
            fail = 1;
            printf("Failed round key generation test at step %i:\n", r);
            printf("Expected %lx but got %lx\n", exp[r], out[r]);
        }
    }
    return fail;
}

_Bool test_encrypt(void) {

    _Bool fail = 0;
    uint64_t round_keys[16] = {0};
    uint64_t out, exp;
    const uint64_t SAMPLE = 0xfedcba0987654321ULL;

    out = DES_decrypt(DES_encrypt(0, round_keys), round_keys),
    exp = 0;
    if (out != exp) {
        fail = 1;
        printf("Failed encryption/decryption test 0:\n");
        printf("Expected %lx but got %lx\n", exp, out);
    }

    DES_generate_round_keys(round_keys, 0x1234);
    out = DES_decrypt(DES_encrypt(SAMPLE, round_keys), round_keys),
    exp = SAMPLE;
    if (out != exp) {
        fail = 1;
        printf("Failed encryption/decryption test 1:\n");
        printf("Expected %lx but got %lx\n", exp, out);
    }

    return fail;
}

int main(void) {

    _Bool fail = 0;

    fail += test_expansion();
    fail += test_s_boxes();
    fail += test_p_box();
    fail += test_key_perm_1();
    fail += test_key_perm_2();
    fail += test_key_shift();
    fail += test_key_generation();
    fail += test_encrypt();

    if (!fail) {
        printf("\x1b[32mAll tests passed successfully!\x1b[0m\n");
    }

    exit(EXIT_SUCCESS);
}
