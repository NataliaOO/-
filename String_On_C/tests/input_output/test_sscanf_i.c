#include "../tests.h"
START_TEST(sscanf_spec_hhi_dec_1) {
  char format[] = "%hhi%hhi%hhi";
  char str[] = "123 +198 -87";
  unsigned char d1, d2;
  unsigned char q1, q2;
  unsigned char z1, z2;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hhi_dec_2) {
  char format[] = "%hhi %hhi %hhi";
  char str[] = "123 +198 -87";
  unsigned char d1, d2;
  unsigned char q1, q2;
  unsigned char z1, z2;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hhi_dec_3) {
  char format[] = "%1hhi %1hhi %1hhi";
  char str[] = "13 +137 -8";
  unsigned char d1, d2;
  unsigned char q1, q2;
  unsigned char z1 = 0, z2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hhi_dec_4) {
  char format[] = "%2hhi %2hhi %2hhi";
  char str[] = "13 +137 -8";
  unsigned char d1, d2;
  unsigned char q1, q2;
  unsigned char z1, z2;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hhi_dec_5) {
  char format[] = "%3hhi %3hhi %3hhi";
  char str[] = "13 +137 -8";
  unsigned char d1, d2;
  unsigned char q1, q2;
  unsigned char z1, z2;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hhi_dec_6) {
  char format[] = "%30hhi %24hhi %21hhi";
  char str[] = "13 +137 -8";
  unsigned char d1, d2;
  unsigned char q1, q2;
  unsigned char z1, z2;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hhi_dec_7) {
  char format[] = "%hhi %hhi %hhi %hhi";
  char str[] = "2147483647 +2147483648 -2147483648 -2147483649";
  unsigned char d1, d2;
  unsigned char q1, q2;
  unsigned char z1, z2;
  unsigned char w1, w2;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1, &w1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_uint_eq(w1, w2);
}
END_TEST

START_TEST(sscanf_spec_hi_dec_1) {
  char format[] = "%hi%hi%hi";
  char str[] = "123 +198 -87";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1, z2;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hi_dec_2) {
  char format[] = "%hi %hi %hi";
  char str[] = "123 +198 -87";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1, z2;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hi_dec_3) {
  char format[] = "%1hi %1hi %1hi";
  char str[] = "13 +137 -8";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1 = 0, z2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hi_dec_4) {
  char format[] = "%2hi %2hi %2hi";
  char str[] = "13 +137 -8";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1, z2;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hi_dec_5) {
  char format[] = "%3hi %3hi %3hi";
  char str[] = "13 +137 -8";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1, z2;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hi_dec_6) {
  char format[] = "%30hi %24hi %21hi";
  char str[] = "13 +137 -8";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1, z2;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_hi_dec_7) {
  char format[] = "%hi %hi %hi %hi";
  char str[] = "2147483647 +2147483648 -2147483648 -2147483649";
  unsigned short d1, d2;
  unsigned short q1, q2;
  unsigned short z1, z2;
  unsigned short w1, w2;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1, &w1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_uint_eq(w1, w2);
}
END_TEST

START_TEST(sscanf_spec_i_dec_1) {
  char format[] = "%i%i%i";
  char str[] = "123 +198 -87";
  unsigned int d1, d2;
  unsigned int q1, q2;
  unsigned int z1, z2;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_i_dec_2) {
  char format[] = "%i %i %i";
  char str[] = "123 +198 -87";
  unsigned int d1, d2;
  unsigned int q1, q2;
  unsigned int z1, z2;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_i_dec_3) {
  char format[] = "%1i %1i %1i";
  char str[] = "13 +137 -8";
  unsigned int d1, d2;
  unsigned int q1, q2;
  unsigned int z1 = 0, z2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_i_dec_4) {
  char format[] = "%2i %2i %2i";
  char str[] = "13 +137 -8";
  unsigned int d1, d2;
  unsigned int q1, q2;
  unsigned int z1, z2;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_i_dec_5) {
  char format[] = "%3i %3i %3i";
  char str[] = "13 +137 -8";
  unsigned int d1, d2;
  unsigned int q1, q2;
  unsigned int z1, z2;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_i_dec_6) {
  char format[] = "%30i %24i %21i";
  char str[] = "13 +137 -8";
  unsigned int d1, d2;
  unsigned int q1, q2;
  unsigned int z1, z2;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_i_dec_7) {
  char format[] = "%i %i %i %i";
  char str[] = "2147483647 +2147483648 -2147483648 -2147483649";
  unsigned int d1, d2;
  unsigned int q1, q2;
  unsigned int z1, z2;
  unsigned int w1, w2;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1, &w1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_uint_eq(w1, w2);
}
END_TEST

START_TEST(sscanf_spec_li_dec_1) {
  char format[] = "%li%li%li";
  char str[] = "123 +198 -87";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1, z2;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_li_dec_2) {
  char format[] = "%li %li %li";
  char str[] = "123 +198 -87";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1, z2;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_li_dec_3) {
  char format[] = "%1li %1li %1li";
  char str[] = "13 +137 -8";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1 = 0, z2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_li_dec_4) {
  char format[] = "%2li %2li %2li";
  char str[] = "13 +137 -8";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1, z2;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_li_dec_5) {
  char format[] = "%3li %3li %3li";
  char str[] = "13 +137 -8";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1, z2;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_li_dec_6) {
  char format[] = "%30li %24li %21li";
  char str[] = "13 +137 -8";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1, z2;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_li_dec_7) {
  char format[] = "%li %li %li %li";
  char str[] = "2147483647 +2147483648 -2147483648 -2147483649";
  unsigned long int d1, d2;
  unsigned long int q1, q2;
  unsigned long int z1, z2;
  unsigned long int w1, w2;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1, &w1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_uint_eq(w1, w2);
}
END_TEST

