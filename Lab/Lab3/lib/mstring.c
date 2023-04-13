#include "mstring.h"

void strrev(char* value)
{
	int length = strlen(value);

	char temp;

	for (int i = 0; i < length/2; i++)
	{
		// temp = shoaib (var = b) (store last char in temp)
		// shoai = hoais (shift first char to the end)
		// bhoais = var (var = null) (add temp into char.)
		temp = value [length-i-1];

		value [length-i-1] = value[i];

		value [i] = temp;
	}
}
