#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include "DES.h"

#define ENCRYPT_FILE_NAME_LENGTH 256
#define ENCRYPT_TEMP_NAME_SEED 42
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

uint8_t encrypt_byte(uint8_t b, uint8_t key_byte) {
    // TODO
    return b^key_byte;
}

uint8_t decrypt_byte(uint8_t b, uint8_t key_byte) {
    // TODO
    return b^key_byte;
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
         key[ENCRYPT_MAX_KEY_LENGTH];

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
                strncpy(key, optarg, ENCRYPT_MAX_KEY_LENGTH);
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

    // Generate temporary output file
    srand(ENCRYPT_TEMP_NAME_SEED);
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

    uint8_t key_byte = 0;
    for (int16_t i = 0; key[i] != '\0'; i++) {
        key_byte ^= key[i];        
    }
    
    //TODO create a random key if one is not provided

    int byte;
    while ((byte = fgetc(input)) != EOF) {
        if (decrypt) {
            fputc(decrypt_byte(byte, key_byte), temp_output);
        } else {
            fputc(encrypt_byte(byte, key_byte), temp_output);
        }
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