START_TEST(sscanf_spec_lli_dec_1) {
  char format[] = "%lli%lli%li";
  char str[] = "123 +198 -87";
  unsigned long long int d1, d2;
  unsigned long long int q1, q2;
  unsigned long long int z1, z2;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_lli_dec_2) {
  char format[] = "%lli %lli %lli";
  char str[] = "123 +198 -87";
  unsigned long long int d1, d2;
  unsigned long long int q1, q2;
  unsigned long long int z1, z2;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_lli_dec_3) {
  char format[] = "%1lli %1lli %1lli";
  char str[] = "13 +137 -8";
  unsigned long long int d1, d2;
  unsigned long long int q1, q2;
  unsigned long long int z1 = 0, z2 = 0;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_lli_dec_4) {
  char format[] = "%2lli %2lli %2lli";
  char str[] = "13 +137 -8";
  unsigned long long int d1, d2;
  unsigned long long int q1, q2;
  unsigned long long int z1, z2;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_lli_dec_5) {
  char format[] = "%3lli %3lli %3lli";
  char str[] = "13 +137 -8";
  unsigned long long int d1, d2;
  unsigned long long int q1, q2;
  unsigned long long int z1, z2;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_lli_dec_6) {
  char format[] = "%30lli %24lli %21lli";
  char str[] = "13 +137 -8";
  unsigned long long int d1, d2;
  unsigned long long int q1, q2;
  unsigned long long int z1, z2;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
}
END_TEST

START_TEST(sscanf_spec_lli_dec_7) {
  char format[] = "%lli %lli %lli %lli";
  char str[] = "2147483647 +2147483648 -2147483648 -2147483649";
  unsigned long long int d1, d2;
  unsigned long long int q1, q2;
  unsigned long long int z1, z2;
  unsigned long long int w1, w2;

  int16_t res1 = s21_sscanf(str, format, &d1, &q1, &z1, &w1);
  int16_t res2 = sscanf(str, format, &d2, &q2, &z2, &w2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(q1, q2);
  ck_assert_uint_eq(z1, z2);
  ck_assert_uint_eq(w1, w2);
}
END_TEST

Suite *test_sscanf_i(void) {
  Suite *s = suite_create("\033[42m==S21_SSCANF_I==\033[0m");
  TCase *tc = tcase_create("sscanf_tc");

  tcase_add_test(tc, sscanf_spec_i_dec_1);
  tcase_add_test(tc, sscanf_spec_i_dec_2);
  tcase_add_test(tc, sscanf_spec_i_dec_3);
  tcase_add_test(tc, sscanf_spec_i_dec_4);
  tcase_add_test(tc, sscanf_spec_i_dec_5);
  tcase_add_test(tc, sscanf_spec_i_dec_6);
  tcase_add_test(tc, sscanf_spec_i_dec_7);

  tcase_add_test(tc, sscanf_spec_hhi_dec_1);
  tcase_add_test(tc, sscanf_spec_hhi_dec_2);
  tcase_add_test(tc, sscanf_spec_hhi_dec_3);
  tcase_add_test(tc, sscanf_spec_hhi_dec_4);
  tcase_add_test(tc, sscanf_spec_hhi_dec_5);
  tcase_add_test(tc, sscanf_spec_hhi_dec_6);
  tcase_add_test(tc, sscanf_spec_hhi_dec_7);

  tcase_add_test(tc, sscanf_spec_hi_dec_1);
  tcase_add_test(tc, sscanf_spec_hi_dec_2);
  tcase_add_test(tc, sscanf_spec_hi_dec_3);
  tcase_add_test(tc, sscanf_spec_hi_dec_4);
  tcase_add_test(tc, sscanf_spec_hi_dec_5);
  tcase_add_test(tc, sscanf_spec_hi_dec_6);
  tcase_add_test(tc, sscanf_spec_hi_dec_7);

  tcase_add_test(tc, sscanf_spec_li_dec_1);
  tcase_add_test(tc, sscanf_spec_li_dec_2);
  tcase_add_test(tc, sscanf_spec_li_dec_3);
  tcase_add_test(tc, sscanf_spec_li_dec_4);
  tcase_add_test(tc, sscanf_spec_li_dec_5);
  tcase_add_test(tc, sscanf_spec_li_dec_6);
  tcase_add_test(tc, sscanf_spec_li_dec_7);

  tcase_add_test(tc, sscanf_spec_lli_dec_1);
  tcase_add_test(tc, sscanf_spec_lli_dec_2);
  tcase_add_test(tc, sscanf_spec_lli_dec_3);
  tcase_add_test(tc, sscanf_spec_lli_dec_4);
  tcase_add_test(tc, sscanf_spec_lli_dec_5);
  tcase_add_test(tc, sscanf_spec_lli_dec_6);
  tcase_add_test(tc, sscanf_spec_lli_dec_7);

  suite_add_tcase(s, tc);
  return s;
}