#include "..\include\SML.h"

void transpose(Matrix** matrix){
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

Matrix* product(Matrix* term1, Matrix* term2){
    // The Matrix Product

    // Confirm that dimensions are compatible
    if (!(term1->cols == term2->rows)) {
        printf("Unable to multiply matrices, their dimensions are incompatible");
        exit(1);
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

