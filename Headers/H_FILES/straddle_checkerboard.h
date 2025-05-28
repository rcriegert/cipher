#ifndef STRADDLE_CHECKERBOARD_H_INCLUDED
#define STRADDLE_CHECKERBOARD_H_INCLUDED

#include <stdlib.h>

/* TODO - write something here */
void straddle_char_encode(unsigned char character, unsigned char ciphertext[], int* len_ptr, int straddle_line[], unsigned char straddle_alphabet[], int straddle_space_1, int straddle_space_2);

/* TODO - write something here */
unsigned char* straddle_checkerboard_encode(unsigned char plaintext[], int straddle_line[], unsigned char straddle_alphabet[], int* len_ptr);

#endif /* STRADDLE_CHECKERBOARD_H_INCLUDED */
