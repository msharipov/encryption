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

int main(void) {

    _Bool fail = 0;

    if (test_expansion()) {
        fail = 1;
    }

    if (!fail) {
        printf("All tests passed successfully!\n");
    }

    exit(EXIT_SUCCESS);
}