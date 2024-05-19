#include "rpn.h"
#include "stack.h"

double evaluate(Data *rpn, double x) {
  Node *stack = NULL;
  int i = 0;

  while (rpn[i].type) {
    if (rpn[i].type == NUMBER)
      stack = stack_push(stack, rpn[i]);
    else if (rpn[i].type == VARIABLE) {
      stack = stack_push(stack, (Data){.type = NUMBER, .value = x});
    } else if (rpn[i].type == OPERATOR) {
      double v1 = stack->data.value;
      stack = stack_pop(stack);

      if (stack) {
        double v2 = stack->data.value;
        stack = stack_pop(stack);
        stack = stack_push(stack,
                           (Data){.type = NUMBER, .value = rpn[i].op(v2, v1)});
      }
    } else if (rpn[i].type == FUNCTION) {
      double v1 = stack->data.value;
      stack = stack_pop(stack);
      stack =
          stack_push(stack, (Data){.type = NUMBER, .value = rpn[i].func(v1)});
    }

    i++;
  }

  return stack->data.value;
}
