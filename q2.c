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
 for (int i = 1; i < argc; i++) {
    Operand *stack = NULL;
    char *expression = argv[i];

    if (strlen(expression) == 0) {
      fprintf(stderr, "Error: Empty expression\n");
      continue;
    }

    for (int i = 0; i < strlen(expression); ++i) {
      if (isdigit(expression[i])) {
        double value = 0;
        while (isdigit(expression[i])) {
          value = value * 10 + (expression[i] - '0');
          i++;
        }
        i--;
        push(&stack, value);
      } else if (expression[i] == '+' || expression[i] == '-' ||
      expression[i] == '*' || expression[i] == '/') {
        if (stack == NULL || stack->next == NULL) {
          fprintf(stderr, "Error: Not enough operands for operator %c\n", expression[i]);
          break;
        }
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
      else if (expression[i] != ' ') {
        fprintf(stderr, "Error: Invalid character in expression\n");
        exit(1);
      }
    }

    if (stack == NULL) {
      fprintf(stderr, "Error: Invalid expression (empty stack)\n");
      continue;
    }
        

    printf("The value of the expression %s is: %.2f\n", expression, pop(&stack));
  }

  return 0;
}

