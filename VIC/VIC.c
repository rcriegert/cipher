// VIC Cipher
// Notation from https://en.wikipedia.org/wiki/VIC_cipher
// Additional information from http://www.quadibloc.com/crypto/pp1324.htm

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Headers/chain_addition.h"
#include "../Headers/straddle_checkerboard.h"

// TODO - Make this accept passed arguments
int vic() {
    // Starting Information
    // TODO - Can I move allocations/instantiations up?
    int personal_number = 8;
    int date_number[] = {7, 4, 1, 7, 7, 6};
    unsigned char phrase[] = "IDREAMOFJEANNIEWITHT";
    // TODO - Write code to break the phrase into two parts - do I? Can I just use the first?
    unsigned char phrase_1[] = "IDREAMOFJE";
    unsigned char phrase_2[] = "ANNIEWITHT";
    int keygroup_number[] = {7, 7, 6, 5, 1};
    int line_F[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    unsigned char straddle_alphabet[] = "ATONESIRBCDFGHJKLMPQUVWXYZ./";
    // TODO - Derive these from straddle_alphabet (how?)
    // Note - Indexed at 0
    // Note - ss1 < ss2
    int straddle_space_1 = 2;
    int straddle_space_2 = 6;
    unsigned char* plaintext = "WEAREPLEASEDTOHEAROFYOURSUCCESSINESTABLISHINGYOURFALSEIDENTITYYOUWILLBESENTSOMEMONEYTOCOVEREXPENSESWITHINAMONTH";

    // Line F Start

    for (int i = 0; i < 5; i++) {
        if (keygroup_number[i] < date_number[i]) {
            line_F[i] += 10;
        }
        line_F[i] += keygroup_number[i];
        line_F[i] -= date_number[i];
    }
    chain_addition(line_F, 5, 10, 10);

    // Line F End

    // Line E Start

    // Note - could make into 1 array, and maybe not separate phrase either?
    // Note - phrase messed up by +26 after this section
    // Note - phrase must be all one case, no spaces/special symbols

    int pos;
    int num;
    int e_1[10];
    for (int i = 1; i < 11; i++) {
        pos = 0;
        num = 0x7A;
        for (int j = 0; j < 10; j++) {
            if (phrase_1[j] < num) {
                pos = j;
                num = phrase_1[j];
            }
        }
        phrase_1[pos] += 26;
        e_1[pos] = i%10;
    }
    int e_2[10];
    for (int i = 1; i < 11; i++) {
        pos = 0;
        num = 0x7A;
        for (int j = 0; j < 10; j++) {
            if (phrase_2[j] < num) {
                pos = j;
                num = phrase_2[j];
            }
        }

        phrase_2[pos] += 26;
        e_2[pos] = i%10;
    }

    // Line E End

    // Line G Start

    int line_G[10];
    for (int i = 0; i < 10; i++) {
        line_G[i] = (e_1[i] + line_F[i]) % 10;
    }

    // Line G End

    // Lines H-P start

    int line_H_P[60];
    for (int i = 0; i < 10; i++) {
        int j = line_G[i] - 1;
        if (j == -1) {
            j = 9;
        }
        line_H_P[i] = e_2[j];
    }

    chain_addition(line_H_P, 10, 60, 10);

    // Lines H-P End

    // Line J Start

    int line_J[10];
    for (int i = 0; i < 10; i++) {
        pos = 0;
        num = 10;
        for (int j = 0; j < 10; j++) {
            if (line_H_P[j] < num) {
                pos = j;
                num = line_H_P[j];
            }
        }
        line_H_P[pos] += 10;
        line_J[pos] = i;
        if (line_J[pos] == 0) {
            line_J[pos] = 10;
        }
    }
    // To revert changes in H_P (all + 10)
    for (int i = 0; i < 10; i++) {
        line_H_P[i] -= 10;
    }

    // Line J End

    // Permutation Keys Start
    // TODO - refactor variable names to pk1/2, maybe?

    int pa1;
    int pa2 = line_H_P[59];
    int neq = 1;
    int index = 58;
    while (neq == 1) {
        if (line_H_P[index] != pa2) {
            pa1 = line_H_P[index];
            neq = 0;
        }
        index--;
    }
    pa1 += personal_number;
    pa2 += personal_number;

    // Permutation Keys End

    // Allocations for Q, R
    int* line_Q_R = malloc(sizeof(int) * (pa1 + pa2));
    int* line_Q_R_Sequenced = malloc(sizeof(int) * (pa1 + pa2));

    // Lines Q-R Start

    int column_index;
    int column_number = 1;
    for (int i = 0; i < 10; i++) {
        if (line_J[i] == column_number) {
            column_index = i;
        }
    }
    int row_index = 0;
    for (int i = 0; i < pa1 + pa2; i++) {
        line_Q_R[i] = line_H_P[10 + ((10 * row_index) + column_index)];
        if (line_Q_R[i] == 0) {
            line_Q_R[i] = 10;
        }
        row_index++;
        if (row_index == 5) {
            row_index = 0;
            column_number++;
            for (int j = 0; j < 10; j++) {
                if (line_J[j] == column_number) {
                    column_index = j;
                }
            }
        }
    }

    // Lines Q-R End

    // Lines Q-R Sequencing Start

    for (int i = 1; i < pa1 + 1; i++) {
        pos = 0;
        num = 11;
        for (int j = 0; j < pa1; j++) {
            if (line_Q_R[j] < num) {
                pos = j;
                num = line_Q_R[j];
            }
        }
        line_Q_R[pos] += 10;
        line_Q_R_Sequenced[pos] = i;
    }
    for (int i = pa1 + 1; i < pa1 + pa2 + 1; i++) {
        pos = 0;
        num = 11;
        for (int j = pa1; j < pa1 + pa2; j++) {
            if (line_Q_R[j] < num) {
                pos = j;
                num = line_Q_R[j];
            }
        }
        line_Q_R[pos] += 10;
        line_Q_R_Sequenced[pos] = i - pa1;
    }
    // To revert changes in Q_R (all + 10)
    for (int i = 0; i < pa1 + pa2; i++) {
        line_Q_R[i] -= 10;
    }

    // Lines Q-R Sequencing End



    // Encode with Straddle Start
    int ciphertext_len;

    unsigned char* text_after_straddle = straddle_checkerboard_callback(plaintext, strlen(plaintext), &(line_H_P[50]), straddle_alphabet, straddle_space_1, straddle_space_2, &ciphertext_len, straddle_checkerboard);

    // Encode with Straddle End
    for (int i = 0; i < ciphertext_len; i++) {
        printf("%d ", text_after_straddle[i]);
    }


    // Cleanup

    free(text_after_straddle);
    free(line_Q_R_Sequenced);
    free(line_Q_R);

    return 0;
}
