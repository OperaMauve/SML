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

// Comparison
int max(int a, int b);
int min(int a, int b);
double maxDouble(double a, double b);
double minDouble(double a, double b);

// Row Operations
void swapRow(Matrix* matrix, int row1, int row2);
void swapCol(Matrix* matrix, int col1, int col2);
void sProdCol(Matrix* matrix, int column, double scalar);
void sProdRow(Matrix* matrix, int row, double scalar);
void addCol(Matrix* matrix, int addend1, int addend2, double scalar);
void addRow(Matrix* matrix, int addend1, int addend2, double scalar);

//Matrix Operation
void transpose(Matrix** matrix);
Matrix* product(Matrix* term1, Matrix* term2);
void squarify(Matrix** matrix);

#endif

