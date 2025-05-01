#ifndef STRADDLE_CHECKERBOARD_H_INCLUDED
#define STRADDLE_CHECKERBOARD_H_INCLUDED

unsigned char* straddle_checkerboard(unsigned char plaintext[], int plaintext_len, unsigned char straddle_alphabet[], int straddle_space_1, int straddle_space_2) {
    // NEED TO BRING IN line_H_P 50-59

    // Straddling Checkerboard Creation Start
    int pos;
    int num;
    int line_Straddle[10];
    for (int i = 0; i < 10; i++) {
        pos = 0;
        num = 10;
        for (int j = 50; j < 60; j++) {
            if (line_H_P[j] < num) {
                pos = j;
                num = line_H_P[j];
            }
        }
        line_H_P[pos] += 10;
        line_Straddle[pos - 50] = i;
    }

    // Top Row
    int straddle_array[28];
    int counter = 0;
    for (int i = 0; i < 10; i++) {
        if (i != straddle_space_1 && i != straddle_space_2) {
            straddle_array[counter] = line_Straddle[i];
            counter++;
        }
    }
    // Middle Row
    for (int i = 0; i < 10; i++) {
        straddle_array[i+8] = (straddle_space_1*10) + i;
    }
    // Bottom Row
    for (int i = 0; i < 10; i++) {
        straddle_array[i+18] = (straddle_space_2*10) + i;
    }
    // Straddling Checkerboard Creation End



    // Encode with Straddle Start
    unsigned char* ciphertext = malloc(plaintext_len * 2 * sizeof(unsigned char));
    pos = 0;
    int ciphertext_size = plaintext_len * 2;
    unsigned char number = 0;
    for (int i = 0; i < plaintext_len; i++) {
        // check row
        int len = 1;
        for (int j = 0; j < 8; j++) {
            if (plaintext[i] == straddle_alphabet[j]) {
                len++;
            }
        }
        // TODO - check number
        // Add to straddle TODO - Support number
        if (pos + len >= ciphertext_size) {
            // TODO - realloc double
        }
        // Add straddle to ciphertext (WHAT IS BEST WAY?!??!?!)

    }
    // Encode with Straddle End
}

#endif // STRADDLE_CHECKERBOARD_H_INCLUDED
