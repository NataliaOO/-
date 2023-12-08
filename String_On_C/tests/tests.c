#include "tests.h"

int main(void) {
  int failed = 0;
  Suite *s21_string_test[] = {test_strlen(),
                              test_memcpy(),
                              test_memchr(),
                              test_memcmp(),
                              test_memset(),
                              test_strncat(),
                              test_strchr(),
                              test_strncmp(),
                              test_strncpy(),
                              test_strcspn(),
                              test_strpbrk(),
                              test_strrchr(),
                              test_strstr(),
                              test_strtok(),
                              test_strerror(),
                              test_to_upper(),
                              test_to_lower(),
                              test_trim(),
                              test_insert(),
                              test_sprintf_c(),
                              test_sprintf_d(),
                              test_sprintf_f(),
                              test_sprintf_u(),
                              test_sprintf_percent(),
                              test_sprintf_e(),
                              test_sprintf_i(),
                              test_sprintf_n(),
                              test_sprintf_hex1(),
                              test_sprintf_hex2(),
                              test_sprintf_octal(),
                              test_sprintf_pointer(),
                              test_sprintf_g(),
                              test_sprintf_s(),
                              test_sscanf_c(),
                              test_sscanf_p(),
                              test_sscanf_u(),
                              test_sscanf_d(),
                              test_sscanf_o(),
                              test_sscanf_percent(),
                              test_sscanf_i(),
                              test_sscanf_n(),
                              test_sscanf_x(),
                              test_sscanf_real(),

                              NULL};

  for (int i = 0; s21_string_test[i] != NULL; i++) {  // (&& failed == 0)
    SRunner *sr = srunner_create(s21_string_test[i]);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  printf("========= FAILED: %d =========\n", failed);

  return failed == 0 ? 0 : 1;
}
