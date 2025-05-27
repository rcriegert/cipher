#include "../H_FILES/sequencing.h"

/* TODO - write this */
/* TODO - safe malloc */
int* positive_increasing_int(int* to_sequence, int len) {
    int* to_sequence_copy = (int*)malloc(len * sizeof(int));
    int i;
    int j;
    for (i = 0; i < len; i++) {
        to_sequence_copy[i] = to_sequence[i];
    }
    int* sequence = (int*)malloc(len * sizeof(int));
    int num;
    int pos;
    for (i = 0; i < len; i++) {
        num = INT_MAX;
        pos = 0;
        for (j = 0; j < len; j++) {
            if (to_sequence_copy[j] < num) {
                pos = j;
                num = to_sequence_copy[j];
            }
            sequence[pos] = i;
            to_sequence_copy[pos] = INT_MAX;
        }
    }

    free(to_sequence_copy);
    return sequence;
}
