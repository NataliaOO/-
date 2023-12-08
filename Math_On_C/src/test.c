#include <check.h>
#include <math.h>
#include <stdio.h>

#include "s21_math.h"

START_TEST(test_abs) {
  ck_assert_int_eq(s21_abs(0), abs(0));
  ck_assert_int_eq(s21_abs(-1), abs(-1));
  ck_assert_int_eq(s21_abs(1), abs(1));
  ck_assert_int_eq(s21_abs(33), abs(33));
  ck_assert_int_eq(s21_abs(-33), abs(-33));
  ck_assert_int_eq(s21_abs(INT_MAX), abs(INT_MAX));
  ck_assert_int_eq(s21_abs(INT_MIN), abs(INT_MIN));
  ck_assert_int_eq(s21_abs(-5555), abs(-5555));
  ck_assert_int_eq(s21_abs(-0), abs(-0));
  ck_assert_int_eq(s21_abs(1234567), abs(1234567));
  ck_assert_int_eq(s21_abs(-1234567), abs(-1234567));
  ck_assert_int_eq(abs(-10), s21_abs(-10));
  ck_assert_int_eq(abs(7895), s21_abs(7895));
  ck_assert_int_eq(abs(-10101), s21_abs(-10101));
  ck_assert_int_eq(abs(10101), s21_abs(10101));
  for (int i = -128; i <= 127; i++) ck_assert_int_eq(abs(i), s21_abs(i));
}
END_TEST

START_TEST(test_fabs) {
  ck_assert_ldouble_eq(s21_fabs(0.0), (long double)fabs(0.0));
  ck_assert_ldouble_eq(s21_fabs(-1.0), (long double)fabs(-1.0));
  ck_assert_ldouble_eq(s21_fabs(1.0), (long double)fabs(1.0));
  ck_assert_ldouble_eq(s21_fabs(33.43543), (long double)fabs(33.43543));
  ck_assert_ldouble_eq(s21_fabs(-33.345345), (long double)fabs(-33.345345));
  ck_assert_ldouble_eq(s21_fabs(FLT_MAX), (long double)fabs(FLT_MAX));
  ck_assert_ldouble_eq(s21_fabs(-FLT_MAX), (long double)fabs(-FLT_MAX));
  ck_assert_ldouble_eq(s21_fabs(-55.55), (long double)fabs(-55.55));
  ck_assert_ldouble_eq(s21_fabs(-0.0), (long double)fabs(-0.0));
  ck_assert_ldouble_eq(s21_fabs(0.0000000000001),
                       (long double)fabs(0.0000000000001));
  ck_assert_ldouble_eq(s21_fabs(-0.0000000000001),
                       (long double)fabs(-0.0000000000001));
  ck_assert_ldouble_nan(s21_fabs(s21_sqrt(-1.0)));
  ck_assert_ldouble_infinite(s21_fabs(S21_INF));
  ck_assert_double_eq(fabs(-INFINITY), s21_fabs(-S21_INF));
  ck_assert_double_nan(fabs(NAN));
  ck_assert_double_nan(s21_fabs(S21_NAN));
  ck_assert_double_eq(fabs(-7.0), s21_fabs(-7.0));
  ck_assert_double_eq(fabs(-98.1), s21_fabs(-98.1));
  ck_assert_double_eq(fabs(123.02), s21_fabs(123.02));
  ck_assert_double_eq(fabs(10009.0), s21_fabs(10009.0));
  ck_assert_double_eq(fabs(-10009.555), s21_fabs(-10009.555));
  ck_assert_double_eq(fabs(-0.10009), s21_fabs(-0.10009));
  ck_assert_double_eq(fabs(-1e23), s21_fabs(-1e23));
  ck_assert_double_eq(fabs(INFINITY), s21_fabs(S21_INF));
  ck_assert_double_eq(fabs(0.000213), s21_fabs(0.000213));
}
END_TEST

