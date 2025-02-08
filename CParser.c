#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//-----stack implementation.----- (based off gfg)
typedef struct
{
    //arbritrarly high stack size
    int list[12000];
    int top;
} Stack;


//init stack by accepting a type stack pointing back to the struct def
void initialize(Stack *stack){
    //set the index so the stack is empty
    stack -> top = -1;
}
bool isEmpty(Stack *stack){
    //if the top is -1 (as defined in the initalize) then the stack is empty
    return stack -> top == -1;
}

//push method
void push(Stack *stack, char character){

    // (->) accesses the struct variables, so it would increment the top pointer
    //and add character to the list by setting the value at the pointer to the char
    stack -> list[++stack -> top] = character;
}

//pop method
int pop(Stack *stack){
    if (isEmpty(stack)){
        return -1;
    }
    //set the pointer to 1 less, so that when the next char comes in it will 
    //over write where the pointer was
    stack -> top--;

}

//peek method
char peek (Stack *stack){
    if (isEmpty(stack)){
        return -1;
    }
    return (stack -> list[stack->top]);
}




int main(void){
    
    //initialize the stack here
    Stack s;
    initialize(&s);

    //current line
    int line = 1;


    //get file
    char fileName[255]="";
    printf("please enter a filename: ");
    scanf("%s", fileName);

    FILE* file;
    file = fopen(fileName, "r");
    
    //print error if file doesn't exist
    if (file == NULL){
        printf("error: file not found");
        return 0;
    }

    //c is the current character in the file being read
    char c;
    //feof is the end charactrer of the file
    while ((c = fgetc(file)) != EOF)
    {
        //if c is a end of line, add 1 to line count
        if (c == '\n'){
            line++;
        }
            
        
        

        //if c is a opening bracket, add to the stack
        if(( c == '(') || (c == '{') || ( c == '[')){
            push(&s, c);
        }

        //else if c is a closing bracket character, check to see if it matches
        //the stack character, if not print error message

        switch(c){
            case ')':
                if (peek(&s) != '('){
                    printf(" error: missing a closing ) on line %d\n", line);
                    break;
                }
                pop(&s);
                break;
            case '}':
                if (peek(&s) != '{'){
                    printf("error: missing a closing } on line %d\n", line);
                    break;
                }
                pop(&s);
                break;
            case ']':
                if (peek(&s) != '['){
                    printf("error: missing a closing ] on line %d \n", line);
                    break;
                }
                pop(&s);
                break;

        }
       
    

    

    } 
    printf("lines: %d", line);
    fclose(file);
    return 0;

}