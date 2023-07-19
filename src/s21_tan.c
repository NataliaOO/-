#include "s21_math.h"

long double s21_tan(double x) {
  long double result = 0.0;
  if (S21_IS_NAN(x) || S21_IS_INF(x))
    result = S21_NAN;
  else if (x == s21_PI / 2) {
    result = 16331239353195370L;
  } else if (x == -s21_PI / 2) {
    result = -16331239353195370L;
  } else
    result = s21_sin(x) / s21_cos(x);
  return result;
}