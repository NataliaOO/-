#include "s21_math.h"

long double s21_fmod(double x, double y) {
  long double result = 0.0;
  if (!y || S21_IS_INF(x) || S21_IS_NAN(x) || S21_IS_NAN(y)) {
    result = S21_NAN;
  } else if (s21_fabs(x) == 1.0 && S21_IS_INF(y)) {
    result = x;
  } else if (x == 0.0L) {
    result = -0.0L;
  } else {
    double quotient = x / y;
    double int_part = (long long)quotient;
    result = x - (int_part * y);
  }
  return result;
}