#include "stack.h"

#include "data.h"

Node *stack_push(Node *top, Data data) {
  Node *node = (Node *)malloc(sizeof(Node));
  node->data = data;
  node->next = top;

  return node;
}

Node *stack_pop(Node *top) {
  if (!top) return NULL;

  Node *next = top->next;
  free(top);

  return next;
}

Node *stack_reverse(Node *top) {
  Node *node = NULL;
  while (top) {
    node = stack_push(node, top->data);
    top = stack_pop(top);
  }
  return node;
}

Data *stack_to_array(Node *top, Data *array) {
  Node *rev = stack_reverse(top);
  int i = 0;
  while (rev) {
    array[i] = rev->data;
    rev = stack_pop(rev);
    i++;
  }
  array[i] = (Data){0};
  return array;
}

/*
void stack_free(Node *top) {
  while (top) top = stack_pop(top);
}

Data stack_peek(Node *top) {
  Data data = {0};

  if (!top) return data;

  return top->data;
}
*/