START_TEST(test_fmod) {
  ck_assert_ldouble_eq_tol(fmod(12345, 12.234), s21_fmod(12345, 12.234),
                           s21_EPS);
  ck_assert_ldouble_eq_tol(fmod(0.0, 0.0001), s21_fmod(0.0, 0.0001), s21_EPS);
  ck_assert_ldouble_nan(s21_fmod(0.0, 0.0));
  ck_assert_ldouble_eq_tol(fmod(-2834.242, 11.2), s21_fmod(-2834.242, 11.2),
                           s21_EPS);
  ck_assert_ldouble_eq_tol(fmod(4, 2), s21_fmod(4, 2), s21_EPS);
  ck_assert_ldouble_nan(s21_fmod(-10, 0));
  ck_assert_ldouble_eq_tol(fmod(-1, S21_INF), s21_fmod(-1, S21_INF), s21_EPS);
  ck_assert_ldouble_eq_tol(fmod(121, 11.0001), s21_fmod(121, 11.0001), s21_EPS);
  ck_assert_ldouble_eq_tol(fmod(1244.12414, 1244), s21_fmod(1244.12414, 1244),
                           s21_EPS);
  ck_assert_ldouble_eq_tol(fmod(1.21, -0.99999), s21_fmod(1.21, -0.99999),
                           s21_EPS);
  ck_assert_ldouble_eq_tol(fmod(1.21, 124214141), s21_fmod(1.21, 124214141),
                           s21_EPS);
  ck_assert_double_nan(s21_fmod(1, 0));
  ck_assert_double_eq(fmod(0, -1), s21_fmod(0, -1));
  ck_assert_double_eq(fmod(0, 1), s21_fmod(0, 1));
  ck_assert_double_nan(fmod(S21_INF, -1));
  ck_assert_double_nan(s21_fmod(S21_INF, -1));
  ck_assert_double_eq(fmod(-1, -S21_INF), s21_fmod(-1, -S21_INF));
  ck_assert_double_eq(fmod(0, S21_INF), s21_fmod(0, S21_INF));
  ck_assert_double_nan(s21_fmod(0, S21_NAN));
  ck_assert_double_nan(fmod(0, S21_NAN));
  ck_assert_double_nan(s21_fmod(S21_NAN, S21_NAN));
  ck_assert_double_nan(fmod(S21_NAN, S21_NAN));
  ck_assert_double_nan(s21_fmod(S21_NAN, S21_INF));
  ck_assert_double_nan(s21_fmod(S21_INF, S21_NAN));
  ck_assert_double_nan(s21_fmod(S21_NAN, -S21_INF));
  ck_assert_double_nan(s21_fmod(-S21_INF, S21_NAN));
  ck_assert_double_nan(fmod(S21_NAN, S21_INF));
  ck_assert_double_nan(fmod(S21_INF, S21_NAN));
  ck_assert_double_nan(fmod(S21_NAN, -S21_INF));
  ck_assert_double_nan(fmod(-S21_INF, S21_NAN));
}
END_TEST

START_TEST(test_floor) {
  ck_assert_double_eq(floor(INFINITY), s21_floor(S21_INF));
  ck_assert_double_eq(floor(-INFINITY), s21_floor(-S21_INF));
  ck_assert_double_nan(s21_floor(NAN));
  ck_assert_int_eq(floor(-7.0), s21_floor(-7.0));
  ck_assert_double_eq(floor(-98.1), s21_floor(-98.1));
  ck_assert_double_eq(floor(123.02), s21_floor(123.02));
  ck_assert_double_eq(floor(FLT_MAX), s21_floor(FLT_MAX));
  ck_assert_double_eq(floor(-10009.555), s21_floor(-10009.555));
  ck_assert_double_eq(floor(-0.10009), s21_floor(-0.10009));
  ck_assert_double_eq(floor(-1e-23), s21_floor(-1e-23));
  ck_assert_double_eq(floor(100091234.5), s21_floor(100091234.5));
  ck_assert_double_eq(floor(7), s21_floor(7));
  ck_assert_double_eq(floor(0), s21_floor(0));
  ck_assert_double_eq(floor(0.0), s21_floor(0.0));
}
END_TEST

