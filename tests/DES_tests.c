#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <DES.h>

_Bool test_init_perm(void) {
    _Bool fail = 0;
    uint64_t out, exp;

    out = DES_init_perm_inv(DES_init_perm(0x1234567890ABCDEFull));
    exp = 0x1234567890ABCDEFull;
    if (out != exp) {
        fail = 1;
        printf("Failed initial block permutation test 0:\n");
        printf("Expected %lx but got %lx\n", exp, out);
    }

    out = DES_init_perm(0x5555555555555555ull);
    exp = 0xFFFFFFFF00000000ull;
    if (out != exp) {
        fail = 1;
        printf("Failed initial block permutation test 1:\n");
        printf("Expected %lx but got %lx\n", exp, out);
    }

    return fail;
}

_Bool test_expansion(void) {

    _Bool fail = 0;
    const uint64_t NUMBER64 = 0x4B4B4B4B4B4B4B4Bull;

    uint8_t out, exp;

    out = DES_get_expanded_word(NUMBER64, 0);
    exp = 0x29;
    if (out != exp) {
        fail = 1;
        printf("Failed expansion test 0:\n");
        printf("Expected %x but got %x\n", exp, out);
    }

    out = DES_get_expanded_word(NUMBER64, 1);
    exp = 0x16;
    if (out != exp) {
        fail = 1;
        printf("Failed expansion test 1:\n");
        printf("Expected %x but got %x\n", exp, out);
    }

    out = DES_get_expanded_word(NUMBER64, 2);
    exp = 0x29;
    if (out != exp) {
        fail = 1;
        printf("Failed expansion test 2:\n");
        printf("Expected %x but got %x\n", exp, out);
    }

    out = DES_get_expanded_word(NUMBER64, 3);
    exp = 0x16;
    if (out != exp) {
        fail = 1;
        printf("Failed expansion test 3:\n");
        printf("Expected %x but got %x\n", exp, out);
    }

    out = DES_get_expanded_word(NUMBER64, 4);
    exp = 0x29;
    if (out != exp) {
        fail = 1;
        printf("Failed expansion test 4:\n");
        printf("Expected %x but got %x\n", exp, out);
    }

    out = DES_get_expanded_word(NUMBER64, 5);
    exp = 0x16;
    if (out != exp) {
        fail = 1;
        printf("Failed expansion test 5:\n");
        printf("Expected %x but got %x\n", exp, out);
    }

    out = DES_get_expanded_word(NUMBER64, 6);
    exp = 0x29;
    if (out != exp) {
        fail = 1;
        printf("Failed expansion test 6:\n");
        printf("Expected %x but got %x\n", exp, out);
    }

    out = DES_get_expanded_word(NUMBER64, 7);
    exp = 0x16;
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

    out = DES_substitute(0x00, 0);
    exp = 14;
    if (out != exp) {
        fail = 1;
        printf("Failed S-box test 0:\n");
        printf("Expected %x but got %x\n", exp, out);
    }

    out = DES_substitute(0x2A, 3);
    exp = 11;
    if (out != exp) {
        fail = 1;
        printf("Failed S-box test 1:\n");
        printf("Expected %x but got %x\n", exp, out);
    }

    out = DES_substitute(0x3F, 2);
    exp = 12;
    if (out != exp) {
        fail = 1;
        printf("Failed S-box test 2:\n");
        printf("Expected %x but got %x\n", exp, out);
    }

    out = DES_substitute(0x07, 6);
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
    uint8_t words[] = {0xA, 0xA, 0xA, 0xA, 0xA, 0xA, 0xA, 0xA};
    uint64_t out = DES_permute(words),
             exp = 0x59EA07C5ul;
    if (out != exp) {
        fail = 1;
        printf("Failed P-box test:\n");
        printf("Expected %lx but got %lx\n", exp, out);
    }

    return fail;
}

_Bool test_key_perm_1(void) {

    _Bool fail = 0;
    uint64_t out = DES_permute_initial_key(0x5555555555555555ull),
             exp = 0x00FF00F00FF00Full;
    if (out != exp) {
        fail = 1;
        printf("Failed initial key permutation test:\n");
        printf("Expected %lx but got %lx\n", exp, out);
    }

    return fail;
}

_Bool test_key_perm_2(void) {

    _Bool fail = 0;
    uint64_t out = DES_key_contraction(0x55555555555555ull),
             exp = 0x9153E54319BDull;
    if (out != exp) {
        fail = 1;
        printf("Failed key contraction test 0:\n");
        printf("Expected %lx but got %lx\n", exp, out);
    }

    out = DES_key_contraction(0xFFFFFFFFFFFFFFull);
    exp = 0xFFFFFFFFFFFFull;
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
    uint64_t out = DES_key_shift(0x55555555555555ull),
             exp = 0xAAAAAAAAAAAAAAull;
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
                0xB092CAD50254ull,
                0xB01AD2D18254ull,
                0x347A5051A68Cull,
                0x06755438348Dull,
                0x4E45552A70A7ull,
                0x4FC1292669A3ull,
                0x8B81ABA60953ull,
                0xB90A8BC78352ull,
                0x391A8AC5834Aull,
                0x3038CC54964Cull,
                0x106C545894ECull,
                0x446D3408FCA9ull,
                0xC6A5252A7C31ull,
                0xCB8623AB4932ull,
                0xE992AA854B12ull,
                0xA192AA950B50ull
             };

    DES_generate_round_keys(out, 0x5555555555555555ull);

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
    const uint64_t SAMPLE = 0xFEDCBA0987654321ull;

    out = DES_decrypt(DES_encrypt(26, round_keys), round_keys),
    exp = 26;
    if (out != exp) {
        fail = 1;
        printf("Failed encryption/decryption test 0:\n");
        printf("Expected %lx but got %lx\n", exp, out);
    }

    DES_generate_round_keys(round_keys, 0x1234ull);
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

    fail += test_init_perm();
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
