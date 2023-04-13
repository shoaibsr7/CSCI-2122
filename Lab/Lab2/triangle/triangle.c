#include "triangle.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void printResult (double opposite, double adjacent, double hypotenuse, double x, double y)
{
	printf("\nopposite = %.2f\nadjacent = %.2f\nhypotenuse = %.2f\nx = %.2f\ny = %.2f\n\n", opposite, adjacent, hypotenuse, x, y);
}

double findOppositePyth(double adjacent, double hypotenuse, double x, double y)
{
	double opposite = pow(hypotenuse, 2) - pow(adjacent, 2);
	
	opposite = sqrt(opposite);

	printResult(opposite, adjacent, hypotenuse, x, y);

	return opposite;
}

double findAdjacentPyth(double opposite, double hypotenuse, double x, double y)
{
	double adjacent = pow(hypotenuse, 2) - pow(opposite, 2);

	adjacent = sqrt(adjacent);

	printResult(opposite, adjacent, hypotenuse, x, y);

	return adjacent;
}

double findHypotenusePyth(double opposite, double adjacent, double x, double y)
{
	double hypotenuse = pow(opposite, 2) + pow(adjacent, 2);

	hypotenuse = sqrt(hypotenuse);

	printResult(opposite, adjacent, hypotenuse, x, y);

	return hypotenuse;
}

double findOppositeTrig(double adjacent, double hypotenuse, double x, double y)
{
	double opposite = hypotenuse * cos(y);

	printResult(opposite, adjacent, hypotenuse, x, y);

	return opposite;
}

double findAdjacentTrig(double opposite, double hypotenuse, double x, double y)
{
	double adjacent = hypotenuse * sin(y);

	printResult(opposite, adjacent, hypotenuse, x, y);

	return adjacent;
}

double findHypotenuseTrig(double opposite, double adjacent, double x, double y)
{
	double hypotenuse = opposite / sin(x);

	printResult(opposite, adjacent, hypotenuse, x, y);

	return hypotenuse;
}
