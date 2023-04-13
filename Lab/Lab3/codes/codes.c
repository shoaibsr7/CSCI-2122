#include "mmath.h"
#include "codes.h"

#include <stdio.h>

// Function Implementation: 
// Name:    	encrypt(int, int, char)
// Description: Encrypt a char and store it in an int.
// Notes:       None.
int encrypt(int start, int offset, char target)
{
	// First, reverse the character's binary representation.
	char rev = (char) bitrevc(target);

	// Convert the reversed char to an integer, then bitshift it
	// to the left by start, then bitshift to the right by offset.
	return ((int)rev << start) >> offset;
}

// Function Implementation: 
// Name:    	decrypt(int, int, int)
// Description: Decrypt an int and store it in a char.
// Notes:       None.
char decrypt(int start, int offset, int cipher)
{
	// Undo the right shift with a left shift, then undo the
	// original left shift with a right shift, then cast it to a char.
	char target = (char)((cipher << offset) >> start);

	// Reverse the char's binary representation and return it.
	return bitrevc(target);
}
