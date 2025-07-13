#include "..\include\SML.h"

int main(){
    printf("Prints 5x5 matrix below\n");
    Matrix* eyes = eye(5);
    printMatrix(eyes);
    printf("Inputs Matrixs and find its row reduced form and gives the determinant\n");
    Matrix* matrix = eye(3);
    printMatrix(matrix);
    printf("Swaps first and second colomn\n");
    swapCol(matrix, 0, 1);
    printMatrix(matrix);
    printf("determinant = %lf\n", determinant(matrix));
    printf("RREF is\n");
    gElim(matrix);
    printMatrix(matrix);
    return 0;
}