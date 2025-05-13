#include <stdio.h>
#include <stdlib.h>

#ifndef COLUMNAR_TRANSPOSITIONS_H_INCLUDED
#define COLUMNAR_TRANSPOSITIONS_H_INCLUDED

unsigned char* unkeyed_columnar_transposition_uc(unsigned char plaintext[], int plaintext_len, int column_count) {
    // TODO - Bounds check column_count
    // TODO - safe malloc

    int curr_row = 0;
    int curr_col = 0;
    unsigned char* ciphertext = (unsigned char*)malloc(plaintext_len * sizeof(unsigned char));
    for (int i = 0; i < plaintext_len; i++) {
        if ((curr_row * column_count) + curr_col >= plaintext_len) {
            curr_col++;
            curr_row = 0;
        }
        ciphertext[i] = plaintext[(curr_row * column_count) + curr_col];
        curr_row++;
    }
    return ciphertext;
}



// Assumes key is already in order numbered: 0 -> len - 1
// TODO - FIX! ! ! KEYING IS OTHER WAY AROUND
unsigned char* keyed_columnar_transposition_uc(unsigned char plaintext[], int plaintext_len, int key[], int key_len) {
    // TODO - Check if key[] is set up correctly
    // TODO - safe malloc

    int curr_row = 0;
    int curr_key_index = 0;
    unsigned char* ciphertext = (unsigned char*)malloc(plaintext_len * sizeof(unsigned char));
    for (int i = 0; i < plaintext_len; i++) {
        if ((curr_row * key_len) + key[curr_key_index] >= plaintext_len) {
            curr_key_index++;
            curr_row = 0;
        }
        ciphertext[i] = plaintext[(curr_row * key_len) + key[curr_key_index]];
        curr_row++;
    }
    return ciphertext;
}

// TODO - Add unkeyed int


// TODO - Fix it, it is Broken
// Assumes key is already in order numbered: 0 -> len - 1
int* keyed_columnar_transposition_int(int* plaintext, int plaintext_len, int* key, int key_len) {
    // TODO - Check if key[] is set up correctly
    // TODO - safe malloc

    int curr_row = 0;
    int curr_key_index = 0;
    int curr_key_num = 0;
    for (int i = 0; i < key_len; i++) {
        if (key[i] == curr_key_num) {
            curr_key_index = i;
        }
    }

    int* ciphertext = (int*)malloc(plaintext_len * sizeof(int));
    for (int i = 0; i < plaintext_len; i++) {
        if ((curr_row * key_len) + curr_key_index >= plaintext_len) {
            curr_key_num++;
            for (int j = 0; j < key_len; j++) {
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

#endif // COLUMNAR_TRANSPOSITIONS_H_INCLUDED