START_TEST(test_ceil) {
  for (double i = -s21_PI / 2; i <= s21_PI / 2; i += 0.25)
    ck_assert_double_eq(ceil(i), s21_ceil(i));
  ck_assert_double_eq(ceil(INFINITY), s21_ceil(S21_INF));
  ck_assert_double_eq(ceil(-INFINITY), s21_ceil(-S21_INF));
  ck_assert_double_nan(s21_ceil(S21_NAN));
  ck_assert_double_eq(ceil(-7.0), s21_ceil(-7.0));
  ck_assert_double_eq(ceil(-98.1), s21_ceil(-98.1));
  ck_assert_double_eq(ceil(123.02), s21_ceil(123.02));
  ck_assert_double_eq(ceil(FLT_MAX), s21_ceil(FLT_MAX));
  ck_assert_double_eq(ceil(-10009.555), s21_ceil(-10009.555));
  ck_assert_double_eq(ceil(-0.10009), s21_ceil(-0.10009));
  ck_assert_double_eq(ceil(-1e-23), s21_ceil(-1e-23));
  ck_assert_double_eq(ceil(7), s21_ceil(7));
  ck_assert_double_eq(ceil(0), s21_ceil(0));
  ck_assert_double_eq(ceil(-0.0), s21_ceil(-0.0));
}
END_TEST

START_TEST(test_exp) {
  ck_assert_ldouble_eq_tol(s21_exp(0.0), expl(0.0), s21_EPS);
  ck_assert_ldouble_eq_tol(s21_exp(-0.0), expl(-0.0), s21_EPS);
  ck_assert_ldouble_eq_tol(s21_exp(1.0), expl(1.0), s21_EPS);
  ck_assert_ldouble_eq_tol(s21_exp(1.1111), expl(1.1111), s21_EPS);
  ck_assert_ldouble_eq_tol(s21_exp(-1.1111), expl(-1.1111), s21_EPS);
  ck_assert_ldouble_eq_tol(s21_exp(10), expl(10), s21_EPS);
  ck_assert_ldouble_eq_tol(s21_exp(-10), expl(-10), s21_EPS);
  ck_assert_ldouble_eq_tol(s21_exp(-1.9999999), expl(-1.9999999), s21_EPS);
  ck_assert_ldouble_eq_tol(s21_exp(1.9999999), expl(1.9999999), s21_EPS);
  ck_assert_ldouble_eq_tol(s21_exp(-0.9999999), expl(-0.9999999), s21_EPS);
  ck_assert_ldouble_eq_tol(s21_exp(0.9999999), expl(0.9999999), s21_EPS);
  ck_assert_ldouble_nan(s21_exp(S21_NAN));
  ck_assert_ldouble_infinite(s21_exp(S21_INF));
  ck_assert_ldouble_eq(s21_exp(-S21_INF), 0.0);
  ck_assert_ldouble_eq_tol(s21_exp(5.5), expl(5.5), s21_EPS);
  ck_assert_double_eq_tol(s21_exp(3.3333), expl(3.3333), s21_EPS);
  ck_assert_double_eq_tol(s21_exp(-5.5), expl(-5.5), s21_EPS);
  ck_assert_double_eq(s21_exp(4566.7899), expl(4566.7899));
  ck_assert_double_nan(s21_exp(NAN));
  ck_assert_double_eq(s21_exp(INFINITY), expl(INFINITY));
  ck_assert_double_eq_tol(s21_exp(0.4564), expl(0.4564), s21_EPS);
  ck_assert_double_eq(expl(0), s21_exp(0));
  ck_assert_double_eq_tol(expl(-45.11), s21_exp(-45.11), s21_EPS);
  ck_assert_double_eq_tol(expl(-1), s21_exp(-1), s21_EPS);
  ck_assert_double_eq_tol(expl(-0.000001), s21_exp(-0.000001), s21_EPS);
  for (double i = -2.7863; i <= 2.6831; i += 0.001)
    ck_assert_double_eq_tol(expl(i), s21_exp(i), s21_EPS);
}
END_TEST

