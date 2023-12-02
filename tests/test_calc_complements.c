#include "test.h"

START_TEST(s21_calc_complements_0) {
  matrix_t A, result;
  int size = 3;
  s21_create_matrix(size, size, &A);

  // MATRIX A
  //
  //  1  2  3
  //  4  5  6
  //  7  8  9

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  int error = s21_calc_complements(&A, &result);
  int true_error = EXIT_OK;

  matrix_t true_result;
  s21_create_matrix(size, size, &true_result);

  //  MATRIX RESULT
  //
  //  -3  6   -3
  //  6  -12  6
  //  -3  6   -3

  true_result.matrix[0][0] = -3;
  true_result.matrix[0][1] = 6;
  true_result.matrix[0][2] = -3;
  true_result.matrix[1][0] = 6;
  true_result.matrix[1][1] = -12;
  true_result.matrix[1][2] = 6;
  true_result.matrix[2][0] = -3;
  true_result.matrix[2][1] = 6;
  true_result.matrix[2][2] = -3;

  int answer = s21_eq_matrix(&result, &true_result);
  int true_answer = SUCCESS;

  ck_assert_int_eq(answer, true_answer);
  ck_assert_int_eq(error, true_error);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&true_result);
}
END_TEST

START_TEST(s21_calc_complements_1) {
  matrix_t A, result;
  int size = 2;
  s21_create_matrix(size, size, &A);

  // MATRIX A
  //
  //  1  1
  //  1  1

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 1;
  A.matrix[1][0] = 1;
  A.matrix[1][1] = 1;

  int error = s21_calc_complements(&A, &result);
  int true_error = EXIT_OK;

  matrix_t true_result;
  s21_create_matrix(size, size, &true_result);

  //  MATRIX RESULT
  //
  //   1  -1
  //  -1   1

  true_result.matrix[0][0] = 1;
  true_result.matrix[0][1] = -1;
  true_result.matrix[1][0] = -1;
  true_result.matrix[1][1] = 1;

  int answer = s21_eq_matrix(&result, &true_result);
  int true_answer = SUCCESS;

  ck_assert_int_eq(answer, true_answer);
  ck_assert_int_eq(error, true_error);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&true_result);
}
END_TEST

START_TEST(s21_calc_complements_2) {
  matrix_t A, result;
  s21_create_matrix(3, 4, &A);

  int error = s21_calc_complements(&A, &result);
  int true_error = EXIT_CALC_ERROR;

  ck_assert_int_eq(error, true_error);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_calc_complements_3) {
  matrix_t A, result;
  int size = 3;
  s21_create_matrix(size, size, &A);

  // MATRIX A
  //
  //  1  2  3
  //  0  4  2
  //  5  2  1

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;

  int error = s21_calc_complements(&A, &result);
  int true_error = EXIT_OK;

  matrix_t true_result;
  s21_create_matrix(size, size, &true_result);

  //  MATRIX RESULT
  //
  //   0   10  -20
  //  -4  -14   -8
  //  -8    2    4

  true_result.matrix[0][0] = 0;
  true_result.matrix[0][1] = 10;
  true_result.matrix[0][2] = -20;
  true_result.matrix[1][0] = 4;
  true_result.matrix[1][1] = -14;
  true_result.matrix[1][2] = 8;
  true_result.matrix[2][0] = -8;
  true_result.matrix[2][1] = -2;
  true_result.matrix[2][2] = 4;

  int answer = s21_eq_matrix(&result, &true_result);
  int true_answer = SUCCESS;

  ck_assert_int_eq(answer, true_answer);
  ck_assert_int_eq(error, true_error);

  s21_remove_matrix(&A);
  s21_remove_matrix(&true_result);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_calc_complements_4) {
  matrix_t A, result;
  s21_create_matrix(1, 2, &A);

  int error = s21_calc_complements(&A, &result);
  int true_error = EXIT_CALC_ERROR;

  ck_assert_int_eq(error, true_error);

  s21_remove_matrix(&A);
}
END_TEST

Suite *test_calc_complements() {
  Suite *s = suite_create("\033[47m==S21_CALC_COMPLEMENTS==\033[0m");
  TCase *tc = tcase_create("calc_complements_tc");

  tcase_add_test(tc, s21_calc_complements_0);
  tcase_add_test(tc, s21_calc_complements_1);
  tcase_add_test(tc, s21_calc_complements_2);
  tcase_add_test(tc, s21_calc_complements_3);
  tcase_add_test(tc, s21_calc_complements_4);

  suite_add_tcase(s, tc);
  return s;
}