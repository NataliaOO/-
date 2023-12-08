#include "../s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  char *result = s21_NULL;
  // Проходим по строке str1 и ищем символ из str2
  while (*str1 != '\0') {
    if (s21_strchr(str2, *str1) != s21_NULL) {
      result = (char *)str1;  // Запоминаем позицию найденного символа
      break;
    }
    str1++;
  }
  // Возвращаем указатель на найденный символ или NULL, если символ не найден
  return result;
}