#include "s21_smart_calc.h"

int s21_calculation(char *expression, double *result) {
  int status = 1;
  char *rpn_expression = (char *)malloc(255 * sizeof(char));
  // a string with unary minuses "-" replaced by "~"
  char *new_expression = string_overwriting(expression);
  status *= S21_rpn_conversion(new_expression, rpn_expression);
  status *= s21_token_splitting(rpn_expression, result);
  free(new_expression);
  free(rpn_expression);
  return status;
}

char *string_overwriting(char *expression) {
  int expression_length = strlen(expression);
  char *str_with_beginning_operator =
      (char *)malloc((expression_length + 1) * sizeof(char));
  str_with_beginning_operator[0] = '<';
  for (int i = 1; i <= expression_length; i++)
    str_with_beginning_operator[i] = expression[i - 1];
  int str_with_bo_length = strlen(str_with_beginning_operator);
  if ((str_with_bo_length - expression_length) > 1)
    for (int i = str_with_bo_length - 1; expression_length < i; i--)
      str_with_beginning_operator[i] = '\0';
  char *new_expression = (char *)calloc(1, 1);
  char *unary_sym_predecessors = "<(+-*/^";

  int new_expression_length = 0;
  int index = 1;
  while (str_with_beginning_operator[index]) {
    new_expression_length++;
    new_expression = (char *)realloc(new_expression, new_expression_length);
    if (str_with_beginning_operator[index] == 'm') {
      new_expression[new_expression_length - 1] = 'M';
      index += 3;
    } else {
      if (str_with_beginning_operator[index] == '-' &&
          strchr(unary_sym_predecessors,
                 str_with_beginning_operator[index - 1]))
        new_expression[new_expression_length - 1] = '~';
      else if (str_with_beginning_operator[index] == '+' &&
               strchr(unary_sym_predecessors,
                      str_with_beginning_operator[index - 1]))
        new_expression[new_expression_length - 1] = '#';
      else
        new_expression[new_expression_length - 1] =
            str_with_beginning_operator[index];
      index++;
    }
  }
  new_expression = (char *)realloc(new_expression, new_expression_length + 1);
  new_expression[new_expression_length] = '>';
  free(str_with_beginning_operator);
  return new_expression;
}

int s21_token_splitting(char *rpn_expression, double *result) {
  int status = 1;
  // stack for performing operations on numbers
  struct node *stack = NULL;

  int token_length = 0;
  char *token = (char *)malloc(sizeof(char));
  for (int i = 0; rpn_expression[i] && status; i++) {
    if (rpn_expression[i] == '_') {
      if (token_length) {
        token = (char *)realloc(token, token_length * sizeof(char));
        s21_strncpy(token, rpn_expression + (i - token_length), token_length);
        status = s21_postfix_calculation(token, &stack);
      }
      token_length = 0;
    } else
      token_length++;
  }
  *result = pop(&stack);
  while (stack) {
    pop(&stack);
    *result = 0;
    status = 0;
  }
  free(token);
  return status;
}

int s21_postfix_calculation(char *token, struct node **stack) {
  // definition of what a token is: (operand)/(operator, function)
  // the function is implemented in the file "s21_common_func.c"
  int status = s21_token_definition(token);
  if (status == OPERAND) {
    double number = s21_convert_str_to_double(token);
    push(NULL, number, stack);
  } else if (status == BINARY_OPERATOR) {
    // getting two operands from the top of the stack
    double number1, number2;
    number2 = pop(stack);
    number1 = pop(stack);
    // passing operands and operator to perform the operation
    double result = s21_performing_operations(number1, number2, token);
    status *= (!isnan(result));
    // putting the result on the stack with numbers
    status = push(NULL, result, stack);
  } else if (status == UNARY_OPERATOR) {
    double number = pop(stack);
    double result = s21_performing_function(number, token);
    status *= (!isnan(result));
    status = push(NULL, result, stack);
  }
  return status;
}

double s21_convert_str_to_double(char *token) {
  double number = strtod(token, NULL);
  return number;
}

double s21_performing_operations(double number1, double number2,
                                 char *operand) {
  double result = 0;
  if (strchr(operand, '+'))
    result = number1 + number2;
  else if (strchr(operand, '-'))
    result = number1 - number2;
  else if (strchr(operand, '*'))
    result = number1 * number2;
  else if (strchr(operand, '/'))
    if (number2)
      result = number1 / number2;
    else
      result = NAN;
  else if (strchr(operand, '^'))
    result = pow(number1, number2);
  else if (strchr(operand, 'M'))
    result = fmod(number1, number2);
  return result;
}

double s21_performing_function(double number, char *function) {
  double result = 0;
  if (strstr(function, "asin"))
    result = asin(number);
  else if (strstr(function, "sin"))
    result = sin(number);
  else if (strstr(function, "acos"))
    result = acos(number);
  else if (strstr(function, "cos"))
    result = cos(number);
  else if (strstr(function, "atan"))
    result = atan(number);
  else if (strstr(function, "tan"))
    result = tan(number);
  else if (strstr(function, "sqrt"))
    result = sqrt(number);
  else if (strstr(function, "ln"))
    result = log(number);
  else if (strstr(function, "log"))
    result = log10(number);
  else if (strstr(function, "~"))
    result = number * (-1);
  else if (strstr(function, "#"))
    result = number;
  return result;
}
