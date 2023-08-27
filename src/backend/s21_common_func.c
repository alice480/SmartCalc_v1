#include "s21_smart_calc.h"

/*  return codes
    0 - ERROR
    1 - BINARY_OPERATOR
    2 - UNARY_OPERATOR
    3 - OPERAND  */
int s21_token_definition(char *token) {
  int definition = TOKEN_DOESNT_EXIST;

  char *binary_operators = "+-*/^M";
  // contains a pointer to the corresponding operand
  char *is_binary_operator = strstr(binary_operators, token);

  char *unary_operators = "sin cos tan asin acos atan sqrt log ln ~ #";
  // contains a pointer to the corresponding substring of the function
  char *is_unary_operator = strstr(unary_operators, token);

  int integer;
  double real;
  // contain 1 if token is a number
  int is_real = sscanf(token, "%lf", &real);
  int is_int = sscanf(token, "%d", &integer);

  if (is_binary_operator)
    definition = BINARY_OPERATOR;
  else if (is_unary_operator)
    definition = UNARY_OPERATOR;
  else if (is_real || is_int)
    definition = OPERAND;
  return definition;
}

void s21_strncpy(char *destination, char *source, int length) {
  destination[0] = '\0';
  for (int i = 0; source[i] && i < length; i++) {
    destination[i] = source[i];
    destination[i + 1] = '\0';
  }
}

void s21_strcat(char *destination, char *source) {
  int code = destination[0] - 'A';
  if (code > 0)
    strcat(destination, source);
  else {
    int source_length = strlen(source);
    s21_strncpy(destination, source, source_length);
  }
}