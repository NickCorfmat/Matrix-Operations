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

int main(int argc, char * argv[]) {

	FILE *in, *out;

	// CHECK that there are exactly two command line arguments.

	if (argc != 3) {
		fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	// OPEN files for reading and writing.

	in = fopen(argv[1], "r");

	if (in == NULL) {
		fprintf(stderr, "Unable to open file %s for reading.\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	out = fopen(argv[2], "w");

        if (out == NULL) {
                fprintf(stderr, "Unable to open file %s for writing.\n", argv[2]);
                exit(EXIT_FAILURE);
        }

	// SCAN first line.

	int n, a, b;
	fscanf(in, "%d %d %d", &n, &a, &b);

	// CREATE Matrix A.
	
	int row, col;
	double value;

	Matrix A = newMatrix(n);

	for (int i = 0; i < a; i++) {

		// READ row, column, and value.
		fscanf(in, "%d %d %lf", &row, &col, &value);

		// ADD entry.
		changeEntry(A, row, col, value);
	}

	// CREATE Matrix B.
	
	Matrix B = newMatrix(n);

	for (int i = 0; i < b; i++) {

		// READ row, column, and value.
                fscanf(in, "%d %d %lf", &row, &col, &value);

                // ADD entry.
                changeEntry(B, row, col, value);
	}

	// PRINT Matrix A and B.
	
	fprintf(out, "A has %d non-zero entries:\n", a);
	printMatrix(out, A);
	fprintf(out, "\n");

	fprintf(out, "B has %d non-zero entries:\n", b);
	printMatrix(out, B);
	fprintf(out, "\n");

	// PRINT scalar product.
	
	Matrix scalarA = scalarMult(1.5, A);
	fprintf(out, "(1.5)*A =\n");
	printMatrix(out, scalarA);
	fprintf(out, "\n");

	// PRINT sum of A and B.
	
	Matrix AplusB = sum(A, B);
	fprintf(out, "A+B =\n");
	printMatrix(out, AplusB);
	fprintf(out, "\n");

	// PRINT sum of A and A.
	
	Matrix AplusA = sum(A, A);
	fprintf(out, "A+A =\n");
	printMatrix(out, AplusA);
	fprintf(out, "\n");

	// PRINT difference of B and A.
	
	Matrix BminusA = diff(B, A);
	fprintf(out, "B-A =\n");
	printMatrix(out, BminusA);
	fprintf(out, "\n");

	// PRINT difference of A and A.
	
	Matrix AminusA = diff(A, A);
	fprintf(out, "A-A =\n");
	printMatrix(out, AminusA);
	fprintf(out, "\n");

	// PRINT transpose of A.
	
	Matrix transposeA = transpose(A);
	fprintf(out, "Transpose(A) =\n");
	printMatrix(out, transposeA);
	fprintf(out, "\n");

	// PRINT product of A and B.
	
	Matrix AxB = product(A, B);
	fprintf(out, "A*B =\n");
	printMatrix(out, AxB);
	fprintf(out, "\n");

	// PRINT product of B and B.
	
	Matrix BxB = product(B, B);
	fprintf(out, "B*B =\n");
	printMatrix(out, BxB);

	// CLOSE files and DEALLOCATE memory.

	fclose(in);
	fclose(out);

	freeMatrix(&A);
	freeMatrix(&B);
	freeMatrix(&scalarA);
	freeMatrix(&AplusB);
	freeMatrix(&AplusA);
	freeMatrix(&BminusA);
	freeMatrix(&AminusA);
	freeMatrix(&transposeA);
	freeMatrix(&AxB);
	freeMatrix(&BxB);

	return EXIT_SUCCESS;
}
