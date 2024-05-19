#include <check.h>

#include "smart_calc.h"

#define SHOW_FAILED true

START_TEST(s21_standart_test_1) {
  char input[255] = "2+2";
  Data *top = malloc(2 * strlen(input) * sizeof(Data));
  double exp = 4.0;

  int status = to_rpn(input, &top);
  double res = evaluate(top, 1);
  free(top);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(res, exp, 1e-6);
}
END_TEST

START_TEST(eq_failure_1_test) {
  char input[255] = "(=";
  Data *top = malloc(2 * strlen(input) * sizeof(Data));

  int status = to_rpn(input, &top);
  free(top);

  ck_assert_int_eq(status, EXPR_ERROR);
}

START_TEST(eq_failure_2_test) {
  char input[255] = ")=";
  Data *top = malloc(2 * strlen(input) * sizeof(Data));

  int status = to_rpn(input, &top);
  free(top);

  ck_assert_int_eq(status, EXPR_ERROR);
}
END_TEST

START_TEST(bad_expr_failure_1_test) {
  char input[255] = "Sin)=Sqrt=";
  Data *top = malloc(2 * strlen(input) * sizeof(Data));

  int status = to_rpn(input, &top);
  free(top);

  ck_assert_int_eq(status, EXPR_ERROR);
}
END_TEST

START_TEST(s21_standart_test_2) {
  char input[255] = "999999999999+777";
  Data *top = malloc(2 * strlen(input) * sizeof(Data));
  double exp = 999999999999 + 777;

  int status = to_rpn(input, &top);
  double res = evaluate(top, 1);
  free(top);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(res, exp, 1e-6);
}
END_TEST

START_TEST(s21_standart_test_3) {
  char input[255] = "8901234+567";
  Data *top = malloc(2 * strlen(input) * sizeof(Data));
  double exp = 8901801;

  int status = to_rpn(input, &top);
  double res = evaluate(top, 1);
  free(top);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(res, exp, 1e-6);
}
END_TEST

START_TEST(s21_standart_test_4) {
  char input[255] = "2^3^2";
  Data *top = malloc(2 * strlen(input) * sizeof(Data));
  double exp = 512;

  int status = to_rpn(input, &top);
  double res = evaluate(top, 1);
  free(top);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(res, exp, 1e-6);
}
END_TEST

START_TEST(s21_standart_test_5) {
  char input[255] = "92345559/5";
  Data *top = malloc(2 * strlen(input) * sizeof(Data));
  double exp = 18469111.8;

  int status = to_rpn(input, &top);
  double res = evaluate(top, 1);
  free(top);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(res, exp, 1e-6);
}
END_TEST

START_TEST(s21_standart_test_6) {
  char input[255] = "92345559*(0.3)";
  Data *top = malloc(2 * strlen(input) * sizeof(Data));
  double exp = 27703667.7;

  int status = to_rpn(input, &top);
  double res = evaluate(top, 1);
  free(top);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(res, exp, 1e-6);
}
END_TEST

START_TEST(s21_standart_test_7) {
  char input[255] = "14Mod3";
  Data *top = malloc(2 * strlen(input) * sizeof(Data));
  double exp = 2;

  int status = to_rpn(input, &top);
  double res = evaluate(top, 1);
  free(top);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(res, exp, 1e-6);
}
END_TEST

START_TEST(s21_standart_test_8) {
  char input[255] = "Cos(2-1)/Sin(5)*Tan(1)^1";
  Data *top = malloc(2 * strlen(input) * sizeof(Data));
  double exp = -0.877516;

  int status = to_rpn(input, &top);
  double res = evaluate(top, 1);
  free(top);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(res, exp, 1e-6);
}
END_TEST

START_TEST(s21_standart_test_9) {
  char input[] = "Cos(1)+Sin(2)+Ln(3)+Tan(4)+Sqrt(5)";
  Data *top = malloc(2 * strlen(input) * sizeof(Data));
  to_rpn(input, &top);
  double res = evaluate(top, 0);
  double real = 5.94210128121;
  free(top);

  ck_assert_double_eq_tol(real, res, 1e-06);
}
END_TEST

START_TEST(s21_standart_test_10) {
  char input[] = "-Cos(1)+100-Sqrt(2^Sin(23))";
  Data *top = malloc(2 * strlen(input) * sizeof(Data));
  to_rpn(input, &top);
  double res = evaluate(top, 0);
  double real = 98.713882652988;
  free(top);
  ck_assert_double_eq_tol(real, res, 1e-06);
}
END_TEST

