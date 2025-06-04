#include "../H_FILES/straddle_checkerboard.h"

void straddle_char_encode(unsigned char character, unsigned char ciphertext[], int* len_ptr, int straddle_line[], unsigned char straddle_alphabet[], int straddle_space_1, int straddle_space_2) {
    int i;
    for (i = 0; i < 10; i++) {
        if (straddle_alphabet[i] == character) {
            ciphertext[*len_ptr] = straddle_line[i];
            *len_ptr += 1;
            return;
        }
    }
    for (i = 10; i < 30; i++) {
        if (straddle_alphabet[i] == character) {
            if (i >= 20) {
                ciphertext[*len_ptr] = straddle_line[straddle_space_2];
            }
            else {
                ciphertext[*len_ptr] = straddle_line[straddle_space_1];
                }
            ciphertext[*len_ptr + 1] = straddle_line[i%10];
        }
    }
    *len_ptr += 2;
    return;
}

int straddle_char_decode(int num1, int num2, unsigned char plaintext[], int* len_ptr, int straddle_line[], unsigned char straddle_alphabet[], int straddle_space_1, int straddle_space_2) {
    // Returns -1 if cannot decode correctly, otherwise length of decoded section (of ciphertext, plaintext is always 1)
    int i;
    // If len 1
    if (num1 != straddle_line[straddle_space_1] && num1 != straddle_line[straddle_space_2]) {
        for (i = 0; i < 10; i++) {
            if (straddle_line[i] == num1) {
                plaintext[*len_ptr] = straddle_alphabet[i];
                *len_ptr += 1;
                return 1;
            }
        }
        return -1;
    }
    // If len 2
    for (i = 0; i < 10; i++) {
        if (num2 == straddle_line[i]) {
            if (num1 == straddle_line[straddle_space_1]) {
                plaintext[*len_ptr] = straddle_alphabet[10 + i];
            }
            else {
                plaintext[*len_ptr] = straddle_alphabet[20 + i];
            }
            *len_ptr += 1;
            return 2;
        }
    }
    return -1;
}

unsigned char* straddle_checkerboard_encode(unsigned char plaintext[], int straddle_line[], unsigned char straddle_alphabet[], int* len_ptr) {
    /* Assumes top line does not have / or . */
    /* Assumes plaintext has only letters & numbers */
    /* TODO - Rename len_ptr/pos/original_len variables so they make more sense */
    /* TODO - clean up variable declaration */

    int i;

    /* Grab straddle space start */
    int straddle_space_1 = -1;
    int straddle_space_2;
    for (i = 0; i < 10; i++) {
        if (straddle_alphabet[i] == ' ') {
            if (straddle_space_1 == -1) {
                straddle_space_1 = i;
            }
            else {
                straddle_space_2 = i;
            }
        }
    }
    /* Grab straddle space end */

    /* Encode with Straddle Start */
    unsigned char* ciphertext = malloc(*len_ptr * 2 * sizeof(unsigned char));
    if (ciphertext == NULL) {
        /* TODO - Send back an actual error (somehow) */
        printf("ERROR - UNABLE TO ALLOCATE MEMORY");
        return NULL;
    }
    int pos = 0;
    int original_len = *len_ptr;
    *len_ptr *= 2;

    /* Main Loop */
    int number = 0;
    for (i = 0; i < original_len; i++) {
        /* Realloc check */
        if (pos + 5 >= *len_ptr) {
            /* TODO - Add realloc successful check */
            unsigned char* temp_alloc = realloc(ciphertext, *len_ptr * 2 * sizeof(unsigned char));
            if (temp_alloc == NULL) {
                free(ciphertext);
                /* TODO - Send back an actual error (somehow) */
                printf("ERROR - UNABLE TO ALLOCATE MEMORY");
                return NULL;
            }
            ciphertext = temp_alloc;
            *len_ptr *= 2;
        }

        /* If not number */
        if ((plaintext[i] >= 65 && plaintext[i] <= 90) || (plaintext[i] == 46 || plaintext[i] == 47)) {
            /* If was previously number */
            if (number == 1) {
                straddle_char_encode('/', ciphertext, &pos, straddle_line, straddle_alphabet, straddle_space_1, straddle_space_2);
                number = 0;
            }
            straddle_char_encode(plaintext[i], ciphertext, &pos, straddle_line, straddle_alphabet, straddle_space_1, straddle_space_2);
        }
        /* If number */
        else {
            /* If was not previously number */
            if (number == 0) {
                straddle_char_encode('/', ciphertext, &pos, straddle_line, straddle_alphabet, straddle_space_1, straddle_space_2);
                number = 1;
            }
            ciphertext[pos] = plaintext[i];
            ciphertext[pos+1] = plaintext[i];
            ciphertext[pos+2] = plaintext[i];
            pos += 3;
        }
    }

    /* Encode with Straddle End */
    *len_ptr = pos;
    return ciphertext;
}

