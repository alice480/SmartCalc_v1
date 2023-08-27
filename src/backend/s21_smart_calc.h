#ifndef SRC_BACKEND_S21_SMART_CALC_H_
#define SRC_BACKEND_S21_SMART_CALC_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --------------------------------------------------------------------------
//                            ERROR CODES
#define TOKEN_DOESNT_EXIST 0
#define STACK_IS_EMPTY 0
#define STACK_IS_FULL 0
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
//                      LEXICAL VALUES OF TOKENS
#define BINARY_OPERATOR 1
#define UNARY_OPERATOR 2
#define OPERAND 3
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
//            STRUCTURE AND FUNCTIONS FOR THE "S21_STACK.C"
struct node {
  char *operation;
  double number;
  struct node *next;
};

double pop(struct node **head);
int push(char *operation, double number, struct node **head);
char *peek_operation(struct node **head);
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
//                     FUNCTIONS FOR THE "S21_SMART_CALC.C"
int s21_calculation(char *expression, double *result);

char *string_overwriting(char *expression);

int s21_token_splitting(char *rpn_expression, double *result);
int s21_postfix_calculation(char *token, struct node **stack);

double s21_convert_str_to_double(char *token);
double s21_performing_operations(double number1, double number2, char *operand);
double s21_performing_function(double number, char *function);
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
//                     FUNCTIONS FOR THE "S21_RPN_CONVERSION.C"
int S21_rpn_conversion(char *expression, char *rpn_expression);

// implementation of Dijkstra 's algorithm
int s21_dijkstra_alg(struct node **stack, char *output_line, char *token,
                     int token_length, int definition);
int s21_priority_determining(char *current_operator);
int s21_dijkstra_completion(struct node **stack, char *output_line);
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
//                    FUNCTIONS FOR THE "S21_COMMON_FUNC.C"

int s21_token_definition(char *token);
void s21_strncpy(char *destination, char *source, int length);
void s21_strcat(char *destination, char *source);

// --------------------------------------------------------------------------

#endif // SRC_BACKEND_S21_SMART_CALC_H_
