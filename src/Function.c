#include "..\include\SML.h"

// Lexer (Infix >>> Polish)

void lexer(Stack* instruction, Stack* output){

    Stack* buffer = (Stack*)malloc(sizeof(Stack));
    
    // Load initial value
    buffer->element = (char*)malloc(sizeof(char));
    output->element = (char*)malloc(sizeof(char));

    // Set top to negative one
    buffer->top = -1;
    output->top = -1;

    int max = instruction->top;
    int prevWeight = 0;

    for (int i = 0; i < max; i++){
        if (isNumber(instruction->element[i])){
            // push to the output
            output->top += 1;
            output->element = (char*)realloc(output->element, sizeof(char)*(output->top+1));
            output->element[output->top] = instruction->element[i];
        } else if(lexerPriority(instruction->element[i]) == 3){
            // Bracket starts
            i++;
            // Start new input stack
            Stack* input = (Stack*)malloc(sizeof(Stack));
            input->element = (char*)malloc(sizeof(char));
            input->top = 0;
            // Define bracket output stack
            Stack* bracOut = (Stack*)malloc(sizeof(Stack));
            
            // Add all elements within the bracket to a new input stack
            while(lexerPriority(instruction->element[i]) != 3){
                input->top += 1;
                input->element = (char*)realloc(input->element, sizeof(char)*(input->top+1)); 
                input->element[input->top] = instruction->element[i]; 
                i++;
            }
            i--;

            input->top -= 1;

            // Add recursion to infix the output.
            lexer(input, bracOut);

            // Push BracOut into Output
            for (int j = 0; j < bracOut->top; j++){\
                output->top += 1;
                output->element = (char*)realloc(output->element, sizeof(char)*(output->top+1));
                output->element[output->top] = bracOut->element[j];
            }

            // Free BracOut
            free(bracOut->element);
            free(bracOut);
            prevWeight = 0;
        } else if(lexerPriority < prevWeight) {
            // Push buffer to output
            for (int j = 0; j < buffer->top; j++){
                output->top += 1;
                output->element = (char*)realloc(output->element, sizeof(char)*(output->top+1));
                output->element[output->top] = buffer->element[j];
            }

            // Free the Buffer
            free(buffer->element);
            free(buffer);

            // Renew the Buffer
            Stack* buffer = (Stack*)malloc(sizeof(Stack));
            buffer->element = (char*)malloc(sizeof(char));
            buffer->top = -1;

            // Push element into buffer
            buffer->top += 1;
            buffer->element = (char*)realloc(buffer->element, sizeof(char)*(buffer->top+1));
            buffer->element[buffer->top] = instruction->element[i];
            
            prevWeight = lexerPriority(instruction->element[i]);
        } else {
            // Add to buffer
            buffer->top += 1;
            buffer->element = (char*)realloc(buffer->element, sizeof(char)*(buffer->top+1));
            buffer->element[buffer->top] = instruction->element[i];
            prevWeight = lexerPriority(instruction->element[i]);
        }
    }
}

void applyFunction(Matrix* matrix, char *function){
    // Apply function to each element on the matrix
    //lexer

    for (int i = 0; i < sizeof(function)/sizeof(char); i++){
        // categories characters, and then if there is a different category of characters in the next character, then switch to the next token
        // category 0, numbers
        // category 1, operator
        // category 2, brackets
        // category 3, element x

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

int lexerPriority(char a){
    // Returns the priority of the binary operand
    if (a == '+' || a == '-'){
        return 1;
    }
    if (a == '*' || a == '/'){
        return 2;
    }
    if (a == '(' || a == ')'){
        return 3;
    }
    printf("Invalid Syntax");
    return -1;
} 