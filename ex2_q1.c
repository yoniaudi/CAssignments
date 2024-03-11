// Course: Advanced C programming
// exercise 2, question 1
// file name: ex2_q1.c

// --------------------------- //
// DO NOT CHANGE anything in the following macro:
#ifdef FUNC_DECLARE
#include "ex2_q1.h"
#else
// --------------------------------------- //
// Include and definition package section:
// --------------------------------------- //
#define FUNC_DECLARE
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define scanf_s scanf
#define ROWS 4
#define COLS 4
// --------------------------------------- //
// Types declration section:
// --------------------------------------- //
typedef struct fraction
{
	int num, numerator, denominator;
} fraction;
// --------------------------------------- //
// Functions declration section:
// --------------------------------------- //
unsigned long student_id();
fraction** createMatrix(int rows, int cols);
fraction** matrixAverageNeighbor(int A[][COLS], int rows, int cols);
fraction neighborFractionAverage(int A[][COLS], int i, int j, int rows, int cols);
void printMatrix(fraction** B, int rows, int cols);
void freeMatrix(fraction** B, int rows);
/** DECLARE HERE ONE FUNCTION ACCORDING TO YOUR NEEDS **/
// --------------------------------------- //
// Main section:
// --------------------------------------- //
int main()
{
	unsigned long id_num;
	fraction** B;
	int A[ROWS][COLS] = {
		{5, 12, 6, 8},
		{4, 7, 0, 9},
		{13, 20, 8, 2},
		{18, 0, 2, 6}
	};

	// call functions:
	id_num = student_id();
	printf("[id: %lu] start main\n", id_num);

	B = matrixAverageNeighbor(A, ROWS, COLS);

	// write output:
	printf("Output:\n");
	printMatrix(B, ROWS, COLS);

	// free matrix:
	freeMatrix(B, ROWS);

	return 0;
}
#endif
// --------------------------- //


// --------------------------- //
// function implementation section:
unsigned long student_id()
{
	// return your id number,
	// for example if your id is 595207432
	// return 595207432;
	// your code:

	return;
}
// --------------------------- //


/// <summary>
/// This code required one extra important function.
/// Think hard about what it should be.
/// </summary>
/// <params>You decide</params>
/// <returns>You decide</returns>

	// your code:

int gcdFunction(int a, int b)
{
	int temp;
	
	if (a < 0) a = -a;
	if (b < 0) b = -b;

	while (b > 0) {
		temp = b;
		b = a % b;
		a = temp;
	}

	return a;
}

// --------------------------- //

/// <summary>
/// This function allocate a dynamic matrix from type fraction.
/// </summary>
/// <param>int rows - the number of rows in the matrix</param>
/// <param>int cols - the number of colums in the matrix</param>
/// <returns>allocated empty matrix B from type fraction</returns>
fraction** createMatrix(int rows, int cols)
{
	// your code:

	fraction** B = (fraction**)malloc(rows * sizeof(fraction*));

	for (int i = 0; i < rows; i++) {
		B[i] = (fraction*)malloc(cols * sizeof(fraction));
	}

	return B;
}
// --------------------------- //

/// <summary>
/// The function receives a static matrix 
/// and for each cell in the matrix calculates 
/// the average of its neighbors.  
/// </summary>
/// <param>int A[][COLS] - the static matrix</param>
/// <param>int rows - the number of rows in the matrix</param>
/// <param>int cols - the number of colums in the matrix</param>
/// <returns>matrix B from type fraction</returns>
fraction** matrixAverageNeighbor(int A[][COLS], int rows, int cols)
{
	// your code:

	fraction** B = createMatrix(rows, cols);

	int i, j;

	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			B[i][j] = neighborFractionAverage(A, i, j, rows, cols);
		}
	}

	return B;
}
// --------------------------- //

/// <summary>
/// The function receives a static matrix, and a cell value,
/// and calculates the average of its neighbors.  
/// </summary>
/// <param>int A[][COLS] - the static matrix</param>
/// <param>int i - the cell row number in matrix</param>
/// <param>int j - the cell colum number in the matrix</param>
/// <param>int rows - the number of rows in the matrix</param>
/// <param>int cols - the number of colums in the matrix</param>
/// <returns>value from type fraction</returns>
fraction neighborFractionAverage(int A[][COLS], int i, int j, int rows, int cols)
{
	// your code:

	fraction neighborsAverage;

	int p, l, gcd; 
	int sum = 0, count = 0;

	for (p = i - 1; p <= i + 1; p++) {
		for (l = j - 1; l <= j + 1; l++) {
			if (p >= 0 && l >= 0 && p < rows && l < cols) {
				sum = sum + A[p][l];
				count++;
				if (p == i && l == j) {
					sum = sum - A[i][j];
					count--;
				}
			}
		}
	}

	if (count != 0) neighborsAverage.num = sum / count;
	else neighborsAverage.num = 0;
	neighborsAverage.numerator = sum - (neighborsAverage.num * count);
	neighborsAverage.denominator = count;

	gcd = gcdFunction(neighborsAverage.numerator, neighborsAverage.denominator);

	if (gcd > 1) {
		neighborsAverage.numerator = neighborsAverage.numerator / gcd;
		neighborsAverage.denominator = neighborsAverage.denominator / gcd;
	}

	return neighborsAverage;
}
// --------------------------- //


/// <summary>
/// The function receives a dynamic matrix from type fraction,
/// and print the matrix as double varibles.  
/// </summary>
/// <param>fraction** B - the dynamic matrix</param>
/// <param>int rows - the number of rows in the matrix</param>
/// <param>int cols - the number of colums in the matrix</param>
/// <returns>None</returns>
void printMatrix(fraction** B, int rows, int cols)
{
	// your code:

	int i, j;
	double avg;

	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			if (B[i][j].denominator != 0)
				avg = (double)B[i][j].numerator / B[i][j].denominator;
			else avg = 0.0;
			printf("%.2f\t", (double)B[i][j].num + avg);
		}
		printf("\n");
	}
}
// --------------------------- //


/// <summary>
/// The function receives a dynamic matrix from type fraction,
/// and free all allocated memory.  
/// </summary>
/// <param>fraction** B - the dynamic matrix</param>
/// <param>int rows - the number of rows in the matrix</param>
/// <returns>None</returns>
void freeMatrix(fraction** B, int rows)
{
	// your code:

	int i;

	for (i = 0; i < rows; i++) {
		free(B[i]);
	}

	free(B);
}
// --------------------------- //
