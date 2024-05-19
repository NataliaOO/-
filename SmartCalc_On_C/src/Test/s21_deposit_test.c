#include <check.h>

#include "smart_calc.h"

#define SHOW_FAILED true

START_TEST(s21_deposit_test_1) {
  DepositInput input = {50000, 24, 10, 0, true, false, true, {{0}}, {{0}}};
  DepositOutput res = calculate_deposit(input);
  DepositOutput exp = {11068.465082, 0, 61068.465082};

  ck_assert(fabs(res.total_earned - exp.total_earned) < 1e-6);
  ck_assert(fabs(res.tax_amount - exp.tax_amount) < 1e-6);
  ck_assert(fabs(res.total_amount - exp.total_amount) < 1e-6);
}
END_TEST

START_TEST(s21_deposit_test_2) {
  DepositInput input = {50000, 24, 10, 13, false, true, true, {{0}}, {{0}}};
  DepositOutput res = calculate_deposit(input);
  DepositOutput exp = {10000, 0, 60000};

  ck_assert(fabs(res.total_earned - exp.total_earned) < 1e-6);
  ck_assert(fabs(res.tax_amount - exp.tax_amount) < 1e-6);
  ck_assert(fabs(res.total_amount - exp.total_amount) < 1e-6);
}
END_TEST

START_TEST(s21_deposit_test_3) {
  DepositInput input = {50000, 24, 10, 0, true, false, false, {{0}}, {{0}}};
  DepositOutput res = calculate_deposit(input);
  DepositOutput exp = {10000, 0, 60000};

  ck_assert(fabs(res.total_earned - exp.total_earned) < 1e-6);
  ck_assert(fabs(res.tax_amount - exp.tax_amount) < 1e-6);
  ck_assert(fabs(res.total_amount - exp.total_amount) < 1e-6);
}
END_TEST

START_TEST(s21_deposit_test_4) {
  DepositInput input = {
      50000, 24,
      10,    13,
      true,  false,
      true,  .replenishments = {{.replenishment = 2000, .day = 90}},
      {{0}}};
  DepositOutput res = calculate_deposit(input);
  DepositOutput exp = {11511.203685, 0, 63511.203685};

  ck_assert(fabs(res.total_earned - exp.total_earned) < 1e-6);
  ck_assert(fabs(res.tax_amount - exp.tax_amount) < 1e-6);
  ck_assert(fabs(res.total_amount - exp.total_amount) < 1e-6);
}
END_TEST

START_TEST(s21_deposit_test_5) {
  DepositInput input = {
      50000, 24,    10,
      13,    true,  false,
      true,  {{0}}, .withdrawals = {{.withdrawal = 2000, .day = 365}}};
  DepositOutput res = calculate_deposit(input);
  DepositOutput exp = {10625.726479, 0, 58625.726479};

  ck_assert(fabs(res.total_earned - exp.total_earned) < 1e-6);
  ck_assert(fabs(res.tax_amount - exp.tax_amount) < 1e-6);
  ck_assert(fabs(res.total_amount - exp.total_amount) < 1e-6);
}
END_TEST

START_TEST(s21_deposit_test_6) {
  DepositInput input = {10000000, 24, 10, 13, true, false, false, {{0}}, {{0}}};
  DepositOutput res = calculate_deposit(input);
  DepositOutput exp = {1999999.999999, 260000.000000, 11999999.999999};

  ck_assert(fabs(res.total_earned - exp.total_earned) < 1e-6);
  ck_assert(fabs(res.tax_amount - exp.tax_amount) < 1e-6);
  ck_assert(fabs(res.total_amount - exp.total_amount) < 1e-6);
}
END_TEST

Suite *s21_sc_suite_create() {
  Suite *suite = suite_create("s21_sc_test");
  TCase *tc_core = tcase_create("tcase_core_s21_sc_test");

  tcase_add_test(tc_core, s21_deposit_test_1);
  tcase_add_test(tc_core, s21_deposit_test_2);
  tcase_add_test(tc_core, s21_deposit_test_3);
  tcase_add_test(tc_core, s21_deposit_test_4);
  tcase_add_test(tc_core, s21_deposit_test_5);
  tcase_add_test(tc_core, s21_deposit_test_6);

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
