#include<stdio.h>
#include<stdlib.h>

#define length 6

void matrix_chain_order(int* matrix)
{
	int n = length;
	int memory[length][length];
	int partpoint[length - 1][length - 1];

	

}

int main()
{
	int matrix1[length + 1] = { 30, 35, 15, 5, 10, 20, 25 };
	int matrix2[length + 1] = { 5, 10, 3, 12, 5, 50, 6 };

	matrix_chain_order(matrix1);
	matrix_chain_order(matrix2)
}