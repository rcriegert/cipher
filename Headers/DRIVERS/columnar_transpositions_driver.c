#include "columnar_transpositions_driver.h"

int columnar_transpositions_tests() {

    /* Test 1 -- Simple Unkeyed Columnar Transposition */
    {
        unsigned char plaintext[] = "abcdefghijklmnopqrstuvwxyz";
        int plaintext_len = 26;
        int column_count = 5;
        unsigned char* ciphertext = columnar_transposition_unkeyed_encode_uc(plaintext, plaintext_len, column_count);
        unsigned char correct_output[] = "afkpuzbglqvchmrwdinsxejoty";

        int test_1 = strncmp(ciphertext, correct_output, plaintext_len);
        if (test_1 == 0) {
            printf("Succeeded - Test 1: Simple Unkeyed Columnar Transposition\n");
        }
        else {
            printf("Failed - Test 1: Simple Unkeyed Columnar Transposition\n");
        }
        free(ciphertext);
    }

    /* Test 2 -- Trivial Keyed Columnar Transposition */
    {
        unsigned char plaintext[] = "abcdefghijklmnopqrstuvwxyz";
        int plaintext_len = 26;
        int key[] = {0, 1, 2, 3, 4};
        int key_len = 5;
        unsigned char* ciphertext = columnar_transposition_keyed_encode_uc(plaintext, plaintext_len, key, key_len);
        unsigned char correct_output[] = "afkpuzbglqvchmrwdinsxejoty";

        int test_2 = strncmp(ciphertext, correct_output, plaintext_len);
        if (test_2 == 0) {
            printf("Succeeded - Test 2: Trivial Keyed Columnar Transposition\n");
        }
        else {
            printf("Failed - Test 2: Trivial Keyed Columnar Transposition\n");
        }
        free(ciphertext);
    }

    /* Test 3 -- Keyed Columnar Transposition */
    {
        unsigned char plaintext[] = "abcdefghijklmnopqrstuvwxyz";
        int plaintext_len = 26;
        int key[] = {2, 0, 4, 1, 3};
        int key_len = 5;
        unsigned char* ciphertext = columnar_transposition_keyed_encode_uc(plaintext, plaintext_len, key, key_len);
        unsigned char correct_output[] = "chmrwafkpuzejotybglqvdinsx";

        int test_3 = strncmp(ciphertext, correct_output, plaintext_len);
        if (test_3 == 0) {
            printf("Succeeded - Test 3: Keyed Columnar Transposition\n");
        }
        else {
            printf("Failed - Test 3: Keyed Columnar Transposition\n");
        }
        free(ciphertext);
    }

    /* TODO - more tests (which?) */

    return 0;
}
