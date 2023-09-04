#include <stdlib.h>

#include "../s21_string.h"

// Функция для преобразования символа в верхний/нижний регистр (для английского
// алфавита)
char s21_change_case(char ch, int to_upper) {
  char result = ch;
  if (ch >= 'a' && ch <= 'z') {
    // Если символ является строчной буквой, преобразуем его в верхний/нижний
    // регистр
    result = to_upper ? ch - ('a' - 'A') : ch;
  } else if (ch >= 'A' && ch <= 'Z') {
    // Если символ является заглавной буквой, преобразуем его в верхний/нижний
    // регистр
    result = to_upper ? ch : ch + ('a' - 'A');
  }
  // Иначе возвращаем символ без изменений
  return result;
}

// Функция для преобразования строки в верхний/нижний регистр
void *s21_change_case_str(const char *str, int to_upper) {
  char *result = s21_NULL;
  if (str != s21_NULL) {
    s21_size_t length = s21_strlen(str);
    result = malloc(length + 1);  // Выделение памяти для новой строки (плюс
                                  // один байт для нуль-терминатора)
    char *result_ptr = result;
    while (*str != '\0') {
      *result_ptr = s21_change_case(*str, to_upper);
      str++;
      result_ptr++;
    }

    *result_ptr = '\0';  // Добавляем нуль-терминатор в конец новой строки
  }
  return result;
}