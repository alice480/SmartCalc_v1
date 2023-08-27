#include "s21_smart_calc.h"

int S21_rpn_conversion(char *expression, char *rpn_expression) {
  memset(rpn_expression, '\0', 256);
  int status = 0;
  int exp_length = strlen(expression);
  if (exp_length) {
    char *exp_copy = (char *)malloc(exp_length * sizeof(char));
    s21_strncpy(exp_copy, expression, exp_length);
    status = 1;
    // stack for Dijkstra's algorithm
    struct node *stack = NULL;
    // ~ unary minus || # unary plus || M mod
    char *single_sign_operators = "()+-*/^~#M>";
    int token_length = 0;
    char *token = (char *)malloc(sizeof(char));
    for (int i = 0; exp_copy[i] && status; i++) {
      // contains a pointer to the corresponding operand
      char *is_single_sign = strchr(single_sign_operators, exp_copy[i]);
      if (is_single_sign) {
        if (token_length) {
          token = (char *)realloc(token, token_length * sizeof(char));
          s21_strncpy(token, exp_copy + i - token_length, token_length);
          // definition of what a token is: operator/operand
          // the function is implemented in the file "s21_common_func.c"
          status = s21_token_definition(token);
          // writing operators and operands to the stack and output string
          status *= s21_dijkstra_alg(&stack, rpn_expression, token,
                                     token_length, status);
          token_length = 0;
        }
        char operator[1];
        operator[0] = exp_copy[i];
        if (strchr(operator, '~') || strchr(operator, '#'))
          status = s21_dijkstra_alg(&stack, rpn_expression, operator, 1,
                                    UNARY_OPERATOR);
        else if (!strchr(operator, '>'))
          status *= s21_dijkstra_alg(&stack, rpn_expression, operator, 1,
                                     BINARY_OPERATOR);
      } else {
        token_length++;
      }
    }
    if (status)
      // adding the remaining tokens: stack -> output_string
      status = s21_dijkstra_completion(&stack, rpn_expression);
    free(token);
    free(exp_copy);
    int rpn_expression_length = strlen(rpn_expression);
    rpn_expression[rpn_expression_length] = '_';
  }
  return status;
}

int s21_dijkstra_alg(struct node **stack, char *output_line, char *token,
                     int token_length, int definition) {
  int status = 1;
  if (definition == OPERAND) {
    // copying operands to the output string
    s21_strcat(output_line, "_");
    s21_strcat(output_line, token);
  } else {
    if (token[0] == '(') {
      // a copy of the string to be added to the stack
      char *copy = (char *)malloc(token_length * sizeof(char));
      s21_strncpy(copy, token, 1);
      status = push(copy, 1, stack);
    } else if (token[0] == ')') {
      char *last_operator = peek_operation(stack);
      while (*stack && last_operator[0] != '(') {
        strcat(output_line, "_");
        strcat(output_line, last_operator);
        status = pop(stack);
        if (*stack)
          last_operator = peek_operation(stack);
      }
      if (*stack)
        status = pop(stack);
    } else {
      if (*stack) {
        // operations in stack with higher or equal priority -> output_string
        char *last_operator = peek_operation(stack);
        int last_operator_priority = s21_priority_determining(last_operator);
        int current_operator_priority = s21_priority_determining(token);
        while (current_operator_priority <= last_operator_priority && *stack) {
          s21_strcat(output_line, "_");
          s21_strcat(output_line, last_operator);
          status = pop(stack);
          if (*stack) {
            last_operator = peek_operation(stack);
            last_operator_priority = s21_priority_determining(last_operator);
          }
        }
      }
      // a copy of the string to be added to the stack
      char *copy = (char *)malloc(token_length * sizeof(char));
      s21_strncpy(copy, token, token_length);
      status = push(copy, 1, stack);
    }
  }
  return status;
}

/*  return codes
  0 - ERROR
  1 - (
  2 - BINARY OPERATORS +|-
  3 - BINARY OPERATORS *|/|M
  4 - UNARY  OPERATORS cos|sin|...|log|~ */
int s21_priority_determining(char *current_operator) {
  int priority = TOKEN_DOESNT_EXIST;

  char *unary_operators = "sin cos tan asin acos atan sqrt log ln ~ #";
  char *is_unary_operator = strstr(unary_operators, current_operator);

  if (is_unary_operator)
    priority = 4;
  else {
    if (current_operator[0] == '(')
      priority = 1;
    else if (current_operator[0] == '+' || current_operator[0] == '-')
      priority = 2;
    else if (current_operator[0] == '*' || current_operator[0] == '/' ||
             current_operator[0] == 'M')
      priority = 3;
  }
  return priority;
}

int s21_dijkstra_completion(struct node **stack, char *output_line) {
  int status = 1;
  char *token;
  while (*stack) {
    token = (*stack)->operation;
    s21_strcat(output_line, "_");
    s21_strcat(output_line, token);
    status = pop(stack);
  }
  return status;
}
