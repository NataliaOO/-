#include "s21_math.h"

long double s21_atan(double x) {
  long double result = 0.0;
  if (S21_IS_NAN(x))
    result = S21_NAN;
  else if (S21_IS_INF(x) == 1)
    result = s21_PI / 2;
  else if (S21_IS_INF(x) == -1)
    result = -s21_PI / 2;
  else {
    long double abs_x = s21_fabs(x);
    long double x_squared = abs_x * abs_x;
    long double term = abs_x;
    long double denominator = 1.0L;
    if (abs_x > 1.0) {
      abs_x = s21_PI / 2 - s21_atan(1.0 / abs_x);
    } else {
      while (s21_fabs(term / denominator) > 1e-8) {
        denominator += 2;
        term *= -x_squared;
        abs_x += term / denominator;
      }
    }
    result = __builtin_signbit(x) ? -abs_x : abs_x;
  }
  return result;
}
