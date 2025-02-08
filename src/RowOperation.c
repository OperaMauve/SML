#include <SML.h>

void swapRow(Matrix* matrix, int row1, int row2){
    // Swaps row1 with row2
    double temp;
    for(int i = 0; i < matrix->cols; i++){
        temp = matrix->data[row1][i];
        matrix->data[row1][i] = matrix->data[row2][i];
        matrix->data[row2][i] = temp;
    }
}

void swapCol(Matrix* matrix, int col1, int col2){
    // Swaps col1 with col2
    double temp;
    for(int i = 0; i < matrix->rows; i++){
        temp = matrix->data[i][col1];
        matrix->data[i][col1] = matrix->data[i][col2];
        matrix->data[i][col2] = temp;
    }
}

void sProdCol(Matrix* matrix, int column, double scalar){
    // Multiply a column of the matrix by a scalar
    for(int i = 0; i < matrix->rows; i++){
        matrix->data[i][column] *= scalar;
    }
}

void sProdRow(Matrix* matrix, int row, double scalar){
    // Multiply a row of the matrix by a scalar
    for(int i = 0; i < matrix->cols; i++){
        matrix->data[row][i] *= scalar;
    }
}

void addCol(Matrix* matrix, int addend1, int addend2, double scalar){
    // Add scalar times addend2'th col to addend1'th row in matrix
    for (int i = 0; i< matrix->rows; i++){
        matrix->data[i][addend1] += scalar*matrix->data[i][addend2];
    }
}

void addRow(Matrix* matrix, int addend1, int addend2, double scalar){
    // Add scalar times addend2'th row to addend1'th row in matrix
    for (int i = 0; i< matrix->cols; i++){
        matrix->data[addend1][i] += scalar*matrix->data[addend2][i];
    }
}