START_TEST(test1_pow) {
  ck_assert_ldouble_eq_tol(powl(2, 3), s21_pow(2, 3), s21_EPS);
  ck_assert_ldouble_eq_tol(powl(0, 0), s21_pow(0, 0), s21_EPS);
  ck_assert_ldouble_eq_tol(powl(3, -1), s21_pow(3, -1), s21_EPS);
  ck_assert_ldouble_eq_tol(powl(-5, 5), s21_pow(-5, 5), s21_EPS);
  ck_assert_ldouble_eq_tol(powl(0.352342, 7), s21_pow(0.352342, 7), s21_EPS);
  ck_assert_ldouble_eq_tol(powl(0.5, 1.245), s21_pow(0.5, 1.245), s21_EPS);
  ck_assert_ldouble_eq_tol(powl(99, -0.99999), s21_pow(99, -0.99999), s21_EPS);
  ck_assert_ldouble_eq_tol(powl(99, -0.0001), s21_pow(99, -0.0001), s21_EPS);
  ck_assert_ldouble_eq_tol(powl(-12.5, 5), s21_pow(-12.5, 5), s21_EPS);
  ck_assert_ldouble_eq_tol(powl(-12.5, 6), s21_pow(-12.5, 6), s21_EPS);
  ck_assert_ldouble_eq_tol(powl(0.0, 6), s21_pow(0.0, 6), s21_EPS);
  ck_assert_double_eq_tol(powl(56.3, 0.3), s21_pow(56.3, 0.3), s21_EPS);
  ck_assert_double_eq(powl(1, 0), s21_pow(1, 0));
  ck_assert_double_eq(powl(-1, 3), s21_pow(-1, 3));
  ck_assert_double_eq(powl(-INFINITY, 3), s21_pow(-S21_INF, 3));
  ck_assert_double_eq(powl(0, 0), s21_pow(0, 0));
  ck_assert_double_eq(powl(0, -1), s21_pow(0, -1));
  ck_assert_double_eq(powl(0, 1), s21_pow(0, 1));
  ck_assert_double_eq(powl(INFINITY, 0), s21_pow(S21_INF, 0));
  ck_assert_double_eq(powl(INFINITY, -1), s21_pow(S21_INF, -1));
}
END_TEST

START_TEST(test2_pow) {
  ck_assert_ldouble_eq_tol(powl(S21_INF, -2), s21_pow(S21_INF, -2), s21_EPS);
  ck_assert_double_eq_tol(powl(0.3123, 0.789456), s21_pow(0.3123, 0.789456),
                          s21_EPS);
  ck_assert_ldouble_eq_tol(powl(S21_INF, -S21_INF), s21_pow(S21_INF, -S21_INF),
                           s21_EPS);
  ck_assert_double_eq(pow(-S21_INF, 2), s21_pow(-S21_INF, 2));
  ck_assert_double_eq(pow(-S21_INF, -3), s21_pow(-S21_INF, -3));
  ck_assert_ldouble_eq_tol(powl(1, 10.000199999), s21_pow(1, 10.000199999),
                           s21_EPS);
  ck_assert_ldouble_eq_tol(powl(1.0001, 10.000199999),
                           s21_pow(1.0001, 10.000199999), s21_EPS);
  ck_assert_ldouble_eq_tol(powl(1.0001, -10.000199999),
                           s21_pow(1.0001, -10.000199999), s21_EPS);
  ck_assert_ldouble_nan(s21_pow(-1.0001, -10.100199999));
  ck_assert_ldouble_eq_tol(powl(0.99999, 0.99999), s21_pow(0.99999, 0.99999),
                           s21_EPS);
  ck_assert_double_nan(s21_pow(-S21_INF, S21_NAN));
  ck_assert_double_eq(powl(2, S21_INF), s21_pow(2, S21_INF));
  ck_assert_double_nan(s21_pow(-0.789456, -0.789456));
  ck_assert_double_nan(s21_pow(-500.789456, -10.1354323));
  ck_assert_double_nan(s21_pow(-500.789456, 34.13));
  ck_assert_double_eq_tol(powl(10.789456, 3.13), s21_pow(10.789456, 3.13),
                          1e-2);
  ck_assert_double_eq_tol(powl(-1, -S21_INF), s21_pow(-1, -S21_INF), s21_EPS);
  ck_assert_double_eq_tol(powl(0, S21_INF), s21_pow(0, S21_INF), s21_EPS);
  ck_assert_double_eq_tol(powl(-S21_INF, -2), s21_pow(-S21_INF, -2), s21_EPS);
  ck_assert_double_nan(s21_pow(0, S21_NAN));
  ck_assert_double_nan(s21_pow(S21_NAN, S21_NAN));
  ck_assert_double_eq(powl(INFINITY, INFINITY), s21_pow(S21_INF, S21_INF));
  ck_assert_double_nan(s21_pow(S21_NAN, S21_INF));
  ck_assert_double_nan(s21_pow(S21_INF, S21_NAN));
  ck_assert_double_nan(s21_pow(S21_NAN, -S21_INF));
}
END_TEST

