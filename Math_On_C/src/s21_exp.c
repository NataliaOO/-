#include "s21_math.h"

long double s21_exp(double x) {
  double result = 1.0;
  if (S21_IS_NAN(x) || x == S21_INF) {
    result = x;
  } else if (x == -S21_INF || (__builtin_signbit(x) && s21_fabs(x) > 20.0)) {
    result = 0.0;
  } else {
    double term = 1.0;
    int i = 1;
    while (s21_fabs(term / result) > 1e-100) {
      term *= (long double)x / i++;
      result += term;
    }
  }
  return result;
}