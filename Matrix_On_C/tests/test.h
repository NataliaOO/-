#ifndef SRC_TESTS_H
#define SRC_TESTS_H

#include <check.h>
#include <stdio.h>

#include "../s21_matrix.h"

Suite *test_create_matrix();
Suite *test_eq_matrix();
Suite *test_sum_matrix();
Suite *test_sub_matrix();
Suite *test_mult_number_matrix();
Suite *test_mult_matrix();
Suite *test_transpose_matrix();
Suite *test_determinant();
Suite *test_calc_complements();
Suite *test_inverse_matrix();

//*********************//
double get_rand(double min, double max);

#endif  // SRC_TESTS_H