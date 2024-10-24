#include "q2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char** argv){

  //Pointer to the stack
  int i = 0;
  Operand * stack = NULL;
  


  //Loop through the second command line arguement, containing the operands and the numbers 
  for(i = 0; i < strlen(argv[1]); ++i){

    /*Remember data passed from command line is a char data type*/
    
    /* **Hint** You will need to perform stack operations that 
    we implemented here to achieve the expected output */

    // addition here
    if(argv[1][i] == '+'){
      double a = pop(&stack);
      double b = pop(&stack);
      push(&stack, a + b);
    }
    // subtraction here
    else if(argv[1][i] == '-'){
      double a = pop(&stack);
      double b = pop(&stack);
      push(&stack, b - a);
    }
    // multiplication here
    else if(argv[1][i] == '*'){
      double a = pop(&stack);
      double b = pop(&stack);
      push(&stack, a * b);
    }
    // division here
    else if(argv[1][i] == '/'){
      double a = pop(&stack);
      double b = pop(&stack);
      push(&stack, b / a);
    }
    // If the character is a number, push it onto the stack here
    else if(argv[1][i] != ' '){
      push(&stack, argv[1][i] - '0');
    }
  }
  printf("The result is: %.2f\n", pop(&stack));
  
  

  return 0;
}