#ifndef encrypt_DES_h
#define encrypt_DES_h

#include "DES.c"

// Turns an array of eight bytes into an uint64_t
uint64_t merge_8_to_64(uint8_t bytes[]);

// Splits an uint64_t into 8 bytes
void split_64_to_8(uint8_t bytes[], uint64_t block);

// Expands 32-bit plaintext to 48 bits and returns the nth 6-bit word
// 6-bit words are stored in the lower bits of uint8_t
uint8_t DES_get_expanded_word(uint64_t plain, uint8_t n);

// Substitutes 4-bit word for 6-bit word, using the nth S-box
uint8_t DES_substitute(uint8_t word, uint8_t n);

// Permutes an array of eight 8-bit words, using the P-box
uint64_t DES_permute(uint8_t words[]);

// Extracts 56 bits from the initial 64-bit key
uint64_t DES_permute_initial_key(uint64_t key64);

// Shrinks the 56-bit key to produce the first round key
uint64_t DES_key_contraction(uint64_t key56);

// Separately left-shifts each half of the key once
uint64_t DES_key_shift(uint64_t key56);

// Generates 16 round keys, starting with initial 64-bit key
void DES_generate_round_keys(uint64_t rnd_keys[], uint64_t key64);

// Feistel function
uint64_t DES_Feistel(uint64_t RE, uint64_t round_key);

// Initial permutation of the 64-bit data block before encryption/decryption
uint64_t DES_init_perm(uint64_t src);

// Inverse of the initial permutation of the data block
uint64_t DES_init_perm_inv(uint64_t src);

// Encrypts one 64-bit block using the array of round keys
uint64_t DES_encrypt(uint64_t plain, uint64_t rnd_keys[]);

// Decrypts one 64-bit block using the array of round keys
uint64_t DES_decrypt(uint64_t cipher, uint64_t rnd_keys[]);

// Encrypts data from the input file using the round keys and writes it to
// the output file
void DES_encrypt_file(FILE *input, FILE *output, uint64_t keys[]);

// Decrypts data from the input file using the round keys and writes it to
// the output file
// return values:
// 0 - decryption finished normally
// 1 - file size is not a multiple of 8
// 2 - error when writing to the output
uint8_t DES_decrypt_file(FILE *input, FILE *output, uint64_t keys[]);

#endif
