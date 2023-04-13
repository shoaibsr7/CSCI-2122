#include "adjmult.h"
#include <stdio.h>

// Function Implementation: 
// Name:    	imax(int[], int)
// Description: Return the largest value in an integer array.
// Notes:       Does not sanity check size or array state.
int imax(int values[], int size)
{
	// Set the starting largest to the first value.
	int largest = values[0];

	// Iterate through the rest of the values in the array.
	for(int i=1; i < size; i++)
		// If this value of the array is largest so far, store it.
		largest = (values[i] > largest ? values[i] : largest);
	
	// We should have the largest value in the array now, so return it.
	return largest;
}

// Function Implementation: 
// Name:    	readGrid(int[20][20])
// Description: Read a grid from stdin and store it in the array..
// Notes:       Does not sanity check array state.
void readGrid(int grid[20][20])
{
	// Read in 20 integers one row at a time and store them in  the array.
	for(int r=0; r < 20; r++)
		for(int c=0; c < 20; c++)
			scanf("%d", &grid[r][c]);
}


// Function Implementation: 
// Name:    	largestProduct()
// Description: Find the largest product in a matrix of integers.
//              The product uses four adjacent values in a straight line.
// Notes:       None.
int largestProduct()
{
	// Create a 2d array to store a grid of integers.
	int grid[20][20];

	// Populate the grid from stdin.
	readGrid(grid);

	// Set up an array for holding individual products based on pattern.
	int values[5] = {0, 0, 0, 0, 0};

	// Iterate through all rows.
	for(int i=0; i < 20; i++)
	{
		// Iterate through all columns.
		for(int j=0; j < 20; j++)
		{
			// As long as there are four numbers in the row,
			// we can check for the horizontal line product,
			// and the right diagonal products.
			if(j <= 16)
			{
				// Save the horizontal line product.
				values[1] = grid[i][j] * grid[i][j+1] * grid[i][j+2] * grid[i][j+3];

				
				// As long as there are three rows below this row, we can check for
				// the lower right diagonal.
				if(i <= 16)
				{
					// Save the lower right diagonal product.
					values[2] = grid[i][j] * grid[i+1][j+1] * grid[i+2][j+2] * grid[i+3][j+3];
				}

				// As long as there are three rows above this row we can check for 
				// the upper right diagonal.
				if(i >= 3)
				{
					// Save the upper right diagonal product.
					values[3] = grid[i][j] * grid[i-1][j+1] * grid[i-2][j+2] * grid[i-3][j+3];
				}
			}

			// As long as there are four rows left to check,
			// we can check the vertical product.
			if(i <= 16)
			{
				// Save the vertical product.
				values[4] = grid[i][j] * grid[i+1][j] * grid[i+2][j] * grid[i+3][j];
			}
			
			// Find the largest value of the current iteration and store it.
			values[0] = imax(values, 5);
		}
	}

	// Since the largest product is stored in the 0th index, we can return it here.
	return values[0];
}

