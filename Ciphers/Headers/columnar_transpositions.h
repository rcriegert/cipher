#include <stdio.h>
#include <stdlib.h>

#ifndef COLUMNAR_TRANSPOSITIONS_H_INCLUDED
#define COLUMNAR_TRANSPOSITIONS_H_INCLUDED

unsigned char* unkeyed_columnar_transposition_uc(unsigned char plaintext[], int plaintext_len, int column_count) {
    // TODO - Bounds check column_count
    // TODO - safe malloc

    int current_row = 0;
    int current_col = 0;
    unsigned char* ciphertext = (unsigned char*)malloc(plaintext_len * sizeof(unsigned char));
    for (int i = 0; i < plaintext_len; i++) {
        if ((current_row * column_count) + current_col >= plaintext_len) {
            current_col++;
            current_row = 0;
        }
        ciphertext[i] = plaintext[(current_row * column_count) + current_col];
        current_row++;
    }
    return ciphertext;
}

#endif // COLUMNAR_TRANSPOSITIONS_H_INCLUDED
