// --------------------------------------------------------------
// Nicolas Corfmat
// CruzID: ncorfmat
// Assignment: pa4
// --------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "Matrix.h"
#include "List.h"

int main(int argc, char* argv[]) {

	Matrix M = newMatrix(3);
	changeEntry(M, 1, 1, 1);
	changeEntry(M, 1, 2, 2);
	changeEntry(M, 1, 3, 7);
	changeEntry(M, 2, 2, 4.0);
	changeEntry(M, 2, 1, 3.0);
	changeEntry(M, 2, 2, 50);
	changeEntry(M, 2, 3, 40);
	changeEntry(M, 3, 1, 8);
	changeEntry(M, 3, 2, 11);
	changeEntry(M, 3, 3, 12);
	
	Matrix N = copy(M);
	
	printMatrix(stdout, M);
	fprintf(stdout, "\n");
	printMatrix(stdout, N);
	fprintf(stdout, "\n");

	changeEntry(M, 2, 2, 4.0);
	changeEntry(N, 1, 1, 3.0);

	fprintf(stdout, "M:\n");
	printMatrix(stdout, M);
	fprintf(stdout, "\n");

	fprintf(stdout, "N:\n");
	printMatrix(stdout, N);
	fprintf(stdout, "\n");

	Matrix S = sum(M, N);
	Matrix D = diff(M, N);
	Matrix SM = scalarMult(1.5, S);
	Matrix T = transpose(SM);

	fprintf(stdout, "M + N:\n");
	printMatrix(stdout, S);
	fprintf(stdout, "\n");

	fprintf(stdout, "M - N:\n");
	printMatrix(stdout, D);
	fprintf(stdout, "\n");

	fprintf(stdout, "T of SM:\n");
        printMatrix(stdout, T);
        fprintf(stdout, "\n");

	fprintf(stdout, "SM:\n");
        printMatrix(stdout, SM);
        fprintf(stdout, "\n");

	Matrix A = newMatrix(1);
	Matrix B = newMatrix(1);

	changeEntry(A, 1, 1, 2.0);
	changeEntry(B, 1, 1, 3.0);
	changeEntry(B, 1, 1, 0);
	changeEntry(B, 1, 1, 2.0);

	Matrix P = product(S, SM);

	fprintf(stdout, "Product:\n");
        printMatrix(stdout, P);
        fprintf(stdout, "\n");

	Matrix CopyB = copy(B);

	printf("A =? B: %s\n", equals(A, B)?"true":"false");
	printf("B =? CopyB: %s\n", equals(B, CopyB)?"true":"false");
	printf("M =? N: %s\n", equals(M, N)?"true":"false");
	printf("S =? D: %s\n", equals(S, D)?"true":"false");
	printf("S =? T: %s\n\n", equals(S, T)?"true":"false");

	makeZero(SM);
	printf("SM NNZ: %d\n\n", NNZ(SM));
	printMatrix(stdout, SM);
	
	freeMatrix(&M);
	freeMatrix(&N);
	freeMatrix(&S);
	freeMatrix(&D);
	freeMatrix(&SM);
	freeMatrix(&T);
	freeMatrix(&P);
	freeMatrix(&A);
	freeMatrix(&B);

	return 0;
}
