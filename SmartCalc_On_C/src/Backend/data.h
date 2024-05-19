#ifndef DATA_H
#define DATA_H

/** @file */

#include <stdbool.h>

/**
 * @brief Struct for data item
 * @param type Type of data
 * @param priority Priority of data
 * @param right_assoc Right assoc
 * @param sym Symbol
 * @param value Value of number
 * @param op op
 * @param func Pointer of function
 */
typedef struct Data {
  int type;
  int priority;
  bool right_assoc;
  char sym;
  double value;
  double (*op)(double a1, double a2);
  double (*func)(double a1);
} Data;

/**
 * @brief Priorities
 * @param PROIRITY_ZERO x, number
 * @param PROIRITY_FIRST sum, sub
 * @param PROIRITY_SECOND div, mult, mode
 * @param PROIRITY_THIRD hooks, pow, unary plus, unary minus
 * @param PROIRITY_FOURTH sin, cos, tan, acos, asin, atan, sqrt, ln, log
 */
typedef enum Priority {
  PROIRITY_ZERO,
  PROIRITY_FIRST,
  PROIRITY_SECOND,
  PROIRITY_THIRD,
  PROIRITY_FOURTH
} Priority;

/**
 * @brief Types of data
 * @param 0 NONE
 * @param 1 NUMBER
 * @param 2 OPERATOR
 * @param 3 BRACKET
 * @param 4 FUNCTION
 * @param 5 VARIABLE
 */
enum Type {
  NONE = 0,
  NUMBER = 1,
  OPERATOR = 2,
  BRACKET = 3,
  FUNCTION = 4,
  VARIABLE = 5
};

#endif
