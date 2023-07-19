#include "s21_math.h"

long double s21_pow(double base, double exp) {
  long double result = 0.0;

  if (S21_IS_NAN(base) || S21_IS_NAN(exp))
    result = S21_NAN;  // NaN^x or x^NaN = NaN
  else if (s21_fabs(base) == 1.0L && S21_IS_INF(exp))
    result = 1.0L;
  else if (base == 1.0)
    result = 1.0;  // 1 raised to any power is 1
  else if (exp == 0.0)
    result = 1.0;  // Any number raised to power 0 is 1
  else if (exp == 1.0)
    result = base;  // Any number raised to power 1 is itself
  else if (base == S21_INF) {
    result = (exp > 0.0)
                 ? S21_INF
                 : 0.0;  // infinity^positive = infinity, infinity^negative = 0
  } else if (base == -S21_INF) {
    if (exp > 0.0) {
      result = (s21_floor(exp) == exp && (long long)exp % 2 == 1)
                   ? -S21_INF
                   : S21_INF;  // (-infinity)^odd = -infinity, (-infinity)^even
                               // = infinity
    } else {
      result = (s21_floor(exp) == exp && (long long)exp % 2 == -1)
                   ? -0.0
                   : 0.0;  // (-infinity)^odd = -0, (-infinity)^even = 0
    }
  } else if (base < 0.0 && s21_fmod(exp, 1.0) != 0.0) {
    result = S21_NAN;  // Negative base and non-integer exponent
  } else {
    result = s21_exp(exp * s21_log(s21_fabs(base)));
    if ((base < 0.0 && s21_fmod(exp, 2) == 1)) result *= -1;
  }

  return result;
}