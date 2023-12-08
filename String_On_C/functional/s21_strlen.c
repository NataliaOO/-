#include "../s21_string.h"

s21_size_t s21_strlen(const char *str) {
  s21_size_t len = 0;
  // Подсчитываем длину строки, пока не дойдем до завершающего нулевого символа
  for (; str[len]; len++)
    ;
  return len;
}