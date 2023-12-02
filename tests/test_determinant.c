#include "test.h"

START_TEST(s21_determinant_0) {
  matrix_t A;
  double result;
  s21_create_matrix(1, 1, &A);

  A.matrix[0][0] = 21;

  int error = s21_determinant(&A, &result);
  int true_error = EXIT_OK;

  double true_result = 21;

  ck_assert_int_eq(error, true_error);
  ck_assert_uint_eq(result, true_result);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_1) {
  matrix_t A;
  double result;
  s21_create_matrix(2, 2, &A);

  // MATRIX A
  //
  //  1  2
  //  3  4

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  int error = s21_determinant(&A, &result);
  int true_error = EXIT_OK;

  double true_result = -2;

  ck_assert_int_eq(error, true_error);
  ck_assert_uint_eq(result, true_result);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_2) {
  matrix_t A;
  double result;
  s21_create_matrix(3, 3, &A);

  // MATRIX A
  //
  //  1.123    2.001     0.12
  //  3.1203   12344.12  1023.198
  //  0.00001  1234.123  9832.826

  A.matrix[0][0] = 1.123;
  A.matrix[0][1] = 2.001;
  A.matrix[0][2] = 0.12;
  A.matrix[1][0] = 3.1203;
  A.matrix[1][1] = 12344.12;
  A.matrix[1][2] = 1023.198;
  A.matrix[2][0] = 0.00001;
  A.matrix[2][1] = 1234.123;
  A.matrix[2][2] = 9832.826;

  int error = s21_determinant(&A, &result);
  int true_error = EXIT_OK;

  double true_result = 134828024.91163;
  double diff = fabs(true_result - result);

  ck_assert_int_eq(error, true_error);
  ck_assert(diff < 1e-6);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_3) {
  matrix_t A;
  double result;
  s21_create_matrix(2, 3, &A);

  int error = s21_determinant(&A, &result);
  int true_error = EXIT_CALC_ERROR;

  ck_assert_int_eq(error, true_error);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_4) {
  matrix_t A, minor;
  s21_create_matrix(1, 10, &A);

  int error = calculate_minor(&A, 0, 0, &minor);
  int true_error = EXIT_CALC_ERROR;

  ck_assert_int_eq(error, true_error);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_5) {
  matrix_t A, minor;
  s21_create_matrix(6, 10, &A);

  int error = calculate_minor(&A, 12, 1, &minor);
  int true_error = EXIT_CALC_ERROR;

  ck_assert_int_eq(error, true_error);

  s21_remove_matrix(&A);
}
END_TEST

Suite *test_determinant() {
  Suite *s = suite_create("\033[47m==S21_DATERMINAT==\033[0m");
  TCase *tc = tcase_create("determinant_tc");

  tcase_add_test(tc, s21_determinant_0);
  tcase_add_test(tc, s21_determinant_1);
  tcase_add_test(tc, s21_determinant_2);
  tcase_add_test(tc, s21_determinant_3);
  tcase_add_test(tc, s21_determinant_4);
  tcase_add_test(tc, s21_determinant_5);

  suite_add_tcase(s, tc);
  return s;
}