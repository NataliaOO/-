#include "s21_math.h"

long double s21_cos(double x) {
  long double result = 0.0;
  if (S21_IS_NAN(x) || S21_IS_INF(x) || S21_IS_INF(x) == -1) {
    result = S21_NAN;
  } else if (s21_fabs(x) < s21_EPS)
    result = 1.0L;
  else {
    for (; x < -2 * s21_PI || x > 2 * s21_PI;) {
      if (x > 2 * s21_PI) {
        x -= 2 * s21_PI;
      } else {
        x += 2 * s21_PI;
      }
    }
    // cos(x) = sin(x + π/2)
    // sin(x) = x - x^3/3! + x^5/5! - x^7/7! + ...
    result = s21_sin(x + s21_PI / 2.);
  }
  return result;
}
