#include "../s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int result = 0;
  // Проходим по символам строк str1 и str2 до n или до первого несовпадения
  for (s21_size_t i = 0; i < n; i++) {
    // Если достигнут символ конца строки или символы не равны
    if (str1[i] == '\0' || str1[i] != str2[i]) {
      result = str1[i] - str2[i];  // Вычисляем разницу символов
      break;
    }
  }
  // Возвращаем результат сравнения (0, если строки равны, иначе разницу между
  // символами)
  return result;
}