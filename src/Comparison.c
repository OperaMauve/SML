#include "..\include\SML.h"

int max(int a, int b){
    // Returns the greater between a and b, if they are equal, return a
    if ( a < b){
        return b;
    }
    return a;
}

int min(int a, int b){
    // Returns the lesser between a and b, if they are equal, return a
    if (a > b){
        return b;
    }
    return a;
}

double maxDouble(double a, double b){
    // Returns the greater between a and b, if they are equal, return a
    if (a < b){
        return b;
    }
    return a;
}

double minDouble(double a, double b){
    // Returns the lesser between a and b, if they are equal, return a
    if (a > b){
        return b;
    }
    return a;
}
