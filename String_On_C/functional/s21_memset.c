#include "../s21_string.h"

void *s21_memset(void *str, int c, s21_size_t n) {
  // Приведение указателя на байтовый тип данных (unsigned char)
  unsigned char *char_str = (unsigned char *)str;
  // Приведение символа к беззнаковому типу данных
  unsigned char char_c = (unsigned char)c;
  // Заполняем блок памяти, начиная с char_str, значением char_c,
  // повторяя это n раз (длина блока)
  for (s21_size_t i = 0; i < n; i++) {
    char_str[i] = char_c;
  }
  // Возвращаем указатель на начало измененной области памяти (str)
  return str;
}