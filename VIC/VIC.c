/* VIC Cipher */
/* Notation from https://en.wikipedia.org/wiki/VIC_cipher */
/* Additional information from http://www.quadibloc.com/crypto/pp1324.htm */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Headers/H_FILES/chain_addition.h"
#include "../Headers/H_FILES/straddle_checkerboard.h"
#include "../Headers/H_FILES/columnar_transpositions.h"
#include "../Headers/H_FILES/sequencing.h"
#include "VIC.h"

/* TODO - rename? maybe send back pa1/pa2 in return array? */
/* TODO - do stuff here (nice looking code, other failure checks, etc.) */
int** vic_creation_straddle_pa1_pa2(int personal_number, int date_number[], unsigned char phrase[], int keygroup_number[], int* pa1_ptr, int* pa2_ptr) {
    /* TODO - Can I move allocations/instantiations up? */
    /* TODO - Clean up comments */

    int i;
    int j;
    int num;
    int pos;


    int line_E[20];
    int line_F[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int line_G[10];
    int line_H_P[60];
    int line_J[10];

    /* Line F */
    for (i = 0; i < 5; i++) {
        if (keygroup_number[i] < date_number[i]) {
            line_F[i] += 10;
        }
        line_F[i] += keygroup_number[i];
        line_F[i] -= date_number[i];
    }
    chain_addition(line_F, 5, 10, 10);

    /* Line E */
    /* Note - could make into 1 array, and maybe not separate phrase either? */
    /* Note - phrase messed up by +26 after this section */
    /* Note - phrase must be all one case, no spaces/special symbols */
    for (i = 1; i < 11; i++) {
        pos = 0;
        num = 0x7A;
        for (j = 0; j < 10; j++) {
            if (phrase[j] < num) {
                pos = j;
                num = phrase[j];
            }
        }
        phrase[pos] += 26;
        line_E[pos] = i%10;
    }
    for (i = 1; i < 11; i++) {
        pos = 10;
        num = 0x7A;
        for (j = 10; j < 20; j++) {
            if (phrase[j] < num) {
                pos = j;
                num = phrase[j];
            }
        }

        phrase[pos] += 26;
        line_E[pos] = i%10;
    }

    /* Line G */
    for (i = 0; i < 10; i++) {
        line_G[i] = (line_E[i] + line_F[i]) % 10;
    }

    /* Lines H-P */
    for (i = 0; i < 10; i++) {
        int j = line_G[i] - 1;
        if (j == -1) {
            j = 9;
        }
        line_H_P[i] = line_E[j+10];
    }

    chain_addition(line_H_P, 10, 60, 10);

    /* Line J */
    for (i = 0; i < 10; i++) {
        pos = 0;
        num = 10;
        for (j = 0; j < 10; j++) {
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
    /* To revert changes in H_P (all + 10) */
    for (i = 0; i < 10; i++) {
        line_H_P[i] -= 10;
    }

    /* Permutation Keys */
    /* TODO - refactor variable names to pk1/2, maybe? */
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

    /* Allocations for Q, R */
    int* line_Q_R = malloc(sizeof(int) * (pa1 + pa2));
    if (line_Q_R == NULL) {
        /* TODO - Send back an actual error (somehow) */
        printf("ERROR - UNABLE TO ALLOCATE MEMORY");
        return NULL;
    }
    int* line_Q_R_Sequenced = malloc(sizeof(int) * (pa1 + pa2));
    if (line_Q_R_Sequenced == NULL) {
        free(line_Q_R);
        /* TODO - Send back an actual error (somehow) */
        printf("ERROR - UNABLE TO ALLOCATE MEMORY");
        return NULL;
    }

    /* Lines Q-R */
    int column_index;
    int column_number = 1;
    for (i = 0; i < 10; i++) {
        if (line_J[i] == column_number) {
            column_index = i;
        }
    }
    int row_index = 0;
    for (i = 0; i < pa1 + pa2; i++) {
        line_Q_R[i] = line_H_P[10 + ((10 * row_index) + column_index)];
        if (line_Q_R[i] == 0) {
            line_Q_R[i] = 10;
        }
        row_index++;
        if (row_index == 5) {
            row_index = 0;
            column_number++;
            for (j = 0; j < 10; j++) {
                if (line_J[j] == column_number) {
                    column_index = j;
                }
            }
        }
    }

    /* Lines Q-R Sequencing */
    for (i = 0; i < pa1; i++) {
        pos = 0;
        num = 11;
        for (j = 0; j < pa1; j++) {
            if (line_Q_R[j] < num) {
                pos = j;
                num = line_Q_R[j];
            }
        }
        line_Q_R[pos] += 10;
        line_Q_R_Sequenced[pos] = i;
    }
    for (i = pa1; i < pa1 + pa2; i++) {
        pos = 0;
        num = 11;
        for (j = pa1; j < pa1 + pa2; j++) {
            if (line_Q_R[j] < num) {
                pos = j;
                num = line_Q_R[j];
            }
        }
        line_Q_R[pos] += 10;
        line_Q_R_Sequenced[pos] = i - pa1;
    }
    /* To revert changes in Q_R (all + 10) */
    for (i = 0; i < pa1 + pa2; i++) {
        line_Q_R[i] -= 10;
    }
    free(line_Q_R);

    /* Straddling Checkerboard Top Line Creation */
    int* straddle_line = malloc(10 * sizeof(int));
    if (straddle_line == NULL) {
        free(line_Q_R_Sequenced);
        /* TODO - Send back an actual error (somehow) */
        printf("ERROR - UNABLE TO ALLOCATE MEMORY");
        return NULL;
    }
    for (i = 0; i < 10; i++) {
        pos = 0;
        num = 10;
        for (j = 0; j < 10; j++) {
            if (line_H_P[j+50] < num) {
                pos = j;
                num = line_H_P[j+50];
            }
        }
        line_H_P[pos+50] += 10;
        straddle_line[pos] = i;
    }
    /* NOTE: Line H_P 50-59 is 10 more than it should be at this point */


    /* Return formatting */
    *pa1_ptr = pa1;
    *pa2_ptr = pa2;
    int** returns = malloc(2*sizeof(int*));
    if (returns == NULL) {
        free(straddle_line);
        free(line_Q_R_Sequenced);
        /* TODO - Send back an actual error (somehow) */
        printf("ERROR - UNABLE TO ALLOCATE MEMORY");
        return NULL;
    }
    returns[0] = line_Q_R_Sequenced;
    returns[1] = straddle_line;

    return returns;
}

/* TODO - do stuff here (safe mallocs, nice looking code, other failure checks, etc.) */
int* vic_encrypt(unsigned char plaintext[], int personal_number, int date_number[], unsigned char phrase[], int keygroup_number[], unsigned char straddle_alphabet[], int* len_ptr) {
    /* TODO - Can I move allocations/instantiations up? */

    int i;
    int num;
    int pos;
    int pa1 = 0;
    int pa2 = 0;

    /* TODO - Separate pa1/pa2 creation? idk */
    int** return_vals = vic_creation_straddle_pa1_pa2(personal_number, date_number, phrase, keygroup_number, &pa1, &pa2);
    int* line_Q_R_Sequenced = return_vals[0];
    int* straddle_line = return_vals[1];

    /* Encode with Straddle Start */
    unsigned char* text_after_straddle = straddle_checkerboard_encode(plaintext, straddle_line, straddle_alphabet, len_ptr);

    /* Re-copy to fixed size */
    int padding = 5 - (*len_ptr % 5);
    int* nums_after_straddle = (int*)malloc((*len_ptr + padding) * sizeof(int));
    for (i = 0; i < *len_ptr; i++) {
        nums_after_straddle[i] = text_after_straddle[i];
    }

    /* Pad to *len_ptr % 5 == 0 */
    /* TODO - make nums_after_straddle additions random(can I do that?) */
    for (i = *len_ptr; i < *len_ptr + padding; i++) {
        nums_after_straddle[i] = 9;
    }
    *len_ptr += padding;

    /* Columnar Transposition 1 (Keyed) */
    int* after_columnar_transposition_1 = columnar_transposition_keyed_encode_int(nums_after_straddle, *len_ptr, line_Q_R_Sequenced, pa1);

    /* Columnar Transposition 2 (Keyed 2-Triangular) */
    int t2_first = 10;
    int t2_second = 10;
    int t2_first_index = 0;
    int t2_second_index = 0;
    for (i = pa1; i < pa1 + pa2; i++) {
        if (line_Q_R_Sequenced[i] < t2_second) {
            if (line_Q_R_Sequenced[i] < t2_first) {
                t2_second = t2_first;
                t2_second_index = t2_first_index;
                t2_first = line_Q_R_Sequenced[i];
                t2_first_index = i - pa1;
            }
            else {
                t2_second = line_Q_R_Sequenced[i];
                t2_second_index = i - pa1;
            }
        }
    }
    int t2_rows = ((int)(*len_ptr / pa2)) + 1;
    int* transpose_table = malloc(t2_rows * sizeof(int));

    pos = 0;
    transpose_table[0] = t2_first_index;
    num = t2_first_index;
    for (i = 1; i < t2_rows; i++) {
        num++;
        if (num > pa2) {
            if (pos == 0) {
                num = t2_second_index;
            }
            else {
                num = pa2;
            }
        }
        transpose_table[i] = num;
    }

    int* t2_after_offset = offset_columnar_transposition_encode_int(after_columnar_transposition_1, *len_ptr, transpose_table, t2_rows, pa2);
    int* ciphertext = columnar_transposition_keyed_encode_int(t2_after_offset, *len_ptr, &(line_Q_R_Sequenced[pa1]), pa2);

    /* Add indicator to ciphertext */
    int group_count = (*len_ptr/5) + 1;
    int indicator_group = group_count - date_number[5];
    int* final_text = (int*)malloc((group_count * 5) * sizeof(int));
    for (i = 0; i < indicator_group * 5; i++) {
        final_text[i] = ciphertext[i];
    }
    for (i = 0; i < 5; i++) {
        final_text[(indicator_group * 5) + i] = keygroup_number[i];
    }
    for (i = indicator_group * 5; i < *len_ptr; i++) {
        final_text[i + 5] = ciphertext[i];
    }

    /* Cleanup */
    free(ciphertext);
    free(t2_after_offset);
    free(transpose_table);
    free(after_columnar_transposition_1);
    free(nums_after_straddle);
    free(text_after_straddle);
    free(line_Q_R_Sequenced);
    free(straddle_line);
    free(return_vals);

    *len_ptr += 5;

    return final_text;
}

/* TODO - do stuff here (safe mallocs, other failure checks, etc.) */
unsigned char* vic_decrypt(int ciphertext[], int personal_number, int date_number[], unsigned char phrase[], unsigned char straddle_alphabet[], int* len_ptr) {
    /* TODO - check that the data being sent is not rubbish */

    /* Simple instantiations */
    int i;
    int num;
    int pos;

    /* Find indicator group */
    int keygroup_number[5];
    int indicator_group = *len_ptr - (date_number[5] * 5);
    for (i = 0; i < 5; i++) {
        keygroup_number[i] = ciphertext[indicator_group + i];
    }

    /* Remove indicator group (It actually copies everything over to the left & overwrites the indicator group, BUT length is changed so in practice it works) */
    for (i = indicator_group; i < *len_ptr - 5; i++) {
        ciphertext[i] = ciphertext[i+5];
    }
    *len_ptr -= 5;

    /* Get straddle line & other general VIC information */
    int pa1;
    int pa2;
    int** return_vals = vic_creation_straddle_pa1_pa2(personal_number, date_number, phrase, keygroup_number, &pa1, &pa2);
    int* line_Q_R_Sequenced = return_vals[0];
    int* straddle_line = return_vals[1];
    int t2_rows = ((int)(*len_ptr / pa2)) + 1;

    /* Undo Second Columnar Transposition */
    int* after_t2_keyed = columnar_transposition_keyed_decode_int(ciphertext, *len_ptr, &(line_Q_R_Sequenced[pa1]), pa2);

    /* Build transpose table */
    int* transpose_table = malloc(t2_rows * sizeof(int));
    if (transpose_table == NULL) {
        free(after_t2_keyed);
        free(line_Q_R_Sequenced);
        free(straddle_line);
        free(return_vals);
        /* TODO - Send back an actual error (somehow) */
        printf("ERROR - UNABLE TO ALLOCATE MEMORY");
        return NULL;
    }
    int t2_first = 10;
    int t2_second = 10;
    int t2_first_index = 0;
    int t2_second_index = 0;
    for (i = pa1; i < pa1 + pa2; i++) {
        if (line_Q_R_Sequenced[i] < t2_second) {
            if (line_Q_R_Sequenced[i] < t2_first) {
                t2_second = t2_first;
                t2_second_index = t2_first_index;
                t2_first = line_Q_R_Sequenced[i];
                t2_first_index = i - pa1;
            }
            else {
                t2_second = line_Q_R_Sequenced[i];
                t2_second_index = i - pa1;
            }
        }
    }
    pos = 0;
    transpose_table[0] = t2_first_index;
    num = t2_first_index;
    for (i = 1; i < t2_rows; i++) {
        num++;
        if (num > pa2) {
            if (pos == 0) {
                num = t2_second_index;
            }
            else {
                num = pa2;
            }
        }
        transpose_table[i] = num;
    }

    /* Undo Message Transposition */
    int* t2_finished = offset_columnar_transposition_decode_int(after_t2_keyed, *len_ptr, transpose_table, t2_rows, pa2);

    /* Finish Undoing Columnar Transpositions */
    int* t1_finished = columnar_transposition_keyed_decode_int(t2_finished, *len_ptr, line_Q_R_Sequenced, pa1);

    /* Since VIC can have 0-4 extra random characters at the end, we assume the longest text with a valid straddle checkerboard decryption is correct */
    /* Theoretically it can have up to garbage characters at the end, but a human should be able to parse them out */
    int solution_index = -1;
    unsigned char* temp_solution;
    unsigned char* solution = NULL;
    int temp_len;
    for (i = 4; i >= 0; i--) {
        temp_len = *len_ptr - i;
        temp_solution = straddle_checkerboard_decode(t1_finished, straddle_line, straddle_alphabet, &temp_len);
        if (temp_solution != NULL) {
            solution_index = i;
            if (solution != NULL) {
                free(solution);
            }
            solution = temp_solution;
        }
    }

    /* Set len_ptr */
    if (solution == NULL) {
        *len_ptr = 0;
    }
    else {
        *len_ptr = temp_len;
    }

    /* Cleanup */
    free(t1_finished);
    free(t2_finished);
    free(transpose_table);
    free(after_t2_keyed);
    free(line_Q_R_Sequenced);
    free(straddle_line);
    free(return_vals);

    /* Return */
    return solution;
}
