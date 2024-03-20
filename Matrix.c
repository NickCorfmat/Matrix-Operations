// --------------------------------------------------------------
// Nicolas Corfmat
// CruzID: ncorfmat
// Assignment: pa4
// --------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include "Matrix.h"
#include "List.h"

/*** Constructors-Destructors ***/

typedef struct EntryObj* Entry;

typedef struct EntryObj {
	int col;
	double val;
} EntryObj;

typedef struct MatrixObj* Matrix;

typedef struct MatrixObj {
	int size;
	int nnz;
	List* rows;
} MatrixObj;

Entry newEntry(int col, double val) {

	// ALLOCATES memory for new Entry variable.
	Entry E = malloc(sizeof(EntryObj));

	assert(E != NULL);

	// ASSIGN the default vaules to the Entry object.
	E->col = col;
	E->val = val;

	return E;
}

Matrix newMatrix(int n) {
	if (n <= 0) {
		fprintf(stderr, "Error: Matrix size must be at least 1x1.\n");
		exit(EXIT_FAILURE);
	}

	// ALLOCATE memory for Matrix object.
	Matrix M = malloc(sizeof(MatrixObj));

	assert(M != NULL);

	// ASSIGN default values to Matrix.
	M->size = n;
	M->nnz = 0;

	M->rows = (List *) malloc((n + 1) * sizeof(List));

	// INITALIZE first slot to NULL.
	M->rows[0] = NULL;

	// INITIALIZE the dynamically allocated array.
	for (int r = 1; r <= n; r++) {
		M->rows[r] = newList();
	}

	return M;
}

void freeEntry(Entry* pE) {

	// FREEs memory used by the Entry object.
	if (pE != NULL && *pE != NULL) {
		free(*pE);
		*pE = NULL;
	}
}

void freeMatrix(Matrix* pM) {
	if (pM != NULL && *pM != NULL) {

		// FREE rows array.
		for (int r = 1; r <= (*pM)->size; r++) {
			List row = (*pM)->rows[r];

			for (moveFront(row); index(row) >= 0; moveNext(row)) {
				Entry E = get(row);
				freeEntry(&E);
			}

			freeList(&row);
		}

		free((*pM)->rows);

		// FREE Matrix object.
		free(*pM);
		*pM = NULL;
	}
}

/*** Access Functions ***/

int size(Matrix M) {
	if (M == NULL) {
		fprintf(stderr, "Error: Calling size() on NULL Matrix object.\n");
		exit(EXIT_FAILURE);
	}

	return M->size;
}

int NNZ(Matrix M) {
	if (M == NULL) {
                fprintf(stderr, "Error: Calling NNZ() on NULL Matrix object.\n");
                exit(EXIT_FAILURE);
        }

	return M->nnz;
}

int equals(Matrix A, Matrix B) {
	if (A == NULL || B == NULL) {
                fprintf(stderr, "Error: Calling equals() on NULL Matrix object(s).\n");
                exit(EXIT_FAILURE);
        }

	if (A->size != B->size) {
		return 0;
	}
	
	for (int r = 1; r <= A->size; r++) {
		List rowA = A->rows[r];
		List rowB = B->rows[r];

		if (length(rowA) != length(rowB)) {
			return 0;
		}

		moveFront(rowA);
		moveFront(rowB);

		while (index(rowA) >= 0 && index(rowB) >= 0) {
			Entry eA = get(rowA);
			Entry eB = get(rowB);

			if (eA->col != eB->col || eA->val != eB->val) {
				return 0;
			}

			moveNext(rowA);
			moveNext(rowB);
		}
	}

	return 1;
}

/*** Helper Functions ***/

void sortAppend(List L, Entry E) { // APPEND in increasing order
	if (length(L) <= 0) {
		append(L, E);
	} else {
		moveBack(L);

		Entry curr = get(L);

		while (E->col < curr->col && index(L) > 0) {
			movePrev(L);
			curr = get(L);
		}

		if (E->col < curr->col) {
                        insertBefore(L, E);
                } else if (E->col > curr->col) {
                        insertAfter(L, E);
                } else {
			set(L, E);
			freeEntry(&curr);
		}
	}
}

/*** Manipulation Procedures ***/

void makeZero(Matrix M) {
	if (M == NULL) {
		fprintf(stderr, "Error: Calling makeZero() on NULL Matrix object.\n");
		exit(EXIT_FAILURE);
	}

	for (int r = 1; r <= M->size; r++) {
                List row = M->rows[r];

                for (moveFront(row); index(row) >= 0; moveNext(row)) {
			Entry E = get(row);
			freeEntry(&E);
                }

		clear(row);
	}

	M->nnz = 0;
}

