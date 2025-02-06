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

    // Set all value to zero

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            matrix->data[i][j] = 0;
        }
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

int sameDim(Matrix* term1, Matrix* term2){
    //Checks if they have the same dimensions
    if (term1->rows!=term2->rows||term1->cols!=term2->cols){
        // The two matrix has different dimensions
        return 0;
    }
    return 1;
}

void copyMatrix(Matrix* original, Matrix* receiver){
    // copies the matrix from original to the receiver
    if (!sameDim(original, receiver)){
        return -1;
    }

    for (int i = 0; i< original->rows; i++){
        for (int j = 0; j< original->cols; j++){
            receiver->data[i][j] = original->data[i][j];
        }
    }
}

void transpose(Matrix** matrix) {
    // Transposes a matrix
    Matrix* nmatrix = createMatrix((*matrix)->cols, (*matrix)->rows);
    
    for (int i = 0; i < (*matrix)->rows; i++){
        for (int j = 0; j < (*matrix)->cols; j++){
            nmatrix->data[j][i] = (*matrix)->data[i][j];
        }
    }

    freeMatrix(*matrix);

    *matrix = nmatrix;
}

void swap(double* a, double* b){
    // swap two doubles
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
    // prints the matrix 
    for (int i = 0; i < matrix->rows; i++){
        for(int j = 0; j < matrix->cols; j++){
            printf("%f ", matrix->data[i][j]);
        }
        printf("\n");
    }
}

Matrix* addMatrix(Matrix* term1, Matrix* term2){
    // Adds term1 and term2
    if(!sameDim(term1, term2)){
        return -1;
    }

    Matrix* sum = createMatrix(term1->rows, term1->cols);

    for(int i = 0; i < term1->rows; i++){
        for (int j = 0; j < term2->cols; j++){
            sum->data[i][j] = term1->data[i][j] + term2->data[i][j];
        }
    }
    
    return sum;
}

Matrix* sProduct(double scalar, Matrix* matrix){
    // The scalar product
    Matrix* product = createMatrix(matrix->rows, matrix->cols);

    for(int i = 0; i < matrix->rows; i++){
        for (int j = 0; j < matrix->cols; j++){
            product->data[i][j] = matrix->data[i][j]*scalar;
        }
    }
    
    return product;
}

Matrix* product(Matrix* term1, Matrix* term2){
    // The Matrix Product

    // Confirm that dimensions are compatible
    if (!(term1->cols == term2->rows)) {    return -1;  }

    Matrix* product = createMatrix(term1->rows, term2->cols);

    for (int i = 0; i < term1->rows; i++){
        for (int j = 0; j < term2->cols; j++){
            for (int k = 0; k < term2->rows; k++){
                product->data[i][j] += term1->data[i][k]*term2->data[j][k];
            }
        }
    }

    return product;
}

double determinant(Matrix* matrix){
    // Implements LUP for solving determinant

}

double detLowerTri(Matrix* matrix){
    // Implements forwards subsitution algorithm
    
    if (!isLowerTri(matrix)){   return -1;  }

    double det = 1;

    // Finds the determinant

    for(int i = 0; i < matrix->rows; i++){
        det *= matrix->data[i][i];
    }

    return det;
}

int isLowerTri(Matrix* matrix){
    
    // Checks if input is a lower triangular matrix
    for (int i = 0; i < matrix->rows; i++){
        for (int j = i; j < matrix->cols; j++){
            if (matrix->data[i][j] != 0){
                return 0;
            }
        }
    }
    return 1;
}

int isUpperTri(Matrix* matrix){
    // Checks if input is an upper triangular matrix
    for (int i = 0; i < matrix->rows; i++){
        for (int j = 0; j < i + 1; j++){
            if (matrix->data[i][j] != 0){
                return 0;
            }
        }
    }
    return 1;
}

int isSquare(Matrix* matrix){
    if (matrix->cols==matrix->rows) {return 1;}
    return 0;
}