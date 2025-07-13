#include "..\include\SML.h"

// dont wanna make vector struct - idk how to inherit matrix properties w/out OOP built into c
// default representation as col. vector
// added vector bool to matrix struct

Matrix* createVector(int len){
    Matrix* vector = createMatrix(len, 0);
    return vector;
}

void inputVector(Matrix* arr, float data[]){
    for(int i = 0; i < arr->rows; i++){
        arr->data[i][0] = data[i];
    }
}



