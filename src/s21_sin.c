#include "s21_math.h"

long double s21_sin(double x) {
  long double result = 0.0;
  if (S21_IS_NAN(x) || S21_IS_INF(x)) {
    result = S21_NAN;
  } else {
    while (x > s21_PI) {
      x -= 2 * s21_PI;
    }
    while (x < -s21_PI) {
      x += 2 * s21_PI;
    }
    double term = x, numerator = x, denominator = 1.0;
    int sign = 1;
    for (int i = 1; i <= 10; ++i) {
      result += sign * numerator / denominator;
      numerator *= term * term;
      denominator *= (2 * i) * (2 * i + 1);
      sign *= -1;
    }
  }
  return result;
}
