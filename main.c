// warning:  This is c++ code... convert it to c
// use:      https://www.geeksforgeeks.org/callbacks-in-c/
// note:     "borrowed" from https://stackoverflow.com/questions/6807376/call-back-routine
// note:     final project will use array of callbacks, but for now I just want to debug stuff :sob:

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

int main() {
    int value = columnar_transpositions_h_tests();
    return 0;
}
