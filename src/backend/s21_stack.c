#include "s21_smart_calc.h"

char *peek_operation(struct node **head) {
  char *result = NULL;
  if (*head != NULL)
    result = (*head)->operation;
  return result;
}

double pop(struct node **head) {
  double number = STACK_IS_EMPTY;
  struct node *node;
  if (*head != NULL) {
    node = *head;
    number = (*head)->number;
    *head = (*head)->next;
    if (node->operation)
      free(node->operation);
    free(node);
  }
  return number;
}

int push(char *operation, double number, struct node **head) {
  int status = 1;
  struct node *new_node = NULL;
  new_node = (struct node *)malloc(sizeof(struct node));
  if (!new_node) {
    status = STACK_IS_FULL;
  } else {
    new_node->operation = operation;
    new_node->number = number;
    new_node->next = *head;
    *head = new_node;
  }
  return status;
}
