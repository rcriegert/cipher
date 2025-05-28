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
    int pos = 0;
    int original_len = *len_ptr;
    *len_ptr *= 2;

    /* Main Loop */
    int number = 0;
    for (i = 0; i < original_len; i++) {
        /* Realloc check */
        if (pos + 5 >= *len_ptr) {
            unsigned char* temp_alloc;
            /* TODO - Add realloc successful check */
            temp_alloc = realloc(ciphertext, *len_ptr * 2 * sizeof(unsigned char));
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
