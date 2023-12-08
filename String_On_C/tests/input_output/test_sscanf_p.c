#include "../tests.h"

START_TEST(sscanf_spec_p_1) {
  void *a = NULL, *b = NULL;
  ck_assert_int_eq(s21_sscanf("0x1234567890", "%p", &a),
                   sscanf("0x1234567890", "%p", &b));
  ck_assert_ptr_eq(a, b);
}
END_TEST

START_TEST(sscanf_spec_p_2) {
  void *a = NULL, *b = NULL;
  ck_assert_int_eq(s21_sscanf("0xabc", "%p", &a), sscanf("0xabc", "%p", &b));
  ck_assert_ptr_eq(a, b);
}
END_TEST

START_TEST(sscanf_spec_p_3) {
  // no prefix
  void *a = NULL, *b = NULL;
  ck_assert_int_eq(s21_sscanf("1234567890", "%p", &a),
                   sscanf("1234567890", "%p", &b));
  ck_assert_ptr_eq(a, b);
}
END_TEST

START_TEST(sscanf_spec_p_4) {
  // -
  void *a = NULL, *b = NULL;
  ck_assert_int_eq(s21_sscanf("-1234567890", "%p", &a),
                   sscanf("-1234567890", "%p", &b));
  ck_assert_ptr_eq(a, b);
}
END_TEST

Suite *test_sscanf_p(void) {
  Suite *s = suite_create("\033[42m==S21_SSCANF_PERCENT==\033[0m");
  TCase *tc = tcase_create("sscanf_tc");

  tcase_add_test(tc, sscanf_spec_p_1);
  tcase_add_test(tc, sscanf_spec_p_2);
  tcase_add_test(tc, sscanf_spec_p_3);
  tcase_add_test(tc, sscanf_spec_p_4);

  suite_add_tcase(s, tc);
  return s;
}