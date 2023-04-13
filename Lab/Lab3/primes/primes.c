#include <stdio.h>
#include <stdbool.h>
#include "primes.h"
#include "mmath.h"

void primes(long value)
{
//	check to see if divided by 2 leaves 0 as remainder
	//while (value % 2 == 0)
	//{
	//	printf("%d ", 2);
	//	value = value/2;
	//}
//	since we done with 2 we can increment leaving one number
//	that is every odd number
	//for(int i = 3; value <= sqrt(value); i += 2)	
	//{
	//	while(value % i == 0)
	//	{
	//		printf("%d ", i);
	//		value = value/i;
	//	}
	//}

	//if (value > 2)
	//{
	//	printf("%d ", value);
	//}
	
	int c = 2;
	while (value > 1)
	{
		if (value % c == 0)
		{
			printf("%d ", c);
			value = value/c;
		}
		else
			c++;
	}
	printf("\n");

}
