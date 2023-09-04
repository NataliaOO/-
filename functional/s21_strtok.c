#include "../s21_string.h"

s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t res = 0;
  // Проходим по строке str1, пока символы из str2 продолжают совпадать
  while (*str1 != '\0' && s21_strchr(str2, *str1) != s21_NULL) {
    res++;
    str1++;
  }
  // Возвращаем количество символов, совпавших из str2
  return res;
}

char *s21_strtok(char *str, const char *delim) {
  static char *p = s21_NULL;
  int flag = 0;
  // Если передана новая строка, обновляем указатель p
  if (str) {
    p = str;
  }
  // Если p не равен NULL, находим начало следующей подстроки,
  // пропуская символы из delim, и обновляем указатель p
  if (p) {
    str = p + s21_strspn(p, delim);
    p = str + s21_strcspn(str, delim);

    // Если подстрока пустая, обнуляем указатель p и устанавливаем флаг
    if (p == str) {
      p = s21_NULL;
      flag = 1;
    } else {
      // Иначе заменяем разделитель на нулевой символ
      p = *p ? *p = 0, p + 1 : 0;
    }
  }
  // Если флаг установлен, возвращаем NULL, иначе возвращаем найденную подстроку
  return flag == 1 ? s21_NULL : str;
}
