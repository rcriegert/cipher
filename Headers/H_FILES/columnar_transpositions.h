#ifndef COLUMNAR_TRANSPOSITIONS_H_INCLUDED
#define COLUMNAR_TRANSPOSITIONS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

/* TODO - write something here */
unsigned char* unkeyed_columnar_transposition_uc(unsigned char plaintext[], int plaintext_len, int column_count);

/* TODO - write something here */
unsigned char* keyed_columnar_transposition_uc(unsigned char plaintext[], int plaintext_len, int key[], int key_len);

/* TODO - write something here */
int* keyed_columnar_transposition_int(int* plaintext, int plaintext_len, int* key, int key_len);

/* TODO - write something here */
/* TODO - rename function*/
int* offset_columns_int(int* plaintext, int plaintext_len, int* offset, int offset_len, int column_count);

#endif /* COLUMNAR_TRANSPOSITIONS_H_INCLUDED */
