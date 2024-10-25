#include "q2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char** argv){

  if (argc != 2) {
    printf("Usage: %s <expression>\n", argv[0]);
    return 1;
  }

  char *expression = argv[1];


  //Pointer to the stack
  int i = 0;
  Operand * stack = NULL;
  

  //Loop through the second command line arguement, containing the operands and the numbers 
  for(i = 0; i < strlen(argv[1]); ++i){

    if (isdigit(expression[i])) {
      // Handle multi-digit numbers
      double value = 0;
      while (isdigit(expression[i])) {
        value = value * 10 + (expression[i] - '0');
        i++;
      }
    } 
    else if (expression[i] == '+' || expression[i] == '-' ||
      expression[i] == '*' || expression[i] == '/') {
      double operand2 = pop(&stack);
      double operand1 = pop(&stack);
      double result;

      switch (expression[i]) {
        case '+': result = operand1 + operand2; break;
        case '-': result = operand1 - operand2; break;
        case '*': result = operand1 * operand2; break;
        case '/':
        if (operand2 == 0) {
          fprintf(stderr, "Error: Division by zero\n");
          exit(1);
        }
      result = operand1 / operand2;
      break;
      }
    push(&stack, result);
  }
    /*Remember data passed from command line is a char data type*/
    
    /* **Hint** You will need to perform stack operations that 
    we implemented here to achieve the expected output */
    
 
  }
  
  printf("The value of the expression is: %.2f\n", pop(&stack));

  return 0;
}