void changeEntry(Matrix M, int i, int j, double x) {
	if (M == NULL) {
                fprintf(stderr, "Error: Calling changeEntry() on NULL Matrix object.\n");
                exit(EXIT_FAILURE);
        }

	if (i < 1 || i > M->size) {
		fprintf(stderr, "Error: i must be in range [1, %d].\n", M->size);
		exit(EXIT_FAILURE);
	}

	if (j < 1 || j > M->size) {
                fprintf(stderr, "Error: j must be in range [1, %d].\n", M->size);
                exit(EXIT_FAILURE);
        }

	if (x == 0) {
		List row = M->rows[i];

		for (moveFront(row); index(row) >= 0; moveNext(row)) {
			Entry E = get(row);

			if (j == E->col) {
				delete(row);
				freeEntry(&E);
				M->nnz -= 1;
				break;
			}
		}
	} else {
		Entry E = newEntry(j, x);

		// EITHER replace or insert new Entry.
		sortAppend(M->rows[i], E);
		M->nnz += 1;
	}
}

/*** Matrix Arithmetic Operations ***/

Matrix copy(Matrix A) {
	if (A == NULL) {
                fprintf(stderr, "Error: Calling copy() on NULL Matrix object.\n");
                exit(EXIT_FAILURE);
        }

	Matrix M = newMatrix(A->size);
	M->nnz = A->nnz;

	// COPY rows in A to new Matrix.
	for (int r = 1; r <= M->size; r++) {
		List rowA = A->rows[r];

		for (moveFront(rowA); index(rowA) >= 0; moveNext(rowA)) {
			Entry E = get(rowA);
			Entry copy = newEntry(E->col, E->val);
			append(M->rows[r], copy);
		}
	}

	return M;
}

Matrix transpose(Matrix A) {
	if (A == NULL) {
                fprintf(stderr, "Error: Calling transpose() on NULL Matrix object.\n");
                exit(EXIT_FAILURE);
        }

	Matrix M = newMatrix(A->size);
	M->nnz = A->nnz;

	for (int r = 1; r <= M->size; r++) {
		List row = A->rows[r];

		for (moveFront(row); index(row) >= 0; moveNext(row)) {
			Entry E = get(row);
			Entry eM = newEntry(r, E->val);
			append(M->rows[E->col], eM);
		}
	}

	return M;
}

Matrix scalarMult(double x, Matrix A) {
	if (A == NULL) {
                fprintf(stderr, "Error: Calling scalarMult() on NULL Matrix object.\n");
                exit(EXIT_FAILURE);
        }

	Matrix M = newMatrix(A->size);
	
	for (int r = 1; r <= M->size; r++) {
		List rowA = A->rows[r];

		if (length(rowA) == 0) {
			continue;
		}

		for (moveFront(rowA); index(rowA) >= 0; moveNext(rowA)) {
			Entry E = get(rowA);

			double product = x * E->val;

			if (product != 0) {
				Entry copy = newEntry(E->col, product);
				append(M->rows[r], copy);
			}
		}

		M->nnz += length(M->rows[r]);
	}

	return M;
}

Matrix sum(Matrix A, Matrix B) {
	if (A == NULL || B == NULL) {
                fprintf(stderr, "Error: Calling sum() on NULL Matrix object(s).\n");
                exit(EXIT_FAILURE);
        }

	if (equals(A, B) == 1) {
		return scalarMult(2.0, A);
	}

	Matrix M = newMatrix(A->size);

	for (int r = 1; r <= M->size; r++) {
		List rowA = A->rows[r];
		List rowB = B->rows[r];
		List out = M->rows[r];

		moveFront(rowA);
		moveFront(rowB);

		// COPY entire row to M if one is empty.
		if (length(rowA) == 0) {
			for (moveFront(rowB); index(rowB) >= 0; moveNext(rowB)) {
				Entry E = get(rowB);
				Entry copy = newEntry(E->col, E->val);
				append(out, copy);
			}
		}		

		if (length(rowB) == 0) {
			for (moveFront(rowA); index(rowA) >= 0; moveNext(rowA)) {
				Entry E = get(rowA);
				Entry copy = newEntry(E->col, E->val);
				append(out, copy);
			}
		}

		while (index(rowA) >= 0 && index(rowB) >= 0) {
			Entry eA = get(rowA);
			Entry eB = get(rowB);

			if (eA->col > eB->col) {
				Entry copyB = newEntry(eB->col, eB->val);
				append(out, copyB);
				moveNext(rowB);
			} else if (eA->col < eB->col) {
				Entry copyA = newEntry(eA->col, eA->val);
				append(out, copyA);
				moveNext(rowA);
			} else {
				double sum = eA->val + eB->val;

				if (sum != 0) {
					Entry copy = newEntry(eA->col, sum);
					append(out, copy);
				}

				moveNext(rowB);
				moveNext(rowA);
			}
		}

		// FLUSH rows.
		while (index(rowA) >= 0) {
			Entry eA = get(rowA);
			Entry copy = newEntry(eA->col, eA->val);
			append(out, copy);
			moveNext(rowA);
		}
		
		while (index(rowB) >= 0) {
			Entry eB = get(rowB);
			Entry copy = newEntry(eB->col, eB->val);
			append(out, copy);
			moveNext(rowB);
		}

		M->nnz += length(M->rows[r]);
	}

	return M;
}

