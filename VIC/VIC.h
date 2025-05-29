#ifndef VIC_H_INCLUDED
#define VIC_H_INCLUDED

/* TODO - write something here */
int** vic_creation_straddle_pa1_pa2(int personal_number, int date_number[], unsigned char phrase[], int keygroup_number[], int* pa1, int* pa2);

/* TODO - write something here */
int* vic_encrypt(unsigned char plaintext[], int personal_number, int date_number[], unsigned char phrase[], int keygroup_number[], unsigned char straddle_alphabet[], int* len_ptr);

/* TODO - write something here */
unsigned char* vic_decrypt(int ciphertext[], int personal_number, int date_number[], unsigned char phrase[], unsigned char straddle_alphabet[], int* len_ptr);

#endif /* VIC_H_INCLUDED */
