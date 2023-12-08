#include "../s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  // Приведение указателей на байтовый тип данных (char)
  char *char_dest = (char *)dest;
  const char *char_src = (const char *)src;
  // Копируем n байтов из src в dest
  for (s21_size_t i = 0; i < n; i++) {
    char_dest[i] = char_src[i];
  }
  // Возвращаем указатель на начало скопированных данных (dest)
  return char_dest;
}