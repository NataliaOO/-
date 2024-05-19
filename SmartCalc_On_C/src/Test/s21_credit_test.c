#include <check.h>

#include "smart_calc.h"

#define SHOW_FAILED true

START_TEST(s21_credit_test_1) {
  CreditInput input = {300000.0, 18, true, false, 15.0, false, true};
  CreditOutput res = calculate_credit(input);
  CreditOutput exp = {20416.666667, 16875.0, 35625.0, 335625.0};

  ck_assert(fabs(res.monthly_payment - exp.monthly_payment) < 1e-6);
  ck_assert(fabs(res.monthly_payment_last - exp.monthly_payment_last) < 1e-6);
  ck_assert(fabs(res.overpayment - exp.overpayment) < 1e-6);
  ck_assert(fabs(res.total - exp.total) < 1e-6);
}
END_TEST

START_TEST(s21_credit_test_2) {
  CreditInput input = {300000.0, 18, true, false, 15.0, true, false};
  CreditOutput res = calculate_credit(input);
  CreditOutput exp = {
      18715.43618,
      0.0,
      36877.851232,
      336877.851232,
  };

  ck_assert(fabs(res.monthly_payment - exp.monthly_payment) < 1e-6);
  ck_assert(fabs(res.monthly_payment_last - exp.monthly_payment_last) < 1e-6);
  ck_assert(fabs(res.overpayment - exp.overpayment) < 1e-6);
  ck_assert(fabs(res.total - exp.total) < 1e-6);
}
END_TEST

START_TEST(s21_credit_test_3) {
  CreditInput input = {300000.0, 18, false, true, 15.0, false, true};
  CreditOutput res = calculate_credit(input);
  CreditOutput exp = {
      5138.888889,
      1406.25,
      406875,
      706875,
  };

  ck_assert(fabs(res.monthly_payment - exp.monthly_payment) < 1e-6);
  ck_assert(fabs(res.monthly_payment_last - exp.monthly_payment_last) < 1e-6);
  ck_assert(fabs(res.overpayment - exp.overpayment) < 1e-6);
  ck_assert(fabs(res.total - exp.total) < 1e-6);
}
END_TEST

START_TEST(s21_credit_test_4) {
  CreditInput input = {300000.0, 18, false, true, 15.0, true, false};
  CreditOutput res = calculate_credit(input);
  CreditOutput exp = {
      4025.072259,
      0.0,
      569415.607906,
      869415.607906,
  };

  ck_assert(fabs(res.monthly_payment - exp.monthly_payment) < 1e-6);
  ck_assert(fabs(res.monthly_payment_last - exp.monthly_payment_last) < 1e-6);
  ck_assert(fabs(res.overpayment - exp.overpayment) < 1e-6);
  ck_assert(fabs(res.total - exp.total) < 1e-6);
}
END_TEST

Suite *s21_sc_suite_create() {
  Suite *suite = suite_create("s21_sc_test");
  TCase *tc_core = tcase_create("tcase_core_s21_sc_test");

  tcase_add_test(tc_core, s21_credit_test_1);
  tcase_add_test(tc_core, s21_credit_test_2);
  tcase_add_test(tc_core, s21_credit_test_3);
  tcase_add_test(tc_core, s21_credit_test_4);

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
