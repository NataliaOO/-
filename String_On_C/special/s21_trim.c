#include <stdlib.h>

#include "../s21_string.h"

// Функция для обрезки строки
void *s21_trim(const char *src, const char *trim_chars) {
  void *result = "";
  if (src == s21_NULL) {
    result = s21_NULL;  // Обработка случая с NULL
  } else {
    s21_size_t length = s21_strlen(src);
    const char *start = src;
    const char *end = src + length - 1;
    if (trim_chars != s21_NULL) {
      // Находим начало исходной строки без ведущих символов из trim_chars
      while (*start != '\0' && s21_strchr(trim_chars, *start) != s21_NULL) {
        start++;
      }

      // Находим конец исходной строки без завершающих символов из trim_chars
      while (end >= start && s21_strchr(trim_chars, *end) != s21_NULL) {
        end--;
      }
    }

    // Вычисляем длину обрезанной строки
    s21_size_t trimmed_length = end - start + 1;
    // Копируем обрезанную строку в новый буфер
    result = malloc(trimmed_length + 1);
    s21_memcpy(result, start, trimmed_length);
    ((char *)result)[trimmed_length] =
        '\0';  // Добавляем нуль-терминатор в конец обрезанной строки
  }
  return result;
}