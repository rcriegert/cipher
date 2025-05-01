#ifndef STRADDLE_CHECKERBOARD_H_INCLUDED
#define STRADDLE_CHECKERBOARD_H_INCLUDED

unsigned char* straddle_checkerboard(unsigned char plaintext[], int plaintext_len, unsigned char straddle_alphabet[], int straddle_space_1, int straddle_space_2) {
    // TODO - Add in line_H_P 50-59

    // Straddling Checkerboard Top Line Creation Start
    int pos;
    int num;
    int straddle_line[10];
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
        straddle_line[pos - 50] = i;
    }
    // Straddling Checkerboard Top Line Creation End



    // Encode with Straddle Start
    unsigned char* ciphertext = malloc(plaintext_len * 2 * sizeof(unsigned char));
    pos = 0;
    int ciphertext_size = plaintext_len * 2;
    int completed_loop;
    // Add number support
    for (int i = 0; i < plaintext_len; i++) {
        completed_loop = 0;
        // Realloc check
        if (pos + 5 >= ciphertext_size) {
            // TODO - realloc double
        }

        // check row

        for (int j = 0; j < 8; j++) {
            if (plaintext[i] == straddle_alphabet[j]) {
                int addition = 0;
                if (j >= straddle_space_1) {
                    addition++;
                }
                if (j >= straddle_space_2) {
                    addition++;
                }
                ciphertext[pos] = straddle_line[j + addition];
                pos++;
                completed_loop = 1;
            }
        }
        if (completed_loop == 0) {
            if ((plaintext[i] >= 65 && plaintext[i] <= 90) || (plaintext[i] == 46 || plaintext[i] == 47)) {
                // add support if currently number
                // if upper alphabet not top row or . or /
                for (int j = 8; j < 28; j++) {
                    if (plaintext[i] == straddle_alphabet[j]) {
                        if (j >= 18) {
                            ciphertext[pos] = straddle_space_1;
                        }
                        else {
                            ciphertext[pos] = straddle_space_2;
                        }
                        pos++;
                        ciphertext[pos] = straddle_line[(j-8)%10];
                        pos++;
                    }
                }
            }
            // introducing number
        }

    }
    // Encode with Straddle End
}

#endif // STRADDLE_CHECKERBOARD_H_INCLUDED
