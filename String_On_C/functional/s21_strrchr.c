#include "../s21_string.h"

char *s21_strrchr(const char *str, int c) {
  char char_c = (char)c;
  char *result = s21_NULL;
  // Проходим по строке str и ищем последнее вхождение символа c
  while (*str != '\0') {
    if (*str == char_c) {
      result =
          (char *)str;  // Запоминаем позицию последнего вхождения символа c
    }
    str++;
  }
  if (c == '\0') result = (char *)str;
  // Возвращаем указатель на последнее вхождение символа c или его позицию
  return result;
}