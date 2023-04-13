#include "power.h"
#include <stdio.h>

void powerRule1 (int a, int b)
{
	printf("%d\n", a);
}

void powerRule2 (int c, int d, int e)
{
	printf("%dx + ", c*2);
	powerRule1(d, e);
}

void powerRule3 (int f, int g, int h, int i)
{
	printf("%dx^2 + ", f*3);
	powerRule2(g, h, i);
}

void powerRule4 (int j, int k, int l, int m, int n)
{
	printf("%dx^3 + ", j*4);
	powerRule3(k, l, m, n);
}
