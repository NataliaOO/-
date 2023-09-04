#include "../s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i;
  // Копируем символы из src в dest, пока не достигнем n или символ конца строки
  for (i = 0; i < n && src[i] != '\0'; i++) {
    dest[i] = src[i];
  }
  // Если источник закончился, но мы еще не достигли n символов,
  // заполняем оставшуюся часть dest нулевыми символами.
  for (; i < n; i++) {
    dest[i] = '\0';
  }
  return dest;
}