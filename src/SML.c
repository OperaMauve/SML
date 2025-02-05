#include "SML.h"

Matrix* createMatrix(int rows, int cols){
    // creates a matrix
    Matrix* matrix = (Matrix*)malloc(sizeof(Matrix));
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->data = (double**)malloc(rows*sizeof(double*));
    for (int i = 0; i < rows; i++){
        matrix->data[i] = (double*)calloc(cols,sizeof(double));
    }
    return matrix;
}

void transposeSquare(Matrix* matrix){
    // Transposes a square matrix
    for (int i = 0; i < matrix->rows; i++){
        for(int j = i + 1; j < matrix->cols; j++){
            swap(&matrix->data[i][j], &matrix->data[j][i]);
        }
    }
}

void copyMatrix(Matrix* original, Matrix* receiver){
    // copies the matrix from original to the receiver
    if (original->rows!=receiver->rows||original->cols!=reciever->cols){
        // The two matrix has different dimensions
        return -1;
    }

    for (int i = 0; i< original->rows; i++){
        for (int j = 0; j< original->cols; j++){
            receiver->data[i][j] = original->data[i][j] 
        }
    }
}

void transpose(Matrix* matrix) {
    // Transposes a matrix
    Matrix* nmatrix = createMatrix(matrix->cols, matrix->rows);
    
    for (int i = 0; i < matrix->rows; i++){
        for (int j = 0; j < matrix->cols; j++){
            nmatrix->data[j][i] = matrix->data[i][j];
        }
    }

    freeMatrix(*matrix);

    *matrix = nmatrix;
}

void swap(double* a, double* b){
    # swap two doubles
    double i = *a;
    *a = *b;
    *b = i;
}

void freeMatrix(Matrix* matrix){
    // Frees the memory used by the matrix
    for(int i = 0; i < matrix->rows; i++){
        free(matrix->data[i]);
    }
    free(matrix->data);
    free(matrix);
    matrix = NULL;
}

void printMatrix(Matrix* matrix){
    for (int i = 0; i < matrix->rows; i++){
        for(int j = 0; j < matrix->cols; j++){
            printf("%f ", matrix->data[i][j]);
        }
        printf("\n");
    }
}