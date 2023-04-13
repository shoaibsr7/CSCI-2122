#include <math.h>
#include "mmath.h"

long fact(int n)
{
	long k = 1;
	for (int i = 2; i <= n; i++)
	{
		k = k*i;
	}
	return k;
}

long nchoosek(int n, int k)
{
	// n!/( k! (n-k)! )
	long nFact = fact(n);
	long kFact = fact(k);
	long NKfact = fact(n-k);
	long result = nFact/( kFact * NKfact );

	return result;
}

int prime(long n)
{
	// 2 is the only even prime number
	if (n == 2)
		return 1;

	if (n < 2)
		return 0;
	
	if (n%2 == 0)
		return 0;

	// since all the primes are odd numbers we will be iterating by 2
	// and we will be starting the loop from 3 because we already checked for 1 and 2
	// since any number will never be more than half of itself we will be keeping the checkpoint
	// until the half of the input
	for (long i = 3; i < n/2; i+=2)
	{
		if (n % i == 0)
			return 0;
	}

	return 1;
}

int gcd(int a, int b)
{
	if (a == 0)
		return b;
	if (b == 0)
		return a;
	if (a == b)
		return a;
	if (a > b)
		return gcd(a-b, b);
	return gcd(a, b-a);
}

int lcm(int a, int b)
{
	return ( (a*b)/gcd(a,b) );
}

char bitrevc(char value)
{
	int bit0,bit1,bit2,bit3,bit4,bit5,bit6,bit7;

	bit0 = value & 0x01;
	bit0 = bit0 << 7;
	
	bit1 = value & 0x02;
	bit1 = bit1 << 5;
	
	bit2 = value & 0x04;
	bit2 = bit2 << 3;
	
	bit3 = value & 0x08;
	bit3 = bit3 << 1;
	
	bit4 = value & 0x10;
	bit4 = bit4 >> 1;
	
	bit5 = value & 0x20;
	bit5 = bit5 >> 3;
	
	bit6 = value & 0x40;
	bit6 = bit6 >> 5;
	
	bit7 = value & 0x80;
	bit7 = bit7 >> 7;

	return (value = bit0 | bit1 | bit2 | bit3 | bit4 | bit5 | bit6 | bit7) ;

//	return value;

//	char rev = 0;
//	char temp = 0;
//	for (int i=0; i < 8; i++)
//	{
//		temp = value >> i;
//
//		temp = temp & 1;
//
//		temp = temp << (8-i-1);
//
//		rev = rev | temp;
//	}	
//	return rev;
}

