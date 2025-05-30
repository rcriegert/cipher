#include "../H_FILES/columnar_transpositions.h"

unsigned char* columnar_transposition_unkeyed_encode_uc(unsigned char plaintext[], int plaintext_len, int column_count) {
    /* TODO - Bounds check column_count */
    /* TODO - safe malloc */

    int curr_row = 0;
    int curr_col = 0;
    unsigned char* ciphertext = (unsigned char*)malloc(plaintext_len * sizeof(unsigned char));
    int i;
    for (i = 0; i < plaintext_len; i++) {
        if ((curr_row * column_count) + curr_col >= plaintext_len) {
            curr_col++;
            curr_row = 0;
        }
        ciphertext[i] = plaintext[(curr_row * column_count) + curr_col];
        curr_row++;
    }
    return ciphertext;
}



/* Assumes key is already in order numbered: 0 -> len - 1 */
unsigned char* columnar_transposition_keyed_encode_uc(unsigned char plaintext[], int plaintext_len, int key[], int key_len) {
    /* TODO - Check if key[] is set up correctly */
    /* TODO - safe malloc */

    int curr_row = 0;
    int curr_key_index = 0;
    unsigned char* ciphertext = (unsigned char*)malloc(plaintext_len * sizeof(unsigned char));
    int i;
    for (i = 0; i < plaintext_len; i++) {
        if ((curr_row * key_len) + key[curr_key_index] >= plaintext_len) {
            curr_key_index++;
            curr_row = 0;
        }
        ciphertext[i] = plaintext[(curr_row * key_len) + key[curr_key_index]];
        curr_row++;
    }
    return ciphertext;
}

/* TODO - Add unkeyed int, decodes, etc. */


/* Assumes key is already in order numbered: 0 -> len - 1 */
int* columnar_transposition_keyed_encode_int(int* plaintext, int plaintext_len, int* key, int key_len) {
    /* TODO - Check if key[] is set up correctly */
    /* TODO - safe malloc */

    int curr_row = 0;
    int curr_key_index = 0;
    int curr_key_num = 0;
    int i;
    int j;
    for (i = 0; i < key_len; i++) {
        if (key[i] == curr_key_num) {
            curr_key_index = i;
        }
    }

    int* ciphertext = (int*)malloc(plaintext_len * sizeof(int));
    for (i = 0; i < plaintext_len; i++) {
        if ((curr_row * key_len) + curr_key_index >= plaintext_len) {
            curr_key_num++;
            for (j = 0; j < key_len; j++) {
                if (key[j] == curr_key_num) {
                    curr_key_index = j;
                }
            }
            curr_row = 0;
        }
        ciphertext[i] = plaintext[(curr_row * key_len) + curr_key_index];
        curr_row++;
    }
    return ciphertext;
}
int* columnar_transposition_keyed_decode_int(int* ciphertext, int ciphertext_len, int* key, int key_len){
    /* TODO - Check if key[] is set up correctly */
    /* TODO - safe malloc */


}

/* TODO - this isn't actually transposing, it's re-arranging. Move to a different file, and figure out the name... */
int* offset_columnar_transposition_encode_int(int* plaintext, int plaintext_len, int* offset, int offset_len, int column_count) {
    /* TODO - Check if offset[] is set up correctly */
    /* TODO - safe malloc */

    /* adjustment */
    int* ciphertext = (int*)malloc(plaintext_len * sizeof(int));
    int i;
    int j;
    int curr = 0;
    for (i = 0; i < offset_len; i++) {
        for (j = 0; j < offset[i]; j++) {
            ciphertext[(i*column_count) + j] = plaintext[curr];
            curr++;
        }
    }
    for (i = 0; i < offset_len; i++) {
        for (j = offset[i]; j < column_count; j++) {
            if (curr < plaintext_len) {
                ciphertext[(i*column_count) + j] = plaintext[curr];
                curr++;
            }
        }
    }

    return ciphertext;
}

/* TODO - this isn't actually transposing, it's re-arranging. Move to a different file, and figure out the name... */
int* offset_columnar_transposition_decode_int(int* ciphertext, int ciphertext_len, int* offset, int offset_len, int column_count) {
    /* TODO - Check if offset[] is set up correctly */
    /* TODO - safe malloc */
    int* plaintext = (int*)malloc(ciphertext_len * sizeof(int));
    int i;
    int j;
    int curr = 0;
    for (i = offset_len - 1; i >= 0; i--) {
        for (j = column_count - 1; j >= offset[i]; j--) {
            plaintext[curr] = ciphertext[(i*column_count) + j];
            curr++;
        }
    }
    for (i = offset_len - 1; i >= 0; i--) {
        for (j = offset[i] - 1; j >= 0; j--) {
            if (curr < plaintext_len) {
                ciphertext[(i*column_count) + j] = plaintext[curr];
                curr++;
            }
        }
    }

    return plaintext;
}

