#ifndef S21_MATH_H_
#define S21_MATH_H_

#include <float.h>
#include <limits.h>
#include <stdlib.h>

#define s21_EPS 1E-6
#define s21_EXP 2.718281828459045
#define s21_PI 3.141592653589793
// Returns float infinite value
#define S21_INF (__builtin_inff())
// Returns float NaN value
#define S21_NAN (__builtin_nanf(""))
// Check for infinity: returns 1 if infinite, -1 if -infinite and 0 if finite
#define S21_IS_INF(x) __builtin_isinf_sign(x)
// Check for nan value: returns 1 if NaN and 0 if not
#define S21_IS_NAN(x) __builtin_isnan(x)

int s21_abs(int x);
long double s21_fabs(double x);
long double s21_fmod(double x, double y);
long double s21_floor(double x);
long double s21_ceil(double x);
long double s21_log(double x);
long double s21_exp(double x);
long double s21_pow(double base, double exp);
long double s21_sqrt(double x);
long double s21_sin(double x);
long double s21_cos(double x);
long double s21_tan(double x);
long double s21_atan(double x);
long double s21_asin(double x);
long double s21_acos(double x);

#endif  // S21_MATH_H_