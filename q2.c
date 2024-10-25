
#include "q2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char** argv) {
  // Verify correct number of command-line arguments
  if (argc != 2) {
      fprintf(stderr, "Incorrect usage. Please provide: %s <expression>\n", argv[0]);
      return 1;
  }

  // Initialize stack and get the expression from command line
  Operand *calculation_stack = NULL;
  char *input_expression = argv[1];

  // Check for blank expression
  int is_blank = 1;
  for (int i = 0; input_expression[i] != '\0'; i++) {
    if (!isspace((unsigned char)input_expression[i])) {
      is_blank = 0;
        break;
    }
  }
  if (is_blank) {
    fprintf(stderr, "Error: Blank expression provided\n");
    return 1;
  }
  // Process the input: remove any spaces from the expression
  int clean_index = 0;
  for (int read_index = 0; input_expression[read_index] != '\0'; read_index++) {
    if (input_expression[read_index] != ' ') {
      input_expression[clean_index++] = input_expression[read_index];
    }
  }
  input_expression[clean_index] = '\0';

  // Check for empty expression after space removal
  if (strlen(input_expression) == 0) {
    fprintf(stderr, "Error: The provided expression is empty\n");
    return 1;
  }

  // Evaluate the postfix expression
  for (int i = 0; input_expression[i] != '\0'; i++) {
    if (isdigit(input_expression[i])) {
      // Convert character digit to double and push to stack
      double numeric_value = input_expression[i] - '0';
      push(&calculation_stack, numeric_value);
    } 
    else if (strchr("+-*/", input_expression[i])) {
    // Handle operators
    if (calculation_stack == NULL || calculation_stack->next == NULL) {
      fprintf(stderr, "Error: Insufficient operands for operator %c\n", input_expression[i]);
      return 1;
    }
    double second_operand = pop(&calculation_stack);
    double first_operand = pop(&calculation_stack);
    double operation_result;

    // Perform the operation
    switch (input_expression[i]) {
      case '+': operation_result = first_operand + second_operand; break;
      case '-': operation_result = first_operand - second_operand; break;
      case '*': operation_result = first_operand * second_operand; break;
      case '/':
        if (second_operand == 0) {
          fprintf(stderr, "Error: Division by zero is not allowed\n");
          return 1;
        }
        operation_result = first_operand / second_operand;
        break;
    }
    push(&calculation_stack, operation_result);
    } 
    
    else {
      fprintf(stderr, "Error: Unrecognized symbol '%c' in expression\n", input_expression[i]);
      return 1;
    }
  }

  // Verify the final state of the stack
  if (calculation_stack == NULL || calculation_stack->next != NULL) {
    fprintf(stderr, "Error: The expression is malformed (mismatched operands and operators)\n");
    return 1;
  }

  // Output the final result
  printf("%.2f\n", pop(&calculation_stack));

  return 0;
}

