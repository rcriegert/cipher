#include "../H_FILES/chain_addition.h"

void chain_addition(int chain[], int start_chain, int total_len, int base) {
    int num_1 = 0;
    int num_2 = 1;
    int i;
    for (i = start_chain; i < total_len; i++) {
        chain[i] = (chain[num_1] + chain[num_2]) % base;
        num_1++;
        num_2++;
    }
    return;
}
