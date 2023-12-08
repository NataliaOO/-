#include <stdlib.h>

#include "../s21_string.h"

void *s21_to_upper(const char *str) {
  return s21_change_case_str(str, 1);  // Указываем флаг to_upper равным 1 для
                                       // преобразования в верхний регистр
}