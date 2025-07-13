#include "..\include\SML.h"

int main(){

    Matrix* try = createMatrix(4,4);
    double in[] = {1,0,3,-1,0,1,1,-2,0,0,0,0,0,0,0,0};
    
    inputMatrix(try, in);

    Matrix** kernels = kernel(try); //returns a pointer to array of pointers
    //return int of number of basis elements
    //change pointer to point to the new stuff

    Matrix** img = rowSpace(try);
    printMatrix(img[1]);
    printMatrix(try);


    return 0;
}