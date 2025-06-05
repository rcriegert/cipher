/* Simple Mono-Alphabetic Substitution Cipher */

#include "MAS.h"
/* TODO - Define 0x61 in macro */
/* TODO - test; may be wrong */

/* TODO - write something here */
/* TODO - make this look nice, clean up, etc */
unsigned char* mas_encrypt(unsigned char plaintext[], unsigned char alphabet[], int len) {
    int i;
    unsigned char* ciphertext = malloc(len * sizeof(unsigned char));
    if (ciphertext == NULL) {
        /* TODO - Send back an actual error (somehow) */
        printf("ERROR - UNABLE TO ALLOCATE MEMORY");
        return NULL;
    }
    /* TODO - Make bit array, convert plaintext to uppercase (re-use Vigenere code) */
    for (i = 0; i < len; i++) {
        unsigned char letter_to_convert = plaintext[i];
        ciphertext[i] = alphabet[letter_to_convert - 0x61];
    }
    /* TODO - Undo bit array */
    return ciphertext;
}

/* TODO - write something here */
/* TODO - make this look nice, clean up, etc */
unsigned char* mas_decrypt(unsigned char ciphertext[], unsigned char alphabet, int len) {
    int i;
    int j;
    unsigned char* ciphertext = malloc(len * sizeof(unsigned char));
    if (plaintext == NULL) {
        /* TODO - Send back an actual error (somehow) */
        printf("ERROR - UNABLE TO ALLOCATE MEMORY");
        return NULL;
    }
    /* TODO - Make bit array, convert plaintext to uppercase (re-use Vigenere code) */
    for (i = 0; i < len; i++) {
        for (j = 0; j < 26; j++) {
            if (ciphertext[i] == alphabet[j]) {
                plaintext[i] = j + 0x61;
            }
        }
    }
    /* TODO - Undo bit array */
    return plaintextt;
}

