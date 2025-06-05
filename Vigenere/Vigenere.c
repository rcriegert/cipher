#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* TODO - Define 0x61 & such in macros */
/* TODO - Make a Vigenere.h file */

unsigned char* to_lower_and_capital_bit_array(unsigned char* array, int len) {
    unsigned char* bit_array = malloc(sizeof(unsigned char) * (len/4 + 1));
    unsigned char bit = 0x01;
    int i;
    for (i = 0; i < len; i++) {
        if (array[i] >= 0x41 && array[i] <= 0x5A) {
            array[i] += 0x20;
            bit_array[i/8] |= bit;
        }
        bit <<= 1;
        if (bit == 0x00) {
            bit = 0x01;
        }
    }
    return bit_array;
}

void to_upper_bit_array(unsigned char* array, unsigned char* bit_array, int len) {
    unsigned char bit = 0x01;
    int i;
    for (i = 0; i < len; i++) {
        if (bit & bit_array[i/8]) {
            array[i] -= 0x20;
        }
        bit <<= 1;
        if (bit == 0x00) {
            bit = 0x01;
        }
    }
}

unsigned char* vigenere_encrypt(unsigned char* plaintext, unsigned char* key, int text_len, int key_len) {
    unsigned char* ciphertext = malloc(sizeof(unsigned char) * text_len);
    int key_index = 0;
    int i;
    for (i = 0; i < text_len; i++) {
        ciphertext[i] = plaintext[i] + key[key_index] - 0x61;
        if (ciphertext[i] > 0x7A) {
            ciphertext[i] -= 26;
        }

        key_index++;
        if (key_index >= key_len) {
            key_index = 0;
        }
    }

    return ciphertext;
}

unsigned char* vigenere_decrypt(unsigned char* ciphertext, unsigned char* key, int text_len, int key_len) {
    unsigned char* plaintext = malloc(sizeof(unsigned char) * text_len);
    int key_index = 0;
    int i;
    for (i = 0; i < text_len; i++) {
        plaintext[i] = ciphertext[i] - key[key_index] + 0x61;
        if (plaintext[i] < 0x61) {
            plaintext[i] += 26;
        }

        key_index++;
        if (key_index >= key_len) {
            key_index = 0;
        }
    }

    return plaintext;
}

/* arg1 = key, arg2 = ciphertext */
int vigenere(int argc, char** argv)
{

    unsigned char* key = argv[1];
    unsigned char* plaintext = argv[2];

    int key_len = strlen(key);
    int text_len = strlen(plaintext);


    unsigned char* bit_array = to_lower_and_capital_bit_array(plaintext, text_len);

    unsigned char* ciphertext = vigenere_encrypt(plaintext, key, text_len, key_len);
    unsigned char* new_plaintext = vigenere_decrypt(ciphertext, key, text_len, key_len);

    to_upper_bit_array(ciphertext, bit_array, text_len);

    printf("%s\n%s\n%s\n%s\n", key, plaintext, ciphertext, new_plaintext);

    free(bit_array);
    free(ciphertext);
    free(new_plaintext);


    return 0;
}
