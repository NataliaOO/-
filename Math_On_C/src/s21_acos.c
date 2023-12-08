#include "s21_math.h"

long double s21_acos(double x) {
  long double result = 0.0;
  if (x < -1.0 || x > 1.0)
    result = S21_NAN;
  else {
    if (x >= -1 && x < 0) result += s21_PI;
    result += s21_atan(s21_sqrt(1 - x * x) / x);
  }

  return result;
}
