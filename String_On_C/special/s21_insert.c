#include <stdlib.h>

#include "../s21_string.h"

// Функция для вставки строки str в исходную строку src, начиная с заданного
// индекса start_index
void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *result = "";

  if (src == s21_NULL || str == s21_NULL || start_index > s21_strlen(src)) {
    result = s21_NULL;  // Обработка случая с NULL и некорректным start_index
  } else {
    s21_size_t src_len = s21_strlen(src);
    s21_size_t str_len = s21_strlen(str);
    s21_size_t new_len = src_len + str_len;

    // Выделяем память под новую строку (плюс один байт для нуль-терминатора)
    result = malloc(new_len + 1);

    // Копируем часть исходной строки до start_index в новую строку
    s21_memcpy(result, src, start_index);
    // Копируем вставляемую строку str в новую строку
    s21_memcpy(result + start_index, str, str_len);
    // Копируем остаток исходной строки после start_index в новую строку
    s21_memcpy(result + start_index + str_len, src + start_index,
               src_len - start_index);

    result[new_len] = '\0';  // Добавляем нуль-терминатор в конец новой строки
  }
  return result;
}