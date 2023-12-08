#include "test.h"

double get_rand(double min, double max) {
  double val = (double)rand() / RAND_MAX;
  return min + val * (max - min);
}

int main(void) {
  int failed = 0;
  Suite *s21_matrix_test[] = {test_create_matrix(),
                              test_eq_matrix(),
                              test_sum_matrix(),
                              test_sub_matrix(),
                              test_mult_matrix(),
                              test_mult_number_matrix(),
                              test_transpose_matrix(),
                              test_determinant(),
                              test_calc_complements(),
                              test_inverse_matrix(),
                              NULL};

  for (int i = 0; s21_matrix_test[i] != NULL; i++) {  // (&& failed == 0)
    SRunner *sr = srunner_create(s21_matrix_test[i]);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  printf("========= FAILED: %d =========\n", failed);

  return failed == 0 ? 0 : 1;
}