START_TEST(test_sqrt) {
  ck_assert_ldouble_eq_tol(sqrt(1234567890123456), s21_sqrt(1234567890123456),
                           s21_EPS);
  ck_assert_ldouble_eq_tol(sqrt(0.0), s21_sqrt(0.0), s21_EPS);
  ck_assert_ldouble_eq_tol(sqrt(0.01), s21_sqrt(0.01), s21_EPS);
  ck_assert_ldouble_eq_tol(sqrt(0.00001), s21_sqrt(0.00001), s21_EPS);
  ck_assert_ldouble_nan(s21_sqrt(-0.00001));
  ck_assert_ldouble_nan(s21_sqrt(-1));
  ck_assert_ldouble_eq_tol(sqrt(2), s21_sqrt(2), s21_EPS);
  ck_assert_ldouble_eq_tol(sqrt(121), s21_sqrt(121), s21_EPS);
  ck_assert_ldouble_eq_tol(sqrt(1244.12414), s21_sqrt(1244.12414), s21_EPS);
  ck_assert_ldouble_eq_tol(sqrt(1.21), s21_sqrt(1.21), s21_EPS);
  ck_assert_ldouble_eq_tol(sqrt(0.999998), s21_sqrt(0.999998), s21_EPS);
  ck_assert_double_eq_tol(s21_sqrt(233), sqrt(233), s21_EPS);
  ck_assert_double_nan(s21_sqrt(S21_NAN));
  ck_assert_double_nan(sqrt(NAN));
  ck_assert_double_eq(s21_sqrt(S21_INF), sqrt(INFINITY));
  ck_assert_double_nan(s21_sqrt(-S21_INF));
  ck_assert_double_nan(sqrt(-INFINITY));
  ck_assert_double_nan(s21_sqrt(-5));
  ck_assert_double_nan(s21_sqrt(-0.000001));
  ck_assert_double_eq_tol(s21_sqrt(1000), sqrt(1000), 1e-7);
  ck_assert_double_eq_tol(s21_sqrt(0.000001), sqrt(0.000001), 1e-7);
}
END_TEST

START_TEST(test1_log) {
  ck_assert_ldouble_infinite(s21_log(0.0));
  ck_assert_ldouble_infinite(s21_log(0.0000001));
  ck_assert_ldouble_infinite(s21_log(S21_INF));
  ck_assert_ldouble_infinite(s21_log(S21_INF));
  ck_assert_ldouble_eq_tol(s21_log(1.0001), (long double)log(1.0001), s21_EPS);
  ck_assert_ldouble_nan(s21_log(-1.0001));
  ck_assert_ldouble_eq_tol(s21_log(2), (long double)log(2), s21_EPS);
  ck_assert_ldouble_eq_tol(s21_log(1.5), (long double)log(1.5), s21_EPS);
  ck_assert_ldouble_eq_tol(s21_log(15), (long double)log(15), s21_EPS);
  ck_assert_ldouble_eq_tol(s21_log(s21_EXP + 1e-16),
                           (long double)log(s21_EXP + 1e-16), s21_EPS);
  ck_assert_ldouble_eq_tol(s21_log(0.9999), (long double)log(0.9999), s21_EPS);
  ck_assert_ldouble_eq_tol(s21_log(100.5), (long double)log(100.5), s21_EPS);
  ck_assert_double_nan(s21_log(S21_NAN));
  ck_assert_double_nan(s21_log(-3));
  ck_assert_double_eq(log(INFINITY), s21_log(S21_INF));
  ck_assert_double_nan(s21_log(-S21_INF));
  ck_assert_double_eq(log(1), s21_log(1));
  ck_assert_double_eq_tol(log(2), s21_log(2), s21_EPS);
  ck_assert_double_nan(s21_log(-S21_INF * 2));
  ck_assert_double_eq_tol(log(0.0001), s21_log(0.0001), s21_EPS);
}
END_TEST

START_TEST(test2_log) {
  for (double k = 1; k < 100; k += 13.2) {
    double a = s21_log(k);
    double b = log(k);
    ck_assert_double_eq_tol(a, b, s21_EPS);
  }
  for (double k = 0.1; k < 4; k += 0.24) {
    double a = s21_log(k);
    double b = log(k);
    ck_assert_double_eq_tol(a, b, s21_EPS);
  }
  for (double k = 0.1; k < 10000; k += 123) {
    double a = s21_log(k);
    double b = log(k);
    ck_assert_double_eq_tol(a, b, s21_EPS);
  }
  for (double k = 0.000005; k < 1; k *= 5) {
    double a = s21_log(k);
    double b = log(k);
    ck_assert_double_eq_tol(a, b, s21_EPS);
  }
}
END_TEST

