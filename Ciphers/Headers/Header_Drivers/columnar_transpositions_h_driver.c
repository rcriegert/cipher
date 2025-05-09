#include "../columnar_transpositions.h"
#include <string.h>

int main(int argc, char** argv) {


    unsigned char plaintext[] = "abcdefghijklmnopqrstuvwxyz";
    int plaintext_len = 26;
    int column_count = 5;
    unsigned char* ciphertext = unkeyed_columnar_transposition_uc(plaintext, plaintext_len, column_count);
    unsigned char correct_output[] = "afkpuzbglqvchmrwdinsxejoty";

    int test_1 = strncmp(ciphertext, correct_output, plaintext_len);
    if (test_1 == 0) {
        printf("Test 1 succeeded\n");
    }
    else {
        printf("Test 1 failed\n");
    }
    free(ciphertext);



    return 0;
}
