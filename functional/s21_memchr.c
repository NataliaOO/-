#include "../s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  // Приведение указателя на байтовый тип данных (unsigned char)
  const unsigned char *char_str = (const unsigned char *)str;
  // Приведение символа к беззнаковому типу данных
  unsigned char char_c = (unsigned char)c;
  // Инициализация указателя на результат (по умолчанию NULL)
  void *result = s21_NULL;
  // Проходимся по байтам в памяти str
  for (s21_size_t i = 0; i < n; i++) {
    // Если текущий байт равен искомому символу
    if (char_str[i] == char_c) {
      // Запоминаем адрес найденного байта как результат
      result = (void *)(char_str + i);
      // Прекращаем поиск, так как символ найден
      break;
    }
  }
  // Возвращаем найденный результат (может быть NULL, если символ не найден)
  return result;
}