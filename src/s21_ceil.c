#include "s21_math.h"

long double s21_ceil(double x) {
  long double result = x;
  if (x == FLT_MAX)
    result = FLT_MAX;
  else if (!S21_IS_NAN(x) && !S21_IS_INF(x)) {
    result = (long int)result + (result > (long int)result);
  }
  return result;
}