#include "../s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  // Приведение указателей на байтовый тип данных (unsigned char)
  const unsigned char *char_str1 = (const unsigned char *)str1;
  const unsigned char *char_str2 = (const unsigned char *)str2;
  // Инициализация результата сравнения (по умолчанию 0, если строки равны)
  int result = 0;
  // Проходимся по байтам в памяти str1 и str2
  for (s21_size_t i = 0; i < n; i++) {
    // Если текущий байт str1 не равен текущему байту str2
    if (char_str1[i] != char_str2[i]) {
      // Записываем разницу между байтами в качестве результата сравнения
      result = char_str1[i] - char_str2[i];
      // Прекращаем дальнейшее сравнение, так как различие найдено
      break;
    }
  }
  // Возвращаем результат сравнения (0, если строки равны, иначе разницу между
  // байтами)
  return result;
}