unsigned char* straddle_checkerboard_decode(int ciphertext[], int straddle_line[], unsigned char straddle_alphabet[], int* len_ptr) {
    /* TODO - re-write this section? Is it correct? Just copy-paste... */
    /* Assumes top line does not have / or . */
    /* Assumes plaintext has only letters & numbers */
    /* TODO - Rename len_ptr/pos/original_len variables so they make more sense */
    /* TODO - clean up variable declaration */

    int i;
    int number;

    /* Grab straddle space start */
    int straddle_space_1 = -1;
    int straddle_space_2;
    for (i = 0; i < 10; i++) {
        if (straddle_alphabet[i] == ' ') {
            if (straddle_space_1 == -1) {
                straddle_space_1 = i;
            }
            else {
                straddle_space_2 = i;
            }
        }
    }
    /* Grab straddle space end */

    int original_len = *len_ptr;
    unsigned char* plaintext = malloc(*len_ptr * sizeof(unsigned char));
    if (plaintext == NULL) {
        /* TODO - Send back an actual error (somehow) */
        printf("ERROR - UNABLE TO ALLOCATE MEMORY");
        return NULL;
    }

    i = 0;
    number = 0;
    *len_ptr = 0;
    while (i < original_len - 1) {
        if (number == 0) {
            int return_val = straddle_char_decode(ciphertext[i], ciphertext[i+1], plaintext, len_ptr, straddle_line, straddle_alphabet, straddle_space_1, straddle_space_2);
            if (return_val != -1) {
                if (plaintext[i] == '/') {
                    *len_ptr -= 1;
                    number = 1;
                    i += 2;
                }
                else {
                    i += return_val;
                }
            }
            else {
                free(plaintext);
                return NULL;
            }
        }
        else {
            /* if it is a number, ciphertext[i] == ciphertext[i+1] == ciphertext[i+2] */
            /* if it is ending, ciphertext[i] != ciphertext[i+1] because layer 2 on straddle is not a double */
            if (ciphertext[i] != ciphertext[i+1]) {
                i += 3;
                number = 0;
            }
            else {
                int return_val = straddle_char_decode(ciphertext[i], ciphertext[i+1], plaintext, len_ptr, straddle_line, straddle_alphabet, straddle_space_1, straddle_space_2);
                if (return_val != 1) {
                    if (plaintext[i] == '/') {
                        *len_ptr -= 1;
                        number = 0;
                        i += 2;
                    }
                    else {
                        free(plaintext);
                        return NULL;
                    }
                }
                else {
                    free(plaintext);
                    return NULL;
                }
            }
        }
    }
    if (i != original_len) {
        /* Double-sends i, because if this runs the last character is a single */
        int return_val = straddle_char_decode(ciphertext[i], ciphertext[i], plaintext, len_ptr, straddle_line, straddle_alphabet, straddle_space_1, straddle_space_2);
        if (return_val != 1) {
            free(plaintext);
            return NULL;
        }
    }

    return plaintext;
}