START_TEST(s21_standart_test_11) {
  char input[] = "3^^3";
  Data *top = malloc(2 * strlen(input) * sizeof(Data));
  int res = to_rpn(input, &top);
  free(top);
  ck_assert_int_eq(DATA_ERROR, res);
}
END_TEST

START_TEST(s21_standart_test_12) {
  char input[] = "3*(sin((((123))";
  Data *top = malloc(2 * strlen(input) * sizeof(Data));
  int res = to_rpn(input, &top);
  free(top);
  ck_assert_int_eq(EXPR_ERROR, res);
}
END_TEST

START_TEST(s21_standart_test_13) {
  char input[] = "son(123)";
  Data *top = malloc(2 * strlen(input) * sizeof(Data));
  int res = to_rpn(input, &top);
  free(top);
  ck_assert_int_eq(EXPR_ERROR, res);
}
END_TEST

START_TEST(s21_standart_test_14) {
  char input[] = "2^2^3";
  Data *top = malloc(2 * strlen(input) * sizeof(Data));
  to_rpn(input, &top);
  double res = evaluate(top, 0);
  double real = 256;
  free(top);
  ck_assert_double_eq_tol(real, res, 1e-06);
}

START_TEST(s21_standart_unary_test_1) {
  char input[255] = "0.999/(-0.9)";
  Data *top = malloc(2 * strlen(input) * sizeof(Data));
  double exp = -1.11;

  int status = to_rpn(input, &top);
  double res = evaluate(top, 1);
  free(top);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(res, exp, 1e-6);
}
END_TEST

START_TEST(s21_standart_unary_test_2) {
  char input[255] = "4394092-49348938493-823498-(-384398493840)";
  Data *top = malloc(2 * strlen(input) * sizeof(Data));
  double exp = 335053125941;

  int status = to_rpn(input, &top);
  double res = evaluate(top, 1);
  free(top);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(res, exp, 1e-6);
}
END_TEST

START_TEST(s21_standart_unary_test_3) {
  char input[255] = "Ln(10)-(-Log(2))";
  Data *top = malloc(2 * strlen(input) * sizeof(Data));
  double exp = 2.603615;

  int status = to_rpn(input, &top);
  double res = evaluate(top, 1);
  free(top);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(res, exp, 1e-6);
}
END_TEST

Suite *s21_sc_suite_create() {
  Suite *suite = suite_create("s21_sc_test");
  TCase *tc_core = tcase_create("tcase_core_s21_sc_test");
  tcase_add_test(tc_core, bad_expr_failure_1_test);
  tcase_add_test(tc_core, eq_failure_1_test);
  tcase_add_test(tc_core, eq_failure_2_test);
  tcase_add_test(tc_core, s21_standart_test_1);
  tcase_add_test(tc_core, s21_standart_test_2);
  tcase_add_test(tc_core, s21_standart_test_3);
  tcase_add_test(tc_core, s21_standart_test_4);
  tcase_add_test(tc_core, s21_standart_test_5);
  tcase_add_test(tc_core, s21_standart_test_6);
  tcase_add_test(tc_core, s21_standart_test_7);
  tcase_add_test(tc_core, s21_standart_test_8);
  tcase_add_test(tc_core, s21_standart_test_9);
  tcase_add_test(tc_core, s21_standart_test_10);
  tcase_add_test(tc_core, s21_standart_test_11);
  tcase_add_test(tc_core, s21_standart_test_12);
  tcase_add_test(tc_core, s21_standart_test_13);
  tcase_add_test(tc_core, s21_standart_test_14);
  tcase_add_test(tc_core, s21_standart_unary_test_1);
  tcase_add_test(tc_core, s21_standart_unary_test_2);
  tcase_add_test(tc_core, s21_standart_unary_test_3);

  suite_add_tcase(suite, tc_core);

  return suite;
}

int main() {
  int failed_count = 0;

  Suite *suite = s21_sc_suite_create();
  SRunner *suite_runner = srunner_create(suite);

  srunner_run_all(suite_runner, CK_NORMAL);
  failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);

  return failed_count != 0 && !SHOW_FAILED ? EXIT_FAILURE : EXIT_SUCCESS;
}
