#ifndef PARSER_H
#define PARSER_H

/** @file */

#include "stack.h"

/**
 * @param OK Ok
 * @param EXPR_ERROR Expression error
 * @param DATA_ERROR Data error
 */
typedef enum Error { OK, EXPR_ERROR, DATA_ERROR } Error;

/**
 * @brief Numbers characterst
 */
#define NUMBERS "1234567890"

/**
 * @brief Convert string to RPN and push to stack
 * @param str Input string
 * @param out_stack Top of the stack
 * @return int Error code
 */
int to_rpn(char *str, Data **array);

/**
 * @brief Calculate expression
 * @param rpn Stack top
 * @param x x value
 * @return double Result of the expression
 */
double evaluate(Data *rpn, double x);

#endif
