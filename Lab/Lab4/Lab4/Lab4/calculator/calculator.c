#include "calculator.h"
#include <stdio.h>
#include <stdlib.h>
#define FILE_DATA_SIZE 100

Calculator* create_calculator(double (**mathOperations)(int,int), int length)
{
	Calculator* calc = malloc(sizeof *calc);

	if (calc == NULL)
		return NULL;

	calc->operations = mathOperations;
	calc->data = NULL;
	calc->operationCount = length;
//	-1 cause when we add the first value in the address the index starts from 0
	calc->dataLength = -1;

	return calc;
}

bool load_calculator_data(Calculator* calc, char* fileName)
{
	if(calc == NULL || fileName == NULL)
		return false;

	calc->data = malloc(sizeof *(calc->data)*FILE_DATA_SIZE);

	FILE* filePointer = fopen(fileName, "r");

	if(filePointer == NULL)
		return false;

	int i = 0;
	int op, a, b;

//	int fscanf(FILE *stream, const char *format, address of)
	while(fscanf(filePointer, "%d %d %d", &op, &a, &b) == 3)
	{
		calc->data[i] = malloc(sizeof *(calc->data[i]) *3);
		calc->data[i][0] = op;
		calc->data[i][1] = a;
		calc->data[i][2] = b;

		i++;
	}
	calc->dataLength = i;

	return true;
}

void run_calculator(Calculator* calc)
{
	for (int i = 0; i < calc->dataLength; i++)
	{
		int op = calc->data[i][0];
		int a = calc->data[i][1];
		int b = calc->data[i][2];

		printf("%.5lf\n", calc->operations[op](a,b));
	}
}

bool destroy_calculator(Calculator* calc)
{
	if (calc == NULL)
		return false;

	for(int i=0; i<calc->dataLength; i++)
		free(calc->data[i]);

	free(calc->data);
	free(calc);

	return true;
}

double add_calculator(int a, int b)
{
	return (double) a + b;
}

double sub_calculator(int a, int b)
{
	return (double) a - b;
}

double mul_calculator(int a, int b)
{
	return (double) a * b;
}

double div_calculator(int a, int b)
{
	return (double) a / b;
}

double mod_calculator(int a, int b)
{
	return (double) (a % b);
}
