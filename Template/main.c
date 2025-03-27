#include "..\include\SML.h"

int main(){

    Matrix* try = createMatrix(3,3);
    double in[] = {1,2,3,5,4,3,1,0,1};
    inputMatrix(try, in);
    //printMatrix(try);
    double det = gElimDet(try);
    printf("\n %lf",det);

    return 0;
}