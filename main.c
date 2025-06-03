/* warning:  This is c++ code... convert it to c */
/* use:      https://www.geeksforgeeks.org/callbacks-in-c/ */
/* note:     "borrowed" from https://stackoverflow.com/questions/6807376/call-back-routine */
/* note:     final project will use array of callbacks, but for now I just want to debug stuff :sob: */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "VIC/VIC.h"

#define MAX_CIPHER_PARAMETERS 6

/*#include <map>
#include <iostream>

typedef void (*Callback)();
std::map<int, Callback>  callback_map;

void RegisterCallback(int event, Callback function)
{
	callback_map[event] = function;
}

bool finished = false;

int GetNextEvent()
{
	static int i = 0;
	++i;
	if (i == 5) finished = true;
	return i;
}

void EventProcessor()
{
	int event;
	while (!finished)
	{
		event = GetNextEvent();
		std::map<int, Callback>::iterator it = callback_map.find(event);
		if (it != callback_map.end())    // if a callback is registered for event
		{
			Callback function = *it->second;
			if (function)
			{
				(*function)();
			}
			else
			{
				std::cout << "No callback found\n";
			}
		}
	}
}

void Cat()
{
	std::cout << "Cat\n";
}

void Dog()
{
	std::cout << "Dog\n";
}

void Bird()
{
	std::cout << "Bird\n";
}

int main()
{
	RegisterCallback(1, Cat);
	RegisterCallback(2, Dog);
	RegisterCallback(3, Cat);
	RegisterCallback(4, Bird);
	RegisterCallback(5, Cat);

	EventProcessor();
	return 0;
}
*/

struct Cipher {
    void* function_ptr;
    unsigned char* plaintext;
    unsigned char* ciphertext;
    void* parameters[MAX_CIPHER_PARAMETERS];
};

int main() {
    /* int value = columnar_transpositions_h_tests(); */
    /* struct Cipher simple_vic; */
    /* vic.function_ptr = & */

    int personal_number = 8;
    int date_number[] = {7, 4, 1, 7, 7, 6};
    unsigned char phrase[] = "IDREAMOFJEANNIEWITHT";
    int keygroup_number[] = {7, 7, 6, 5, 1};
    unsigned char straddle_alphabet[] = "AT ONE SIRBCDFGHJKLMPQUVWXYZ./";
    unsigned char plaintext[] = "WEAREPLEASEDTOHEAROFYOURSUCCESSINESTABLISHINGYOURFALSEIDENTITYYOUWILLBESENTSOMEMONEYTOCOVEREXPENSESWITHINAMONTH";
    int ciphertext_len = strlen(plaintext);

    int* vic_end = vic_encrypt(plaintext, personal_number, date_number, phrase, keygroup_number, straddle_alphabet, &ciphertext_len);

    unsigned char* vic_free = vic_decrypt(vic_end, personal_number, date_number, phrase, straddle_alphabet, &ciphertext_len);

    int i;
    for (i = 0; i < ciphertext_len; i++) {
        printf("%c ", vic_free[i]);
    }

    free(vic_free);


    /* Cleanup */
    free(vic_end);
    return 0;
}