START_TEST(test1_sin) {
  for (int R = 20; R >= -20; R -= 4)
    for (double k = 2 * s21_PI; k > -2 * s21_PI; k -= s21_PI / 9)
      ck_assert_ldouble_eq_tol(sinl(k + R * s21_PI), s21_sin(k + R * s21_PI),
                               s21_EPS);
  for (int R = 20; R >= -20; R -= 2)
    for (double k = 2 * s21_PI; k > -2 * s21_PI; k -= s21_PI / 6)
      ck_assert_ldouble_eq_tol(sinl(k + R * s21_PI), s21_sin(k + R * s21_PI),
                               s21_EPS);
  for (double i = -223.654; i <= 148.522; i += 2.456)
    ck_assert_double_eq_tol(sinl(i), s21_sin(i), s21_EPS);
  for (double i = -10009.6; i <= -9808.0; i += 0.1)
    ck_assert_double_eq_tol(sinl(i), s21_sin(i), s21_EPS);
  for (double i = 9809.6; i <= 10890.0; i += 0.1)
    ck_assert_double_eq_tol(sinl(i), s21_sin(i), s21_EPS);
  for (double i = -1.000000; i <= 1.000000; i += 0.00001)
    ck_assert_double_eq_tol(sinl(i), s21_sin(i), s21_EPS);
}
END_TEST

START_TEST(test2_sin) {
  ck_assert_ldouble_eq_tol(sinl(0.0), s21_sin(0.0), s21_EPS);
  ck_assert_ldouble_eq_tol(sinl(s21_PI * 2), s21_sin(s21_PI * 2), s21_EPS);
  ck_assert_ldouble_eq_tol(sinl(3 * s21_PI * 2), s21_sin(3 * s21_PI * 2),
                           s21_EPS);
  ck_assert_ldouble_eq_tol(sinl(2 * s21_PI * 2), s21_sin(2 * s21_PI * 2),
                           s21_EPS);
  ck_assert_ldouble_eq_tol(sinl(-2 * s21_PI * 2), s21_sin(-2 * s21_PI * 2),
                           s21_EPS);
  ck_assert_ldouble_eq_tol(sinl(-s21_PI), s21_sin(-s21_PI), s21_EPS);
  ck_assert_ldouble_eq_tol(sinl(-0.0), s21_sin(-0.0), s21_EPS);
  ck_assert_ldouble_eq_tol(sinl(12415.12415), s21_sin(12415.12415), s21_EPS);
  ck_assert_ldouble_eq_tol(sinl(-124345.9999), s21_sin(-124345.9999), s21_EPS);
  ck_assert_ldouble_eq_tol(sinl(11.010101), s21_sin(11.010101), s21_EPS);
  ck_assert_ldouble_nan(s21_sin(S21_INF));
  ck_assert_ldouble_nan(s21_sin(-S21_INF));
  ck_assert_ldouble_nan(s21_sin(S21_NAN));
  ck_assert_double_nan(s21_sin(S21_NAN));
  ck_assert_double_nan(s21_sin(S21_INF));
  ck_assert_double_nan(s21_sin(-S21_INF));
  ck_assert_double_nan(s21_sin(-0.0 / 0.0));
}
END_TEST

START_TEST(test1_cos) {
  for (int R = 20; R >= -20; R -= 4)
    for (double k = 2 * s21_PI; k > -2 * s21_PI; k -= s21_PI / 9)
      ck_assert_ldouble_eq_tol(cos(k + R * s21_PI), s21_cos(k + R * s21_PI),
                               s21_EPS);
  for (int R = 20; R >= -20; R -= 2)
    for (double k = 2 * s21_PI; k > -2 * s21_PI; k -= s21_PI / 6)
      ck_assert_ldouble_eq_tol(cosl(k + R * s21_PI), s21_cos(k + R * s21_PI),
                               s21_EPS);
  for (double i = -223.654; i <= 148.522; i += 2.456)
    ck_assert_double_eq_tol(cosl(i), s21_cos(i), s21_EPS);
  for (double i = -10009.6; i <= -9808.0; i += 0.1)
    ck_assert_double_eq_tol(cosl(i), s21_cos(i), s21_EPS);
  for (long double i = 9809.6; i <= 10890.0; i += 0.1)
    ck_assert_ldouble_eq_tol(cosl(i), s21_cos(i), s21_EPS);
  for (double i = -1.000000; i <= 1.000000; i += 0.00001)
    ck_assert_double_eq_tol(cosl(i), s21_cos(i), s21_EPS);
}
END_TEST

