#ifndef encrypt_DES_h
#define encrypt_DES_h

#include <stdint.h>
#include <stdlib.h>

const uint8_t DES_S_BOXES[8][4][16] = {

    {{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
     {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
     {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
     {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}},

    {{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
     {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
     {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
     {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}},

    {{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
     {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
     {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
     {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}},

    {{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
     {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
     {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
     {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}},

    {{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
     {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
     {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
     {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}},

    {{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
     {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
     {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
     {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}},

    {{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
     {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
     {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
     {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}},

    {{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
     {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
     {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
     {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}}

};

const uint64_t DES_EXPANSION_MASKS[8] = {
    0b011111ULL << 27,
    0b111111ULL << 23,
    0b111111ULL << 19,
    0b111111ULL << 15,
    0b111111ULL << 11,
    0b111111ULL << 7,
    0b111111ULL << 3,
    0b011111ULL,
};

const size_t DES_P_BOX[32] = {
    15, 6,  19, 20, 28, 11, 27, 16,
    0,  14, 22, 25, 4,  17, 30, 9,
    1,  7,  23, 13, 31, 26, 2,  8,
    18, 12, 29, 5,  21, 10, 3,  24    
};

const size_t DES_KEY_PERM_1[56] = {
    56, 48, 40, 32, 24, 16, 8,
    0,  57, 49, 41, 33, 25, 17,
    9,  1,  58, 50, 42, 34, 26,
    18, 10, 2,  59, 51, 43, 35,
    62, 54, 46, 38, 30, 22, 14,
    6,  61, 53, 45, 37, 29, 21,
    13, 5,  60, 52, 44, 36, 28,
    20, 12, 4,  27, 19, 11, 3
};

const size_t DES_KEY_PERM_2[48] = {
    13, 16, 10, 23, 0,  4,  2,  27,
    14, 5,  20, 9,  22, 18, 11, 3,
    25, 7,  15, 6,  26, 19, 12, 1,
    40, 51, 30, 36, 46, 54, 29, 39,
    50, 44, 32, 47, 43, 48, 38, 55,
    33, 52, 45, 41, 49, 35, 28, 31
};

// Expands 32-bit plaintext to 48 bits and returns the nth 6-bit word
// 6-bit words are stored in the lower bits of uint8_t
uint8_t DES_get_expanded_word(uint64_t plain, uint8_t n) {

    uint64_t mask_product = DES_EXPANSION_MASKS[n] & plain;

    // Uses bit masks to pull out the desired bits for each word
    if (n == 0) {
        mask_product >>= 27;
        mask_product += (plain & 1) << 5;
    } else if (n < 7) {
        mask_product >>= 4*(7 - n) - 1;
    } else {
        mask_product <<= 1;
        mask_product += (plain >> 31) & 1;
    }

    return (uint8_t)mask_product;
}

uint8_t DES_substitute(uint8_t word, uint8_t n) {

    size_t row = (word & 1) + ((word & 0b100000) >> 4);
    size_t col = (word & 0b011110) >> 1;

    return DES_S_BOXES[n][row][col];
}

uint64_t DES_permute(uint8_t words[]) {

    uint64_t input = 0,
             output = 0;

    // Combines 4-bit words back into 32 bits
    for (int i = 0; i < 8; i++) {
        input += (uint64_t)words[i] << 4*(7 - i);
    }

    const uint64_t ZEROTH_BIT = 1ULL << 31;
    // Permutes bits according to the P-box
    for (size_t out_pos = 0; out_pos < 32; out_pos++) {
        
        size_t in_pos = DES_P_BOX[out_pos];

        if (input & ZEROTH_BIT >> in_pos) {
            output += ZEROTH_BIT >> out_pos;
        }
    }

    return output;
}

// Extracts 56 bits from the initial 64-bit key
uint64_t DES_permute_initial_key(uint64_t key64) {
    
    uint64_t key56 = 0;

    const uint64_t ZEROTH_BIT_IN = 1ULL << 63,
                   ZEROTH_BIT_OUT = 1ULL << 55;
    for (size_t out_pos = 0; out_pos < 56; out_pos++) {
        
        size_t in_pos = DES_KEY_PERM_1[out_pos];
        
        if (key64 & ZEROTH_BIT_IN >> in_pos) {
            key56 += ZEROTH_BIT_OUT >> out_pos;
        }
    }

    return key56;
}

// Shrinks the 56-bit key to produce the first round key
uint64_t DES_key_contraction(uint64_t key56) {
    
    uint64_t round_key = 0;

    const uint64_t ZEROTH_BIT_IN = 1ULL << 55,
                   ZEROTH_BIT_OUT = 1ULL << 47;
    for (size_t out_pos = 0; out_pos < 48; out_pos++) {
        
        size_t in_pos = DES_KEY_PERM_2[out_pos];

        if (key56 & ZEROTH_BIT_IN >> in_pos) {
            round_key += ZEROTH_BIT_OUT >> out_pos;
        }
    }
    return round_key;
}

// Separately left-shifts each half of the key once
uint64_t DES_key_shift(uint64_t key56) {

    uint64_t output = 0;
    const uint64_t PRE_SHIFT_MASK = 0x7ffffff7ffffffULL;
    output += (key56 & PRE_SHIFT_MASK) << 1;
    output += (key56 & 1ULL << 27) ? 1ULL : 0;
    output += (key56 & 1ULL << 55) ? (1ULL << 28) : 0;

    return output;
}

// Generates 16 round keys, starting with initial 64-bit key
void DES_generate_round_keys(uint64_t rnd_keys[], uint64_t key64) {

    uint64_t key = DES_permute_initial_key(key64);

    for (int round = 0; round < 16; round++) {

        key = DES_key_shift(key);
        if (round > 1 && round != 8 && round != 15) {
            key = DES_key_shift(key);
        }

        rnd_keys[round] = DES_key_contraction(key);
    }
}

// Feistel function
uint64_t DES_Feistel(uint64_t RE, uint64_t round_key) {
    
    uint8_t words[8] = {0};
    for (int i = 0; i < 8; i++) {
        uint8_t word = DES_get_expanded_word(RE, i);
        word ^= (round_key >> (i * 6) & 0x00111111);
        word = DES_substitute(word, i);
    }

    return DES_permute(words);
}

#endif