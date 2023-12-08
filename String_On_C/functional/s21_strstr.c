#include "../s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  if (*needle == '\0') {
    return (char *)haystack;  // Если needle пустая строка, возвращаем haystack
  }
  while (*haystack != '\0') {
    const char *temp_haystack = haystack;
    const char *temp_needle = needle;
    // Проверяем, совпадает ли подстрока needle с текущим местоположением
    // haystack
    while (*temp_needle != '\0' && *temp_haystack == *temp_needle) {
      temp_haystack++;
      temp_needle++;
    }
    // Если подстрока needle полностью совпала, возвращаем haystack
    if (*temp_needle == '\0') {
      return (char *)haystack;
    }

    haystack++;
  }
  // Если needle не найден в haystack, возвращаем NULL
  return s21_NULL;
}