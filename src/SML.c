#include "..\include\SML.h"

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
        exit(1);
    }

    for (int i = 0; i< original->rows; i++){
        for (int j = 0; j< original->cols; j++){
            receiver->data[i][j] = original->data[i][j];
        }
    }
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
            printf("%5.5f ", matrix->data[i][j]);
        }
        printf("\n");
    }
}

Matrix* addMatrix(Matrix* term1, Matrix* term2){
    // Adds term1 and term2
    if(!sameDim(term1, term2)){
        printf("Unable to add Matrix, the two matrix have different dimensions");
        exit(1);
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

double determinant(Matrix* matrix){
    // See if zeros exist on principle diagonal

    for (int i = 0; i < matrix->cols; i++){
        if (matrix->data[i][i] == 0) {
            return gElimDet(matrix);
        }
    }


    // Use LUP 
    Matrix* L = createMatrix(matrix->rows, matrix->cols);
    Matrix* U = createMatrix(matrix->rows, matrix->cols);
    
    LUP(matrix, L, U);

    double det = detTri(U);
    freeMatrix(L);
    freeMatrix(U);
    return det;
}

void gElim(Matrix* matrix){
    // To do. Partial pivot for better selection of leading term
    // Use Guassian elimination to obtain upper triangular form
    for (int i = 0; i < matrix->rows; i++){
        // iterate through the amount of most required columns for upper triangular form
        for (int j = i; j < matrix->rows; j++){
            // iterate through all the rows that is not in upper triangular form

            if (matrix->data[j][i] != 0){
                // Found suitable row for i'th column

                swapRow(matrix, i, j);
                sProdRow(matrix, i, 1.0/matrix->data[i][i]);
                // Pivot the row and set its leading term to 1
                matrix->data[i][i] = 1;
                // Ensures numerical stability by explicity setting the leading term to 1

                for(int k = i + 1; k< matrix->rows; k++){
                    addRow(matrix, k, i, -matrix->data[k][i]);
                    // Add to the row such that the elements below the leading term is now 0
                    matrix->data[k][i] = 0;
                    // Guarantees numerical stability by explicitly setting it to 0
                }
                break;
            }
        }
    }
}

double gElimDet(Matrix* matrix){
    if (!isSquare(matrix)) {
        printf("Unable to find determinant, Non square matrixs doesn't have a determinant");
        exit(1);
    }
    // Use Guassian elimination to obtain determinants
    int det = 1;
    Matrix* upperTri = createMatrix(matrix->rows, matrix->cols);
    copyMatrix(matrix, upperTri);

    // Use Guassian elimination to obtain upper triangular form
    for (int i = 0; i < upperTri->rows; i++){
        // iterate through the amount of most required columns for upper triangular form
        for (int j = i; j < upperTri->rows; j++){
            // iterate through all the rows that is not in upper triangular form

            if (upperTri->data[j][i] != 0){
                // Found suitable row for i'th column
                det *= -1;

                swapRow(upperTri, i, j);
                sProdRow(upperTri, i, 1.0/upperTri->data[i][i]);
                det *= 1.0/upperTri->data[i][i];
                // Pivot the row and set its leading term to 1
                upperTri->data[i][i] = 1;
                // Ensures numerical stability by explicity setting the leading term to 1

                for(int k = i + 1; k< upperTri->rows; k++){
                    addRow(upperTri, k, i, -upperTri->data[k][i]);
                    // Add to the row such that the elements below the leading term is now 0
                    upperTri->data[k][i] = 0;
                    // Guarantees numerical stability by explicitly setting it to 0
                }
                break;
            }
            return 0;
        }
    }
    
    det *= detTri(upperTri);

    freeMatrix(upperTri);

    return det;
}

void LUP(Matrix* matrix, Matrix* L, Matrix* U){
    // Check square-ness
    if (!isSquare(matrix)) {
        printf("Unable to apply LU, matrix is not square");
        exit(1);
    }

    // Check for zero's on the principle diagonal
    for (int i = 0; i < matrix->cols; i++){
        if (matrix->data[i][i] == 0) {
            printf("Unable to apply LU, zeros exist on principle diagonal");
            exit(1);
        }
    }

    // Decompose a matrix into LU form

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
        exit(1);
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

double trace(Matrix* matrix){
    if (!isSquare(matrix)){
        printf("Unable to find trace, the matrix is not square");
        exit(1);
    }
    double trace = 0;
    for(int i = 0; i < matrix->rows; i++){
        trace += matrix->data[i][i];
    }
    return trace;
}

void inputMatrix(Matrix* matrix, double array[]){
    // Input an array into a matrix
    for(int i = 0; i < matrix->rows; i++){
        for(int j = 0; j < matrix->cols; j++){
            matrix->data[i][j] = array[i*matrix->rows+j];
        }
    }
}
