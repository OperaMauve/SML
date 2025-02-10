#include "..\include\SML.h"

// Step 1, write lexer
// Step 2, write parser
// Step 3, win

void applyFunction(Matrix* matrix, char *function){
    // Apply function to each element on the matrix
    //lexer
    instructions* instruct = (instructions*)malloc(sizeof(instructions));

    for (int i = 0; i < sizeof(function)/sizeof(char); i++){
        // categories characters, and then if there is a different category of characters in the next character, then switch to the next token
        // category 0, numbers
        // category 1, operator
        // category 2, brackets
        // category 3, element x

    }
}

void freeInstruct(instructions* Instruct){
    while (Instruct->token != '\0'){
        free(Instruct)
        Instruct = Instruct->next;
    }
}

int categorise(char character){
    if (isNumber(character)){
        return 0;
    }
    if (isOperator(character)){
        return 1;
    }
    if (character == '(' || character == ')'){
        return 2;
    }
    if (character == 'x'){
        return 3;
    }
    printf("%s is not recognised", character);
    return -1;
}