Matrix diff(Matrix A, Matrix B) {
	if (A == NULL || B == NULL) {
                fprintf(stderr, "Error: Calling diff() on NULL Matrix object(s).\n");
                exit(EXIT_FAILURE);
        }

	Matrix M = newMatrix(A->size);

	if (equals(A, B) == 1) {
		return M;
	}

	for (int r = 1; r <= M->size; r++) {
		List rowA = A->rows[r];
		List rowB = B->rows[r];
		List out = M->rows[r];

		moveFront(rowA);
		moveFront(rowB);

		// COPY entire row to M if one is empty.
		if (length(rowA) == 0) {
			for (moveFront(rowB); index(rowB) >= 0; moveNext(rowB)) {
				Entry E = get(rowB);
                                Entry copy = newEntry(E->col, (0 - E->val));
                                append(out, copy);
			}
		}

		if (length(rowB) == 0) {
			for (moveFront(rowA); index(rowA) >= 0; moveNext(rowA)) {
                                Entry E = get(rowA);
                                Entry copy = newEntry(E->col, (E->val));
                                append(out, copy);
			}
		}

		while (index(rowA) >= 0 && index(rowB) >= 0) {
			Entry eA = get(rowA);
			Entry eB = get(rowB);

			if (eA->col > eB->col) {
				Entry copyB = newEntry(eB->col, 0 - eB->val);
				append(out, copyB);
				moveNext(rowB);
			} else if (eA->col < eB->col) {
				Entry copyA = newEntry(eA->col, eA->val);
				append(out, copyA);
				moveNext(rowA);
			} else {
				double diff = eA->val - eB->val;
				
				if (diff != 0) {
					Entry copy = newEntry(eA->col, diff);
					append(out, copy);
				}

				moveNext(rowA);
				moveNext(rowB);
			}
		}

		while (index(rowB) >= 0) {
			Entry eB = get(rowB);
			Entry copy = newEntry(eB->col, 0 - eB->val);
			append(out, copy);
			moveNext(rowB);
		}
		
		while (index(rowA) >= 0) {
			Entry eA = get(rowA);
			Entry copy = newEntry(eA->col, eA->val);
			append(out, copy);
			moveNext(rowA);
		}

		M->nnz += length(M->rows[r]);
	}

	return M;
}

double vectorDot(List P, List Q) {
	if (P == NULL || Q == NULL) {
                fprintf(stderr, "Error: Calling vectorDot() on NULL Matrix object(s).\n");
                exit(EXIT_FAILURE);
        }

	double sum = 0.0;

	moveFront(P);
	moveFront(Q);

	while (index(P) >= 0 && index(Q) >= 0) {
		Entry eP = get(P);
		Entry eQ = get(Q);

		if (eP->col > eQ->col) {
			moveNext(Q);
		} else if (eP->col < eQ->col) {
			moveNext(P);
		} else {
			sum += eP->val * eQ->val;
			moveNext(P);
			moveNext(Q);
		}
	}

	return sum;
}

Matrix product(Matrix A, Matrix B) {
	if (A == NULL || B == NULL) {
                fprintf(stderr, "Error: Calling product() on NULL Matrix object(s).\n");
                exit(EXIT_FAILURE);
	}

	Matrix M = newMatrix(A->size);
	Matrix BT = transpose(B);

	for (int i = 1; i <= M->size; i++) {
		List row = A->rows[i];

		if (length(row) > 0) {
			for (int j = 1; j <= M->size; j++) {
				List col = BT->rows[j];

				if (length(col) > 0) {
					double dot = vectorDot(row, col);

					if (dot != 0.0) {
						Entry E = newEntry(j, dot);
						append(M->rows[i], E);
						M->nnz += 1;
					}
				}
			}
		}
	}

	freeMatrix(&BT);

	return M;
}

/*** Other Helper Functions ***/

void printMatrix(FILE* out, Matrix M) {
	if (M == NULL) {
                fprintf(stderr, "Error: Calling printMatrix() on NULL Matrix object.\n");
                exit(EXIT_FAILURE);
        }

	if (out == NULL) {
		fprintf(stderr, "Error: printMatrix() could not access output file.\n");
		exit(EXIT_FAILURE);
	}

	for (int r = 1; r <= M->size; r++) {
		List row = M->rows[r];

		if (length(row) > 0) {
			fprintf(out, "%d: ", r);

			for (moveFront(row); index(row) >= 0; moveNext(row)) {
				Entry E = get(row);
				fprintf(out, "(%d, %.1lf)%s", E->col, E->val, index(row)==length(row)-1?"":" ");
			}

			fprintf(out, "\n");
		}
	}
}
