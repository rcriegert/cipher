#ifndef STRADDLE_CHECKERBOARD_H_INCLUDED
#define STRADDLE_CHECKERBOARD_H_INCLUDED

#include <stdlib.h>

/* TODO - write something here */
void straddle_char_encode(unsigned char character, unsigned char ciphertext[], int* len_ptr, int straddle_line[], unsigned char straddle_alphabet[], int straddle_space_1, int straddle_space_2);

/* TODO - write something here */
int straddle_char_decode(int num1, int num2, unsigned char plaintext[], int* len_ptr, int straddle_line[], unsigned char straddle_alphabet[], int straddle_space_1, int straddle_space_2);

/* TODO - write something here */
/* TODO - make it return int* instead and you have to do other stuff like remove the atoi after in vic its a bit too much jumping around so thats why past you didnt do it (: */
unsigned char* straddle_checkerboard_encode(unsigned char plaintext[], int straddle_line[], unsigned char straddle_alphabet[], int* len_ptr);

/* TODO - write something here */
unsigned char* straddle_checkerboard_decode(int ciphertext[], int straddle_line[], unsigned char straddle_alphabet, int* len_ptr);

#endif /* STRADDLE_CHECKERBOARD_H_INCLUDED */
