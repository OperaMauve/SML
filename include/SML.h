#ifndef SML_H
#define SML_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int rows;
    int cols;
    double** data;
} Matrix;

Matrix* createMatrix(int rows, int cols);

typedef struct {
    int size;
    double** data;
} SquareMatrix;

void transposeSquare(Matrix* matrix);
void transpose(Matrix** matrix);
void swap(double* a, double* b);
void freeMatrix(Matrix* matrix);
void printMatrix(Matrix* matrix);
#endif

