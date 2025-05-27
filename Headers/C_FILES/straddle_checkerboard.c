#include "../H_FILES/straddle_checkerboard.h"

unsigned char* straddle_checkerboard_callback(unsigned char plaintext[], int plaintext_len, int straddle_line[], unsigned char straddle_alphabet[], int straddle_space_1, int straddle_space_2, int* ciphertext_len, unsigned char* (*callback)(unsigned char[], int, int[], unsigned char[], int, int, int*)) {
    return callback(plaintext, plaintext_len, straddle_line, straddle_alphabet, straddle_space_1, straddle_space_2, ciphertext_len);
}

unsigned char* straddle_checkerboard(unsigned char plaintext[], int plaintext_len, int straddle_line[], unsigned char straddle_alphabet[], int straddle_space_1, int straddle_space_2, int* ciphertext_len) {
    /* Assumes top line does not have / or . */

    /* Encode with Straddle Start */
    unsigned char* ciphertext = malloc(plaintext_len * 2 * sizeof(unsigned char));
    int pos = 0;
    int ciphertext_size = plaintext_len * 2;
    int completed_loop;
    /* Add number support */
    int number = 0;
    int i;
    int j;
    for (i = 0; i < plaintext_len; i++) {
        completed_loop = 0;
        /* Realloc check */
        if (pos + 5 >= ciphertext_size) {
            unsigned char* temp_alloc;
            /* Add realloc successful check */
            temp_alloc = realloc(ciphertext, ciphertext_size * 2 * sizeof(unsigned char));
            ciphertext = temp_alloc;
            ciphertext_size *= 2;
        }

        /* Check top row */
        for (j = 0; j < 8; j++) {
            if (plaintext[i] == straddle_alphabet[j]) {
                int addition = 0;
                if (j >= straddle_space_1) {
                    addition++;
                }
                if (j >= straddle_space_2 - 1) {
                    addition++;
                }
                ciphertext[pos] = straddle_line[j + addition];
                pos++;
                completed_loop = 1;
            }
        }
        /* Not top row */
        if (completed_loop == 0) {
            /* If upper alphabet not top row or . or / */
            if ((plaintext[i] >= 65 && plaintext[i] <= 90) || (plaintext[i] == 46 || plaintext[i] == 47)) {
                /* add support if currently number */
                if (number == 1) {
                    for (j = 8; j < 28; j++) {
                        if ('/' == straddle_alphabet[j]) {
                            if (j >= 18) {
                                ciphertext[pos] = straddle_line[straddle_space_2];
                            }
                            else {
                                ciphertext[pos] = straddle_line[straddle_space_1];
                            }
                            pos++;
                            ciphertext[pos] = straddle_line[(j-8)%10];
                            pos++;
                        }
                    }
                    number = 0;
                }
                for (j = 8; j < 28; j++) {
                    if (plaintext[i] == straddle_alphabet[j]) {
                        if (j >= 18) {
                            ciphertext[pos] = straddle_line[straddle_space_2];
                        }
                        else {
                            ciphertext[pos] = straddle_line[straddle_space_1];
                        }
                        pos++;
                        ciphertext[pos] = straddle_line[(j-8)%10];
                        pos++;
                    }
                }
            }
            /* Number */
            else {
                if (number == 0) {
                    for (j = 8; j < 28; j++) {
                        if ('/' == straddle_alphabet[j]) {
                            if (j >= 18) {
                                ciphertext[pos] = straddle_space_1;
                            }
                            else {
                                ciphertext[pos] = straddle_space_2;
                            }
                            pos++;
                            ciphertext[pos] = straddle_line[(j-8)%10];
                            pos++;
                        }
                    }
                    number = 1;
                }
                ciphertext[pos] = plaintext[i];
                pos++;
                ciphertext[pos] = plaintext[i];
                pos++;
                ciphertext[pos] = plaintext[i];
                pos++;
            }
        }

    }
    /* Encode with Straddle End */
    *ciphertext_len = pos;
    return ciphertext;
}
