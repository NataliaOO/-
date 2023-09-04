#include "../s21_string.h"

char *s21_strchr(const char *str, int c) {
  // Проходим по строке до тех пор, пока не найдем искомый символ c
  while (*str != '\0' && *str != c) {
    str++;
  }
  // Если символ c найден, возвращаем указатель на его позицию в строке,
  // иначе возвращаем NULL
  return *str == c ? (char *)str : s21_NULL;
}