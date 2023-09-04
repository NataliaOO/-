#include "../s21_string.h"

// Функция для преобразования строки в нижний регистр
void *s21_to_lower(const char *str) {
  return s21_change_case_str(str, 0);  // Указываем флаг to_upper равным 0 для
                                       // преобразования в нижний регистр
}