START_TEST(test2_cos) {
  ck_assert_ldouble_eq_tol(cosl(0.0), s21_cos(0.0), s21_EPS);
  ck_assert_ldouble_eq_tol(cosl(s21_PI * 2), s21_cos(s21_PI * 2), s21_EPS);
  ck_assert_ldouble_eq_tol(cosl(3 * s21_PI * 2), s21_cos(3 * s21_PI * 2),
                           s21_EPS);
  ck_assert_ldouble_eq_tol(cosl(2 * s21_PI * 2), s21_cos(2 * s21_PI * 2),
                           s21_EPS);
  ck_assert_ldouble_eq_tol(cosl(-2 * s21_PI * 2), s21_cos(-2 * s21_PI * 2),
                           s21_EPS);
  ck_assert_ldouble_eq_tol(cosl(-s21_PI), s21_cos(-s21_PI), s21_EPS);
  ck_assert_ldouble_eq_tol(cosl(-0.0), s21_cos(-0.0), s21_EPS);
  ck_assert_ldouble_eq_tol(cosl(12415.12415), s21_cos(12415.12415), s21_EPS);
  ck_assert_ldouble_eq_tol(cosl(-124345.9999), s21_cos(-124345.9999), s21_EPS);
  ck_assert_ldouble_eq_tol(cosl(11.010101), s21_cos(11.010101), s21_EPS);
  ck_assert_ldouble_nan(s21_cos(S21_INF));
  ck_assert_ldouble_nan(s21_cos(-S21_INF));
  ck_assert_ldouble_nan(s21_cos(S21_NAN));
  ck_assert_double_nan(s21_cos(S21_NAN));
  ck_assert_double_nan(s21_cos(S21_INF));
  ck_assert_double_nan(s21_cos(-S21_INF));
  ck_assert_double_nan(s21_cos(-0.0 / 0.0));
}
END_TEST

START_TEST(test_tan) {
  ck_assert_ldouble_eq_tol(tanl(0.123456), s21_tan(0.123456), s21_EPS);
  ck_assert_ldouble_nan(s21_tan(S21_NAN));
  ck_assert_ldouble_nan(s21_tan(S21_INF));
  ck_assert_ldouble_nan(s21_tan(-S21_INF));
  ck_assert_ldouble_eq_tol(tanl(-0.123456), s21_tan(-0.123456), s21_EPS);
  ck_assert_ldouble_eq_tol(tanl(11115.123456), s21_tan(11115.123456), s21_EPS);
  ck_assert_ldouble_eq_tol(tanl(s21_PI), s21_tan(s21_PI), s21_EPS);
  ck_assert_ldouble_eq_tol(tan(s21_PI / 2.0), s21_tan(s21_PI / 2.0), s21_EPS);
  ck_assert_ldouble_eq_tol(tan(-s21_PI / 2.0), s21_tan(-s21_PI / 2.0), s21_EPS);
  ck_assert_ldouble_eq_tol(tanl(0.000001), s21_tan(0.000001), s21_EPS);
  ck_assert_ldouble_eq_tol(tanl(-0.0), s21_tan(-0.0), s21_EPS);
  ck_assert_ldouble_nan(s21_tan(-0.0 / 0.0));
  for (double i = 1.0; i >= -1.0; i -= 0.0001)
    ck_assert_ldouble_eq_tol(tanl(i), s21_tan(i), s21_EPS);
}
END_TEST

