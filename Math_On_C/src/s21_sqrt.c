#include "s21_math.h"

long double s21_sqrt(double x) {
  long double result = 0.0;
  if (__builtin_signbit(x))
    result = S21_NAN;
  else if (S21_IS_INF(x))
    result = S21_INF;
  else
    result = s21_pow(x, 0.5);

  return result;
}
