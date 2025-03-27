#ifndef SML_H
#define SML_H

#include <stdio.h>
#include <stdlib.h>
//Data
typedef struct {
    char* element;
    int top;
} Stack;

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

// SML
void inputMatrix(Matrix* matrix, double array[]);
Matrix* createMatrix(int rows, int cols);
void transposeSquare(Matrix* matrix);
void swap(double* a, double* b);
void freeMatrix(Matrix* matrix);
void printMatrix(Matrix* matrix);
int sameDim(Matrix* term1, Matrix* term2);
void copyMatrix(Matrix* original, Matrix* receiver);
void freeMatrix(Matrix* matrix);
void printMatrix(Matrix* matrix);
Matrix* addMatrix(Matrix* term1, Matrix* term2);
Matrix* sProduct(double scalar, Matrix* matrix);
double determinant(Matrix* matrix);
void gElim(Matrix* matrix);
double gElimDet(Matrix* matrix);
void LUP(Matrix* matrix, Matrix* L, Matrix* U);
double detTri(Matrix* matrix);
int isLowerTri(Matrix* matrix);
int isUpperTri(Matrix* matrix);
int isSquare(Matrix* matrix);
double trace(Matrix* matrix);
Matrix* eye(int size);

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

/*Function
void applyFunction(Matrix* matrix, char *function);
int categorise(char character);*/

//Conditions
int isNumber(char character);
int isOperator(char character);
int lexerPriority(char a);


#endif
