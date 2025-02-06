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
        printf("Unable to copy Matrix, the two matrix have different dimensions");
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
        printf("Unable to add Matrix, the two matrix have different dimensions");
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
    if (!(term1->cols == term2->rows)) {
        printf("Unable to multiply matrices, their dimensions are incompatible");
        return -1;
    }

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
    // See if zeros exist on principle diagonal

    for (int i = 0; i < matrix->cols; i++){
        if (matrix->data[i][i] == 0) {
            return gElimDet(matrix);
        }
    }


    // Use LUP 
    Matrix* L;
    Matrix* U;
    
    LUP(matrix, L, U);

    return determinant(L)*determinant(U);
}

void gElim(Matrix* matrix){
    // Use Guassian elimination to obtain RREF
    for (int i = 0; i< matrix->rows; i++){
        for(int j = i; j< matrix->rows; j++){
            if (matrix->data[j][i] != 0){
                swapRow(matrix, i, j);

                sProdRow(matrix, i, 1/matrix->data[i][i]);

                for(int k = i + 1; k< matrix->rows; k++){
                    addRow(matrix, k, i, -matrix->data[k][i]);
                    matrix->data[k][i] = 0;
                }
            }
        }
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

double gElimDet(Matrix* matrix){
    if (!isSquare(matrix)) {
        printf("Unable to find determinant, Non square matrixs doesn't have a determinant");
        return -1;  
    }
    // Use Guassian elimination to obtain determinants
    int det = 1;
    Matrix* RREF = createMatrix(matrix->rows, matrix->cols);

    for (int i = 0; i< RREF->rows; i++){
        for(int j = i; j< RREF->rows; j++){
            if (RREF->data[j][i] != 0){
                swapRow(RREF, i, j);
                if (i != j){
                    det *= -1;
                }

                sProdRow(RREF, i, 1/RREF->data[i][i]);
                det *= 1/RREF->data[i][i];

                for(int k = i + 1; k< RREF->rows; k++){
                    addRow(RREF, k, i, -RREF->data[k][i]);
                    RREF->data[k][i] = 0;
                }
            }
        }
    }
    
    det *= detTri(RREF);

    freeMatrix(RREF);

    return det;
}

void squarify(Matrix** matrix){
    // Make the matrix square
    int a = max((*matrix)->rows,(*matrix)->cols);
    Matrix* Nmatrix = createMatrix(a , a);
    for(int i = 0; i < a; i++){
        for(int j = 0; j < a ; j++){
            Nmatrix->data[i][j] = (*matrix)->data[i][j];
        }
    }
}

int max(int a, int b){
    // Returns the greater between a and b, if they are equal, return a
    if ( a < b){
        return b;
    }
    return a;
}

int min(int a, int b){
    // Returns the lesser between a and b, if they are equal, return a
    if ( a > b){
        return b;
    }
    return a;
}

double maxDouble(double a, double b){
    // Returns the greater between a and b, if they are equal, return a
    if ( a < b){
        return b;
    }
    return a;
}

double minDouble(double a, double b){
    // Returns the lesser between a and b, if they are equal, return a
    if ( a > b){
        return b;
    }
    return a;
}

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


void LUP(Matrix* matrix, Matrix* L, Matrix* U){
    // Check square-ness
    if (!isSquare(matrix)) {
        printf("Unable to apply LU, matrix is not square");
        return -1;
    }

    // Check for zero's on the principle diagonal
    for (int i = 0; i < matrix->cols; i++){
        if (matrix->data[i][i] == 0) {
            printf("Unable to apply LU, zeros exist on principle diagonal");
            return -1;
        }
    }

    // Decompose a matrix into LU form
    L = createMatrix(matrix->rows, matrix->cols);
    U = createMatrix(matrix->rows, matrix->cols);

    for (int i = 0; i < matrix->rows; i++){
        L->data[i][i] = 1;
        U->data[i][i] = matrix->data[i][i];

        for (int j = i + 1; j < matrix->cols; j++){
            L->data[i][j] = 0;
            L->data[j][i] = matrix->data[j][i]/matrix->data[i][i];
            U->data[j][i] = 0;
            U->data[i][j] = matrix->data[i][j];
        }
    }
}

double detTri(Matrix* matrix){
    // Implements forwards subsitution algorithm
    
    if (!isLowerTri(matrix)||!isUpperTri(matrix)){  
        printf("Unable to find determinant, Matrix isn't triangular");
        return -1;
    }

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