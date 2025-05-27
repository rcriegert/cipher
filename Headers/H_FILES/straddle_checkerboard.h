#ifndef STRADDLE_CHECKERBOARD_H_INCLUDED
#define STRADDLE_CHECKERBOARD_H_INCLUDED

/* TODO - write something here */
unsigned char* straddle_checkerboard_callback(unsigned char plaintext[], int plaintext_len, int straddle_line[], unsigned char straddle_alphabet[], int straddle_space_1, int straddle_space_2, int* ciphertext_len, unsigned char* (*callback)(unsigned char[], int, int[], unsigned char[], int, int, int*));

/* TODO - write something here */
unsigned char* straddle_checkerboard(unsigned char plaintext[], int plaintext_len, int straddle_line[], unsigned char straddle_alphabet[], int straddle_space_1, int straddle_space_2, int* ciphertext_len);

#endif /* STRADDLE_CHECKERBOARD_H_INCLUDED */