START_TEST(test_atan) {
  ck_assert_ldouble_eq_tol(atan(500.000), s21_atan(500.000), 1e-4);
  for (double i = -565.324; i <= 789.532; i += 50.6235)
    ck_assert_ldouble_eq_tol(atan(i), s21_atan(i), 1e-6);
  for (double i = -1.000000; i <= 1.000000; i += 0.0001)
    ck_assert_ldouble_eq_tol(atan(i), s21_atan(i), 1e-6);
  ck_assert_ldouble_eq_tol(atan(-INFINITY), s21_atan(-INFINITY), 1e-7);
  ck_assert_ldouble_eq_tol(atan(0.0), s21_atan(0.0), 1e-7);
  ck_assert_ldouble_nan(s21_atan(0.0 / 0.0));
  ck_assert_ldouble_eq_tol(atan(0.0), s21_atan(0.0), 1e-7);
  for (double i = -123456.789456; i <= 123456.789456; i += 1.0)
    ck_assert_ldouble_eq_tol(atan(i), s21_atan(i), 1e-07);
  ck_assert_ldouble_eq_tol(atan(INFINITY), s21_atan(S21_INF), 1e-7);
  ck_assert_ldouble_eq_tol(atan(-2.78965), s21_atan(-2.78965), 1e-7);
}
END_TEST

START_TEST(test_asin) {
  for (double i = -1.000000; i <= 1.000000; i += 0.00005)
    ck_assert_ldouble_eq_tol(asin(i), s21_asin(i), 1e-6);
  for (double i = -1.000000; i <= 1.000000; i += 0.0001)
    ck_assert_ldouble_eq_tol(asin(i), s21_asin(i), 1e-6);
  ck_assert_ldouble_nan(s21_asin(S21_NAN));
  ck_assert_ldouble_eq_tol(asin(1), s21_asin(1), 1e-7);
  ck_assert_ldouble_eq_tol(asin(-1), s21_asin(-1), 1e-6);
  for (double i = -1.000000; i <= 1.000000; i += 0.00003)
    ck_assert_ldouble_eq_tol(asin(i), s21_asin(i), 1e-6);
  ck_assert_ldouble_eq_tol(asin(0), s21_asin(0), 1e-6);
  ck_assert_ldouble_nan(s21_asin(INFINITY));
  ck_assert_ldouble_nan(s21_asin(-INFINITY));
  ck_assert_ldouble_nan(s21_asin(-252.568));
  ck_assert_ldouble_nan(s21_asin(555));
  ck_assert_ldouble_nan(s21_asin(s21_sqrt(-1)));
}
END_TEST

START_TEST(test_acos) {
  ck_assert_ldouble_eq(acos(0), s21_acos(0));
  for (double i = -1.000000; i <= 1; i += 0.00005)
    ck_assert_ldouble_eq_tol(acos(i), s21_acos(i), 1e-6);
  ck_assert_ldouble_nan(s21_acos(-S21_INF));
  for (double i = -1.000000; i <= 1.000000; i += 0.0001)
    ck_assert_ldouble_eq_tol(acos(i), s21_acos(i), 1e-6);
  for (double i = -1.000000; i <= 1.000000; i += 0.00003)
    ck_assert_ldouble_eq_tol(acos(i), s21_acos(i), 1e-6);
  ck_assert_ldouble_nan(s21_acos(S21_NAN));
  ck_assert_ldouble_nan(s21_acos(-1.0 / 0.0));
  ck_assert_ldouble_nan(s21_acos(6.654));
  ck_assert_ldouble_nan(s21_acos(1.5 * s21_PI));
  ck_assert_ldouble_eq_tol(acos(0.00001), s21_acos(0.00001), 1e-6);
}
END_TEST

int main() {
  Suite *suite = suite_create("Test Suite");
  TCase *tc = tcase_create("Test Cases");
  tcase_add_test(tc, test_abs);
  tcase_add_test(tc, test_fabs);
  tcase_add_test(tc, test_fmod);
  tcase_add_test(tc, test_floor);
  tcase_add_test(tc, test_ceil);
  tcase_add_test(tc, test_exp);
  tcase_add_test(tc, test1_pow);
  tcase_add_test(tc, test2_pow);
  tcase_add_test(tc, test_sqrt);
  tcase_add_test(tc, test1_log);
  tcase_add_test(tc, test2_log);
  tcase_add_test(tc, test1_sin);
  tcase_add_test(tc, test2_sin);
  tcase_add_test(tc, test1_cos);
  tcase_add_test(tc, test2_cos);
  tcase_add_test(tc, test_tan);
  tcase_add_test(tc, test_atan);
  tcase_add_test(tc, test_asin);
  tcase_add_test(tc, test_acos);
  suite_add_tcase(suite, tc);

  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  int failures = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (failures == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}