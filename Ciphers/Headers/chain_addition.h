#ifndef CHAIN_ADDITION_H_INCLUDED
#define CHAIN_ADDITION_H_INCLUDED

void chain_addition(int array[], int start_chain, int total_len, int base) {
    int num_1 = 0;
    int num_2 = 1;
    for (int i = start_chain; i < total_len; i++) {
        array[i] = (array[num_1] + array[num_2]) % base;
        num_1++;
        num_2++;
    }
    return;
}

#endif // CHAIN_ADDITION_H_INCLUDED
