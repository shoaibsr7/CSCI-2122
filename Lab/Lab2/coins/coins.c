#include "coins.h"
#include <stdio.h>

//1 dollar = 100 pennies
//1 quarter = 25 pennies
//1 dime = 10 pennies
//1 nickle = 5 pennies

int dollars(int pennies){
	//1999 % 100 = 99
	int remainder = pennies % 100;
	// 1999 - 99 = 1900 pennies / 100 = $19
	int dollarAmount = (pennies - remainder) / 100;
	// left over 99 pennies
	printf("%d dollars, ", dollarAmount);
	return remainder;
}

int quarters(int pennies){
	// remainder is 99 pennies
	// therefore 99 % 25 = 24
	int remainder = pennies % 25;
	// 99 - 24 = 75 pennies / 25 = 3 quarters
	int quarterAmount = (pennies - remainder) / 25;
	printf("%d quarters, ", quarterAmount);
	return remainder;
}

int dimes(int pennies){
	// remainder is 24 pennies
	// 24 % 10 = 4 
	int remainder = pennies % 10;
	// 24 - 4 = 20 pennies / 10 = 2 dimes
	int dimeAmount = (pennies - remainder) / 10;
	printf("%d dimes, ", dimeAmount);
	return remainder;
}

int nickel(int pennies){
	//remainder is 4
	//4 % 5 = 4
	int remainder = pennies % 5;
	// 4 - 5 = -1 pennies / 5 = 2 (int)
	int nickelAmount = (pennies - remainder) / 5;
	printf("%d nickels, ", nickelAmount);
	return remainder;
}

//int main(int argc, char** argv){
//	int pennies = 2000;

void calculateCoins(int pennies){
	pennies = dollars(pennies);
	pennies = quarters(pennies);
	pennies = dimes(pennies);
	pennies = nickel(pennies);
	printf("%d pennies\n", pennies);
}
