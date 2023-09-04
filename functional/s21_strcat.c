#include "../s21_string.h"

char *s21_strcat(char *dest, const char *src) {
  // Копируем содержимое строки src в конец строки dest,
  // начиная с позиции, следующей за последним символом в dest,
  // и включая завершающий нулевой символ
  s21_memcpy(dest + s21_strlen(dest), src, s21_strlen(src) + 1);
  return dest;
}