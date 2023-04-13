#ifndef __CALCULATOR_HEADER
#define __CALCULATOR_HEADER

#include <stdbool.h>

typedef struct _Calculator
{
	double (**operations)(int, int);
	int **data;
	int operationCount;
	int dataLength;
} Calculator;

Calculator* create_calculator(double (**)(int, int), int);
bool load_calculator_data(Calculator*, char*);
void run_calculator(Calculator*);
bool destroy_calculator(Calculator*);

double add_calculator(int, int);
double sub_calculator(int, int);
double mul_calculator(int, int);
double div_calculator(int, int);
double mod_calculator(int, int);

#endif
