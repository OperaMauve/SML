#include "..\include\SML.h"

// Wrapped Stack

void createStack(Stack *output){
    // Memory safe stack definition
    output = (Stack*)malloc(sizeof(Stack));
    if (output == NULL) {
    	printf("Out of memory defining Stack");
    }
    output->top = -1;
    output->element = (char*)malloc(sizeof(char));
}

void addStack(Stack *output, char addend){
    // Add addend to Stack
    output->top += 1;
    output->element = (char*)realloc(output->element, sizeof(char)*(output->top+1));
    output->element[output->top] = addend;
}

void freeStack(Stack *freed){
	// free Stack and it's subsidaries
    free(freed->element);
    free(freed);
}

void removeStack(Stack *output){
	// remove one from a Stack
    output->top -= 1;
    output->element = (char*)realloc(output->element, sizeof(char)*(output->top+1));    
}

void pullAllStack(Stack *addend, Stack *addon){
	// pull elements from addon and add them to addend
    for(int i = 0; i < addon->top; i++{
        addStack(addend, addon->element[i]);
    }
}
