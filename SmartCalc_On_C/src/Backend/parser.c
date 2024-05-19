#include <math.h>
#include <stdint.h>

#include "rpn.h"
#include "stack.h"

#define TABLE_SIZE 256

uint8_t rotl(uint8_t x, uint8_t n) { return (x << n) | (x >> (8 - n)); }

uint8_t hash(char const *input) {
  uint8_t result = 0xAA;

  while (*input) {
    result ^= *input++;
    result = rotl(result, 3);
  }

  return result;
}

double do_mul(double a1, double a2) { return a1 * a2; }
double do_div(double a1, double a2) { return a1 / a2; }
double do_add(double a1, double a2) { return a1 + a2; }
double do_sub(double a1, double a2) { return a1 - a2; }
double acot(double a1) { return atan(1.0 / a1); }
double cot(double a1) { return 1.0f / tan(a1); }

int to_rpn(char *str, Data **array) {
  Data ops[256] = {{0}};

  ops['+'] = (Data){.type = OPERATOR, .priority = PROIRITY_FIRST, .op = do_add};
  ops['-'] = (Data){.type = OPERATOR, .priority = PROIRITY_FIRST, .op = do_sub};
  ops['*'] =
      (Data){.type = OPERATOR, .priority = PROIRITY_SECOND, .op = do_mul};
  ops['/'] =
      (Data){.type = OPERATOR, .priority = PROIRITY_SECOND, .op = do_div};
  ops['%'] = (Data){.type = OPERATOR, .priority = PROIRITY_SECOND, .op = fmod};
  ops['^'] = (Data){.type = OPERATOR,
                    .priority = PROIRITY_THIRD,
                    .op = pow,
                    .right_assoc = true};

  Data funcs[TABLE_SIZE] = {{0}};
  funcs[hash("Sin")] = (Data){.type = FUNCTION, .func = sin};
  funcs[hash("Asin")] = (Data){.type = FUNCTION, .func = asin};
  funcs[hash("Cos")] = (Data){.type = FUNCTION, .func = cos};
  funcs[hash("Acos")] = (Data){.type = FUNCTION, .func = acos};
  funcs[hash("Tan")] = (Data){.type = FUNCTION, .func = tan};
  funcs[hash("Ctan")] = (Data){.type = FUNCTION, .func = cot};
  funcs[hash("Actan")] = (Data){.type = FUNCTION, .func = acot};
  funcs[hash("Atan")] = (Data){.type = FUNCTION, .func = atan};
  funcs[hash("Sqrt")] = (Data){.type = FUNCTION, .func = sqrt};
  funcs[hash("Ln")] = (Data){.type = FUNCTION, .func = log};
  funcs[hash("Log")] = (Data){.type = FUNCTION, .func = log10};

  if (!str) return DATA_ERROR;

  Node *out = NULL;

  int status = OK;

  char *token = str;

  Node *stack = NULL;

  while (*token) {
    if (strchr(NUMBERS, *token)) {
      double number = 0.0;
      int l = strlen(token);
      char *str = malloc(l * sizeof(char));
      int res = sscanf(token, "%lf%s", &number, str);
      token = token + (l - strlen(str));
      free(str);
      out = stack_push(out, (Data){.type = NUMBER, .value = number});

      if (res != 2) *token = '\0';

    } else if (ops[(uint8_t)(*token)].type || !strncmp(token, "Mod", 3)) {
      if (ops[(uint8_t)(*(token + 1))].type) {
        status = DATA_ERROR;
        break;
      }

      if (!strncmp(token, "Mod", 3)) {
        token += 2;
        *token = '%';
      }

      while (stack && stack->data.type == OPERATOR &&
             (stack->data.priority > ops[(uint8_t)(*token)].priority ||
              (stack->data.priority == ops[(uint8_t)(*token)].priority &&
               !ops[(uint8_t)(*token)].right_assoc))) {
        out = stack_push(out, stack->data);
        stack = stack_pop(stack);
      }

      if ((*token == '-' || *token == '+') && (!out || (*(token - 1) == '(')))
        out = stack_push(out, (Data){.type = NUMBER, .value = 0.});

      stack = stack_push(stack, ops[(uint8_t)(*token++)]);
    } else if (*token == 'x')
      out = stack_push(out, (Data){.type = VARIABLE, .sym = *token++});
    else if (*token == '(')
      stack = stack_push(stack, (Data){.type = BRACKET, .sym = *token++});
    else if (*token == ')') {
      if (!stack) {
        status = EXPR_ERROR;
        break;
      }

      while (stack && stack->data.sym != '(') {
        out = stack_push(out, stack->data);
        stack = stack_pop(stack);
      }

      if (stack && stack->data.sym != '(') {
        status = EXPR_ERROR;
        break;
      } else {
        stack = stack_pop(stack);
        if (stack && stack->data.type == FUNCTION) {
          out = stack_push(out, stack->data);
          stack = stack_pop(stack);
        }
      }

      token++;
    } else {
      char *func = malloc(strlen(token) * sizeof(char *) + 1);

      if (sscanf(token, "%[^(]", func)) {
        if (funcs[hash(func)].type != NONE) {
          stack = stack_push(stack, funcs[hash(func)]);
          token += strlen(func);

          if (*token != '(') status = EXPR_ERROR;
        } else
          status = EXPR_ERROR;
      } else
        status = EXPR_ERROR;

      free(func);
    }
    if (status) break;
  }
  while (stack && stack->data.type != NONE) {
    if (stack->data.sym == '(') {
      status = EXPR_ERROR;
      break;
    }

    out = stack_push(out, stack->data);
    stack = stack_pop(stack);
  }

  *array = stack_to_array(out, *array);

  return status;
}
