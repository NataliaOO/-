#include "../s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t count = 0;
  // Проходим по строке str1 до тех пор, пока не встретим символ,
  // который есть в str2, либо пока не дойдем до конца строки str1
  while (str1[count] != '\0' && !s21_strchr(str2, str1[count])) {
    count++;
  }
  return count;
}