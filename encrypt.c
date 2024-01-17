#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include "DES.h"

#define ENCRYPT_FILE_NAME_LENGTH 256
#define ENCRYPT_MAX_KEY_LENGTH 64

void encrypt_print_usage(void) {
    printf("Usage: encrypt.exe [OPTIONS] INPUT_FILE\n"
           "Encrypts/decrypts files using DES.\n\n"
           "Arguments:\n"
           "  -d, --decrypt              decrypts the input file instead of encrypting\n\n"
           "  -K, --keep-original        retains the original file, which is\n"
           "                               deleted by default; must specify the name\n"
           "                               of the output file when this flag is set\n\n"
           "  -o, --output [FILENAME]    specifies the name of the output file; if the\n"
           "                               file already exists, it will be overwritten\n\n"
           "  -k, --key [KEY]            specifies the encryption key\n\n");
}

void encrypt_print_error(void) {
    printf("\x1b[1;31mError!\x1b[0m ");
}

int main(int argc, char *argv[]) {

    bool keep_original_flag = false,
         out_filename_provided = false,
         key_provided = false,
         decrypt = false;
    int current_arg = 0;
    FILE * input = NULL,
         * temp_output = NULL;
    char in_filename[ENCRYPT_FILE_NAME_LENGTH],
         out_filename[ENCRYPT_FILE_NAME_LENGTH],
         out_temp_name[ENCRYPT_FILE_NAME_LENGTH] = "encrypt_temp_",
         key_str[ENCRYPT_MAX_KEY_LENGTH];
    uint64_t key_word = 0;

    static struct option long_options[] = {
        {"decrypt", no_argument, NULL, 'd'},
        {"keep-original", no_argument, NULL, 'K'},
        {"output", required_argument, NULL, 'o'},
        {"key", required_argument, NULL, 'k'},
        {NULL, 0, NULL, 0}
    };
    
    while (1) {
        int option_index = 0;
        current_arg = getopt_long(argc, argv, "dKo:k:", 
                                  long_options, &option_index);
        
        if (current_arg == -1) {
            break;
        }

        switch (current_arg) {
            case 'd':
                decrypt = true;
                break;

            case 'K':
                keep_original_flag = true;
                break;

            case 'o':
                strncpy(out_filename, optarg, ENCRYPT_FILE_NAME_LENGTH);
                out_filename_provided = true;
                break;

            case 'k':
                strncpy(key_str, optarg, ENCRYPT_MAX_KEY_LENGTH);
                key_provided = true;
                break;

            case '?':
                encrypt_print_usage();
                exit(EXIT_FAILURE);
                break;

            default:
                abort();
        }
    }

    if (argc - optind != 1) {
        encrypt_print_error();
        printf("Please specify exactly one input file!\n");
        encrypt_print_usage();
        exit(EXIT_FAILURE);
    }

    strncpy(in_filename, argv[optind], ENCRYPT_FILE_NAME_LENGTH);
    input = fopen(in_filename, "rb");

    if (!input) {
        encrypt_print_error();
        printf("Cannot open the input file: %s\n", in_filename);
        exit(EXIT_FAILURE);
    }

    if (keep_original_flag && !out_filename_provided) {
        encrypt_print_error();
        printf("Must specify the name of the output file when the --keep-original\n"
               "flag is set.\n");
        exit(EXIT_FAILURE);
    }

    // Check whether both input and output point to the same file
    if (keep_original_flag) {
        if (!strncmp(in_filename, out_filename, ENCRYPT_FILE_NAME_LENGTH)) {
            encrypt_print_error();
            printf("Input and output files cannot be the same. If you want to\n"
                   "overwrite the original file, omit the --keep-original flag.\n");
            exit(EXIT_FAILURE);
        }
    }
    
    if(key_provided) {

        // Handle hex keys that start with "0x"
        if(!strncmp(key_str, "0x", 2)) {
            char hex_key[ENCRYPT_MAX_KEY_LENGTH];
            strncpy(hex_key, &key_str[2], ENCRYPT_MAX_KEY_LENGTH - 2);
            key_word = (uint64_t)strtoull(hex_key, NULL, 16);

        // Handle ASCII keys
        } else {
            for (size_t i = 0; i < 8; i++) {
                if (key_str[i] == '\0') {
                    break;
                }
                key_word <<= 8;
                key_word += (uint8_t)key_str[i] << 1;
            }

            if (!decrypt) {
                printf("WARNING! Keys made up of only ASCII characters are weaker\n"
                       "than those which utilize the entire byte. Consider providing\n"
                       "the key in the form of a hexcode: 0x...\n");
            }
        }

    } else if (!decrypt) {

        // Generate random key
        srand((uint16_t)time(NULL));
        key_word += (uint64_t)rand() << 48;
        key_word += (uint64_t)rand() << 32;
        key_word += (uint64_t)rand() << 16;
        key_word += (uint64_t)rand();

        printf("KEY: 0x%lx\n", key_word);
        
    } else {
        encrypt_print_error();
        printf("Must provide a key for decryption. \n");
        exit(EXIT_FAILURE);
    }

    // Generate temporary output file
    srand((uint16_t)time(NULL));
    do {
        char numbers[10];
        snprintf(numbers, 10, "%i", rand());
        strncat(out_temp_name, numbers, 10);
    } while (!access(out_temp_name, F_OK));
    temp_output = fopen(out_temp_name, "wb");

    if (!temp_output) {
        encrypt_print_error();
        printf("Failed to open a temporary output file for writing.\n");
        exit(EXIT_FAILURE);
    }

    uint64_t rnd_keys[16] = {0};
    DES_generate_round_keys(rnd_keys, key_word);

    if (decrypt) {
        DES_decrypt_file(input, temp_output, rnd_keys);
    } else {
        DES_encrypt_file(input, temp_output, rnd_keys);
    }

    fclose(input);
    fclose(temp_output);

    if (!keep_original_flag) {
        remove(in_filename);
    }

    if (!out_filename_provided) {
        strncpy(out_filename, in_filename, ENCRYPT_FILE_NAME_LENGTH);
    }

    rename(out_temp_name, out_filename);
    exit(EXIT_SUCCESS);   
}
