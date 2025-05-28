#ifndef VIC_H_INCLUDED
#define VIC_H_INCLUDED

/* TODO - write something here */
int* vic_encrypt(unsigned char plaintext[], int personal_number, int date_number[], unsigned char phrase[], int keygroup_number[], unsigned char straddle_alphabet[], int* len_ptr);

/* TODO - write something here */
int* vic_decrypt(unsigned char ciphertext[], int personal_number, int date_number[], unsigned char phrase[], unsigned char straddle_alphabet[], int* len_ptr);

#endif /* VIC_H_INCLUDED */
