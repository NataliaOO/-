#include "s21_math.h"

#define S21_LN2 0.693147180559945309417232121458176568

long double s21_log(double x) {
  long double result = 0.0;
  if (!x || s21_fabs(x) < s21_EPS)
    result = -S21_INF;
  else if (S21_IS_INF(x) == 1)
    result = S21_INF;
  else if (x == 2)
    result = S21_LN2;
  else if (s21_fabs(x - 1.0) < s21_EPS / 10)
    result = 0.0L;
  else if (s21_fabs(x - s21_EXP) <= 1e-15)
    result = 1.0L;
  else if (__builtin_signbit(x) || S21_IS_NAN(x))
    result = S21_NAN;
  else {
    if (x > 0 && x <= 2) {
      long double num = (long double)x - 1.0L;
      long double sign = 1.0L;
      long double delim = 1.0L;
      long double temp = num;
      while (s21_fabs(temp) > 1E-50) {  // 0 < x < 2
        result += temp / delim * sign;
        temp *= num;
        sign *= -1.0L;
        delim += 1.0L;
      }
    } else {
      double how_much = 0;
      while (x >= 2.0) {
        x /= 2.0L;
        how_much++;
      }
      result = how_much * S21_LN2 + s21_log(x);
    }
  }
  return result;
}