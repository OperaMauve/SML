#include "..\include\SML.h"

// Wrapped Stack

void createStack(Stack *output){
    output = (Stack*)malloc(output, sizeof(Stack));
    if (output == NULL) {
    	printf("Out of memory defining Stack");
    }
    output->element = (char*)malloc(
}