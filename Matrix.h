// --------------------------------------------------------------
// Nicolas Corfmat
// CruzID: ncorfmat
// Assignment: pa4
// --------------------------------------------------------------

#ifndef MATRIX_H_
#define MATRRIX_H_

#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "List.h"

/*** Constructors-Destructors ***/

typedef struct MatrixObj* Matrix;

Matrix newMatrix(int n);

void freeMatrix(Matrix* pM);

/*** Access Functions ***/

int size(Matrix M);

int NNZ(Matrix M);

int equals(Matrix A, Matrix B);

/*** Manipulation Procedures ***/

void makeZero(Matrix M);

void changeEntry(Matrix M, int i, int j, double x);

/*** Matrix Arithmetic Operations ***/

Matrix copy(Matrix A);

Matrix transpose(Matrix A);

Matrix scalarMult(double x, Matrix A);

Matrix sum(Matrix A, Matrix B);

Matrix diff(Matrix A, Matrix B);

Matrix product(Matrix A, Matrix B);

/*** Other Helper Functions ***/

void printMatrix(FILE* out, Matrix M);

#endif
