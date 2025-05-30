#ifndef COLUMNAR_TRANSPOSITIONS_H_INCLUDED
#define COLUMNAR_TRANSPOSITIONS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

/* TODO - write something here */
unsigned char* columnar_transposition_unkeyed_encode_uc(unsigned char plaintext[], int plaintext_len, int column_count);

/* TODO - write something here */
unsigned char* columnar_transposition_keyed_encode_uc(unsigned char plaintext[], int plaintext_len, int key[], int key_len);

/* TODO - write something here */
int* columnar_transposition_keyed_encode_int(int* plaintext, int plaintext_len, int* key, int key_len);
int* columnar_transposition_keyed_decode_int(int* ciphertext, int ciphertext_len, int* key, int key_len);

/* TODO - write something here */
/* TODO - rename function maybe? */
int* offset_columnar_transposition_encode_int(int* plaintext, int plaintext_len, int* offset, int offset_len, int column_count);

/* TODO - write something here */
/* TODO - rename function maybe? */
int* offset_columnar_transposition_decode_int(int* ciphertext, int ciphertext_len, int* offset, int offset_len, int column_count);

#endif /* COLUMNAR_TRANSPOSITIONS_H_INCLUDED */
