#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "DES.h"

const uint64_t NUMBER64 = 
//                                v32
//FEDCBA9876543210FEDCBA9876543210FEDCBA9876543210FEDCBA9876543210
0b0100101101001011010010110100101101001011010010110100101101001011;

_Bool test_expansion(void) {

    _Bool fail = 0;

    if (DES_get_expanded_word(NUMBER64, 0)!= 0b010110) {
        fail = 1;
        printf("Failed expansion test 0\n");
        printf("Expected %x but got %x\n", 0b010110, 
               DES_get_expanded_word(NUMBER64, 0));
    }

    if (DES_get_expanded_word(NUMBER64, 1)!= 0b101001) {
        fail = 1;
        printf("Failed expansion test 1\n");
        printf("Expected %x but got %x\n", 0b101001, 
               DES_get_expanded_word(NUMBER64, 1));
    }

    if (DES_get_expanded_word(NUMBER64, 2)!= 0b010110) {
        fail = 1;
        printf("Failed expansion test 2\n");
        printf("Expected %x but got %x\n", 0b010110, 
               DES_get_expanded_word(NUMBER64, 2));
    }

    if (DES_get_expanded_word(NUMBER64, 3)!= 0b101001) {
        fail = 1;
        printf("Failed expansion test 3\n");
        printf("Expected %x but got %x\n", 0b101001, 
               DES_get_expanded_word(NUMBER64, 3));
    }

    if (DES_get_expanded_word(NUMBER64, 4)!= 0b010110) {
        fail = 1;
        printf("Failed expansion test 4\n");
        printf("Expected %x but got %x\n", 0b010110, 
               DES_get_expanded_word(NUMBER64, 4));
    }

    if (DES_get_expanded_word(NUMBER64, 5)!= 0b101001) {
        fail = 1;
        printf("Failed expansion test 5\n");
        printf("Expected %x but got %x\n", 0b101001, 
               DES_get_expanded_word(NUMBER64, 5));
    }

    if (DES_get_expanded_word(NUMBER64, 6)!= 0b010110) {
        fail = 1;
        printf("Failed expansion test 6\n");
        printf("Expected %x but got %x\n", 0b010110, 
               DES_get_expanded_word(NUMBER64, 6));
    }

    if (DES_get_expanded_word(NUMBER64, 7)!= 0b101001) {
        fail = 1;
        printf("Failed expansion test 7:\n");
        printf("Expected %x but got %x\n", 0b101001, 
               DES_get_expanded_word(NUMBER64, 7));
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
        printf("Failed key contraction test:\n");
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


int main(void) {

    _Bool fail = 0;

    fail += test_expansion();
    fail += test_s_boxes();
    fail += test_p_box();
    fail += test_key_perm_1();
    fail += test_key_perm_2();
    fail += test_key_shift();

    if (!fail) {
        printf("All tests passed successfully!\n");
    }

    exit(EXIT_SUCCESS);
}