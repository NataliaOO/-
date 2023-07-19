#include "s21_math.h"

long double s21_asin(double x) {
  long double result = 0.0;
  if (x < -1.0 || x > 1.0)
    result = S21_NAN;
  else
    result = s21_atan(x / s21_sqrt(1 - x * x));

  return result;
}
